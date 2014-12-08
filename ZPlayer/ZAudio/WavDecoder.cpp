#include "stdafx.h"
#include "WavDecoder.h"

namespace audio
{
	WavDecoder::WavDecoder()
	{
	}


	WavDecoder::~WavDecoder()
	{
	}

	int WavDecoder::Open(const wchar_t* file)
	{
		Decoder::Open(file);

		fileBuffer.reset(new common::InternalBuffer<wchar_t>(wcslen(file) + 1));
		
		wcscpy(fileBuffer->getData(), file);
		
		m_hmmio = mmioOpen(fileBuffer->getData(), NULL, MMIO_ALLOCBUF | MMIO_READ);

		if (NULL == m_hmmio)
		{
			HRSRC hResInfo;
			HGLOBAL hResData;
			DWORD dwSize;
			VOID* pvRes;

			// Loading it as a file failed, so try it as a resource
			if (NULL == (hResInfo = FindResource(NULL, (wchar_t*)fileBuffer.get(), L"WAVE")))
			{
				if (NULL == (hResInfo = FindResource(NULL, (wchar_t*)fileBuffer.get(), L"WAV")))
					//return DXTRACE_ERR( L"FindResource", E_FAIL );
					return AudioError::UnrecognizedFileFormat;
			}

			if (NULL == (hResData = LoadResource(GetModuleHandle(NULL), hResInfo)))
				//return DXTRACE_ERR( L"LoadResource", E_FAIL );
				return AudioError::UnrecognizedFileFormat;

			if (0 == (dwSize = SizeofResource(GetModuleHandle(NULL), hResInfo)))
				//return DXTRACE_ERR( L"SizeofResource", E_FAIL );
				return AudioError::UnrecognizedFileFormat;

			if (NULL == (pvRes = LockResource(hResData)))
				//return DXTRACE_ERR( L"LockResource", E_FAIL );
				return AudioError::UnrecognizedFileFormat;

			//m_pResourceBuffer = new CHAR[dwSize];
			m_pResourceBuffer.reset(new common::InternalBuffer<CHAR>(dwSize));
			if (m_pResourceBuffer.get() == NULL)

				return  AudioError::FailToAllocateMemory;
			memcpy(m_pResourceBuffer.get(), pvRes, dwSize);

			MMIOINFO mmioInfo;
			ZeroMemory(&mmioInfo, sizeof(mmioInfo));
			mmioInfo.fccIOProc = FOURCC_MEM;
			mmioInfo.cchBuffer = dwSize;
			mmioInfo.pchBuffer = (CHAR*)m_pResourceBuffer.get();

			m_hmmio = mmioOpen(NULL, &mmioInfo, MMIO_ALLOCBUF | MMIO_READ);
		}
		HRESULT hr;
		if (FAILED(hr = ReadMMIO()))
		{
			// ReadMMIO will fail if its an not a wave file
			mmioClose(m_hmmio, 0);
			// return DXTRACE_ERR( L"ReadMMIO", hr );
			return hr;
		}

		if (0 != Reset())
			//return DXTRACE_ERR( L"ResetFile", hr );
			return hr;

		// After the reset, the size of the wav file is m_ck.cksize so store it now
		mWaveInfo.waveSize = m_ck.cksize;
		mWaveInfo.durationTime = (float)((double)mWaveInfo.waveSize / mWaveInfo.waveFormatex.nAvgBytesPerSec);
		mWaveInfo.bitrate = mWaveInfo.waveFormatex.nChannels * mWaveInfo.waveFormatex.nSamplesPerSec * mWaveInfo.waveFormatex.wBitsPerSample;
		return 0;
	}
	int WavDecoder::Read(BYTE* buffer, DWORD dwSizeToRead, DWORD* sizeReaded)
	{
		MMIOINFO mmioinfoIn; // current status of m_hmmio

		if (m_hmmio == NULL)
			return AudioError::FileNotInitialized;
		if (buffer == NULL || sizeReaded == NULL)
			return AudioError::InvalidParameter;

		
		*sizeReaded = 0;

		if (0 != mmioGetInfo(m_hmmio, &mmioinfoIn, 0))
			return AudioError::FailToRead;

		UINT cbDataIn = dwSizeToRead;
		if (cbDataIn > m_ck.cksize)
			cbDataIn = m_ck.cksize;

		m_ck.cksize -= cbDataIn;

		for (DWORD cT = 0; cT < cbDataIn; cT++)
		{
			// Copy the bytes from the io to the buffer.
			if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
			{
				if (0 != mmioAdvance(m_hmmio, &mmioinfoIn, MMIO_READ))
					return AudioError::FailToRead;

				if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
					return AudioError::FailToRead;
			}

			// Actual copy.
			*((BYTE*)buffer + cT) = *((BYTE*)mmioinfoIn.pchNext);
			mmioinfoIn.pchNext++;
		}

		if (0 != mmioSetInfo(m_hmmio, &mmioinfoIn, 0))
			return AudioError::FailToRead;

		*sizeReaded = cbDataIn;
		mCurrentPosition += cbDataIn;
		return 0;
	}
	int WavDecoder::Reset()
	{
		mCurrentPosition = 0;
		if (m_hmmio == NULL)
			return AudioError::FileNotInitialized;

		// Seek to the data
		if (-1 == mmioSeek(m_hmmio, m_ckRiff.dwDataOffset + sizeof(FOURCC),
			SEEK_SET))
			return AudioError::FailToReset;

		// Search the input file for the 'data' chunk.
		m_ck.ckid = mmioFOURCC('d', 'a', 't', 'a');
		if (0 != mmioDescend(m_hmmio, &m_ck, &m_ckRiff, MMIO_FINDCHUNK))
			return AudioError::FailToReset;
		return 0;
	}
	int WavDecoder::Seek(float duration)
	{
		if (duration < 0 || duration >= mWaveInfo.durationTime)
		{
			return AudioError::SeekDurationOutOfRange;//E_FAIL;
		}

		if (0 == duration)
		{
			mCurrentPosition = 0;
			return Reset();
		}
		else
		{
			DWORD seekSize = (DWORD)(duration * mWaveInfo.waveFormatex.nAvgBytesPerSec);

			if (seekSize > mWaveInfo.waveSize)
			{
				return AudioError::SeekDurationOutOfRange;;
			}
			mCurrentPosition = seekSize;
			if (-1 == mmioSeek(m_hmmio, m_ckRiff.dwDataOffset + sizeof(FOURCC)+seekSize,
				SEEK_SET))
				return AudioError::FailToSeek;

			// Search the input file for the 'data' chunk.
			//m_ck.ckid = mmioFOURCC( 'd', 'a', 't', 'a' );
			//if( 0 != mmioDescend( m_hmmio, &m_ck, &m_ckRiff, MMIO_FINDCHUNK ) )
			//    return E_FAIL;
			return 0;
		}
	}
	int WavDecoder::Close()
	{
		mmioClose(m_hmmio, 0);
		m_hmmio = NULL;
		return 0;
	}

