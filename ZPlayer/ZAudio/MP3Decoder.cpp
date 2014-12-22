#include "stdafx.h"
#include "MP3Decoder.h"
#include <ZString.h>

namespace audio
{
	MP3Decoder::MP3Decoder()
	{
	}


	MP3Decoder::~MP3Decoder()
	{
	}

	int MP3Decoder::Open(const wchar_t* file)
	{
		Decoder::Open(file);

		if (mpg123_init() != MPG123_OK)
		{
			return AudioError::FailToInitialized;
		}
		
		int ret = -1;
		_handle = mpg123_new(NULL, &ret);
		if (_handle == NULL || ret != MPG123_OK)
		{
			return AudioError::FailToInitializeAudioLibrary;
		}
		
		if (mpg123_topen(_handle, file) != MPG123_OK)
		{
			return AudioError::FailToOpenFile;
		}
		struct mpg123_frameinfo i;
		mpg123_scan(_handle);
		mpg123_info(_handle, &i);
		switch (i.vbr)
		{
		case MPG123_CBR: mWaveInfo.bitrate = i.bitrate; break;
		case MPG123_VBR: mWaveInfo.bitrate = 0; break;
		case MPG123_ABR: mWaveInfo.bitrate = i.bitrate; break;
		default: break;
		}
		// set the wave header
		long rate = 0;
		int channel = 0;
		int encoding = 0;

		if (mpg123_getformat(_handle, &rate, &channel, &encoding) != MPG123_OK)
			return AudioError::FailToGetWaveInfo;//-1;
		if ((encoding & MPG123_ENC_16) == MPG123_ENC_16)
			encoding = 16;
		else if ((encoding & MPG123_ENC_32) == MPG123_ENC_32)
			encoding = 32;
		else
			encoding = 8;

		WAVEFORMATEX* m_pwfx = &mWaveInfo.waveFormatex;
		m_pwfx->wFormatTag = WAVE_FORMAT_PCM;
		m_pwfx->nChannels = channel;
		m_pwfx->nSamplesPerSec = rate;
		m_pwfx->wBitsPerSample = encoding;
		m_pwfx->nBlockAlign = (encoding / 8) * channel;
		m_pwfx->nAvgBytesPerSec = rate * (encoding / 8) * channel;
		m_pwfx->cbSize = 0;

		mWaveInfo.waveSize = mpg123_length(_handle) * (m_pwfx->nBlockAlign);
		mWaveInfo.durationTime = (float)((double)mWaveInfo.waveSize / m_pwfx->nAvgBytesPerSec);


		return 0;
	}
	int MP3Decoder::Read(BYTE* buffer, DWORD dwSizeToRead, DWORD* sizeReaded)
	{
		size_t outsize = 0;
		int ret = mpg123_read(_handle, buffer, dwSizeToRead, &outsize);
		*sizeReaded = 0;
		if (ret != MPG123_OK)
			return AudioError::FailToDecodeData;//E_FAIL;
		*sizeReaded = outsize;
		mCurrentPosition += outsize;
		return 0;
	}
	int MP3Decoder::Reset()
	{
		mCurrentPosition = 0;
		if (mpg123_seek(_handle, 0, SEEK_SET) >= 0)
		{
			return 0;
		}
		return AudioError::FailToSeek;
	}
	int MP3Decoder::Seek(float duration)
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
				return AudioError::SeekDurationOutOfRange;
			}
			mCurrentPosition = seekSize;
			unsigned int samples = (unsigned int)((double)mWaveInfo.waveFormatex.nSamplesPerSec * (double)duration);
			if (mpg123_seek(_handle, samples, SEEK_SET) >= 0)
			{
				return 0;
			}
		}
		return AudioError::FailToSeek;//E_FAIL;
	}
	int MP3Decoder::Close()
	{
		if (_handle != NULL)
		{
			mpg123_close(_handle);
			mpg123_delete(_handle);
			mpg123_exit();
			_handle = NULL;
		}
		return 0;
	}
}