	HRESULT WavDecoder::ReadMMIO()
	{
		MMCKINFO ckIn;           // chunk info. for general use.
		PCMWAVEFORMAT pcmWaveFormat;  // Temp PCM structure to load in.

		memset(&ckIn, 0, sizeof(ckIn));

		if ((0 != mmioDescend(m_hmmio, &m_ckRiff, NULL, 0)))
			//return DXTRACE_ERR( L"mmioDescend", E_FAIL );
			return E_FAIL;

		// Check to make sure this is a valid wave file
		if ((m_ckRiff.ckid != FOURCC_RIFF) ||
			(m_ckRiff.fccType != mmioFOURCC('W', 'A', 'V', 'E')))
			//return DXTRACE_ERR( L"mmioFOURCC", E_FAIL );
			return E_FAIL;

		// Search the input file for for the 'fmt ' chunk.
		ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
		if (0 != mmioDescend(m_hmmio, &ckIn, &m_ckRiff, MMIO_FINDCHUNK))
			//return DXTRACE_ERR( L"mmioDescend", E_FAIL );
			return E_FAIL;

		// Expect the 'fmt' chunk to be at least as large as <PCMWAVEFORMAT>;
		// if there are extra parameters at the end, we'll ignore them
		if (ckIn.cksize < (LONG)sizeof(PCMWAVEFORMAT))
			//return DXTRACE_ERR( L"sizeof(PCMWAVEFORMAT)", E_FAIL );
			return E_FAIL;

		// Read the 'fmt ' chunk into <pcmWaveFormat>.
		if (mmioRead(m_hmmio, (HPSTR)&pcmWaveFormat,
			sizeof(pcmWaveFormat)) != sizeof(pcmWaveFormat))
			//return DXTRACE_ERR( L"mmioRead", E_FAIL );
			return E_FAIL;

		// Allocate the waveformatex, but if its not pcm format, read the next
		// word, and thats how many extra bytes to allocate.
		if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
		{
			

			// Copy the bytes from the pcm structure to the waveformatex structure
			memcpy(&mWaveInfo.waveFormatex, &pcmWaveFormat, sizeof(pcmWaveFormat));
			mWaveInfo.waveFormatex.cbSize = 0;
		}
		else
		{
			// Read in length of extra bytes.
			WORD cbExtraBytes = 0L;
			if (mmioRead(m_hmmio, (CHAR*)&cbExtraBytes, sizeof(WORD)) != sizeof(WORD))
				//return DXTRACE_ERR( L"mmioRead", E_FAIL );
				return E_FAIL;

			WAVEFORMATEX* m_pwfx = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)+cbExtraBytes];
			if (NULL == m_pwfx)
				//return DXTRACE_ERR( L"new", E_FAIL );
				return E_FAIL;

			// Copy the bytes from the pcm structure to the waveformatex structure
			memcpy(m_pwfx, &pcmWaveFormat, sizeof(pcmWaveFormat));
			m_pwfx->cbSize = cbExtraBytes;

			// Now, read those extra bytes into the structure, if cbExtraAlloc != 0.
			if (mmioRead(m_hmmio, (CHAR*)(((BYTE*)&(m_pwfx->cbSize)) + sizeof(WORD)),
				cbExtraBytes) != cbExtraBytes)
			{
				delete (m_pwfx);
				//return DXTRACE_ERR( L"mmioRead", E_FAIL );
				return E_FAIL;
			}
			mWaveInfo.waveFormatex.cbSize = m_pwfx->cbSize;
			mWaveInfo.waveFormatex.nAvgBytesPerSec = m_pwfx->nAvgBytesPerSec;
			mWaveInfo.waveFormatex.nBlockAlign = m_pwfx->nBlockAlign;
			mWaveInfo.waveFormatex.nChannels = m_pwfx->nChannels;
			mWaveInfo.waveFormatex.nSamplesPerSec = m_pwfx->nSamplesPerSec;
			mWaveInfo.waveFormatex.wBitsPerSample = m_pwfx->wBitsPerSample;
			mWaveInfo.waveFormatex.wFormatTag = m_pwfx->wFormatTag;

			delete (m_pwfx);
			
		}

		// Ascend the input file out of the 'fmt ' chunk.
		if (0 != mmioAscend(m_hmmio, &ckIn, 0))
		{
			//return DXTRACE_ERR( L"mmioAscend", E_FAIL );
			return E_FAIL;
		}

		return S_OK;

	}
}

