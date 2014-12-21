#include "stdafx.h"
#include "ApeDecoder.h"
#include <ape\APETag.h>

namespace audio
{
	ApeDecoder::ApeDecoder()
	{
		m_total_blocks = 0;
		m_current_blocks = 0;
		m_pAPEDecompress = NULL;
		m_block_algin = 0;

	}


	ApeDecoder::~ApeDecoder()
	{
	}

	int ApeDecoder::Open(const wchar_t* file)
	{
		Decoder::Open(file);
		m_nWaveDataNum = 0;
		int nRetVal = 0;
		m_pAPEDecompress = CreateIAPEDecompress(file, &nRetVal);
		if (NULL == m_pAPEDecompress)
		{
			return AudioError::FailToOpenFile;//E_FAIL;
		}
		m_block_algin = m_pAPEDecompress->GetInfo(APE::APE_INFO_BLOCK_ALIGN);
		m_pWaveDataAlloc.reset(new common::InternalBuffer<BYTE>(APE_BLOCKS_NUM * m_block_algin));
		m_pWaveDataBuffer = (BYTE*)m_pWaveDataAlloc.get()->getData();
		m_total_blocks = m_pAPEDecompress->GetInfo(APE::APE_DECOMPRESS_TOTAL_BLOCKS);
		mWaveInfo.bitrate = m_pAPEDecompress->GetInfo(APE::APE_DECOMPRESS_AVERAGE_BITRATE);
		// get and set wave header
		nRetVal = m_pAPEDecompress->GetInfo(APE::APE_INFO_WAVEFORMATEX, (APE::intn)&mWaveInfo.waveFormatex, 0);

		if (0 != nRetVal)
		{
			return AudioError::FailToGetWaveInfo;//E_FAIL;
		}
		mWaveInfo.waveSize = m_pAPEDecompress->GetInfo(APE::APE_INFO_WAV_DATA_BYTES);
		if (mWaveInfo.waveSize <= 0)
		{
			return AudioError::FailToGetWaveInfo;//E_FAIL;
		}
		mWaveInfo.durationTime = (double)mWaveInfo.waveSize / (double)mWaveInfo.waveFormatex.nAvgBytesPerSec;

		APE::CAPETag * pAPETag = (APE::CAPETag *)m_pAPEDecompress->GetInfo(APE::APE_INFO_TAG);
		BOOL bHasID3Tag = pAPETag->GetHasID3Tag();
		BOOL bHasAPETag = pAPETag->GetHasAPETag();

		if (bHasID3Tag || bHasAPETag)
		{
			// iterate through all the tag fields
			
			APE::CAPETagField * pTagField = pAPETag->GetTagField(APE_TAG_FIELD_TITLE);
			if (pTagField)
			{
			//	/*printf("%X\n",pTagField->GetFieldValue()[0]);
			//	printf("%X\n",pTagField->GetFieldValue()[1]);
			//	printf("%X\n",pTagField->GetFieldValue()[2]);*/
			//	/*if (pTagField->GetIsUTF8Text())
			//	{
			//		CCharWCharHelper cwh;
			//		cwh.ZMultiByteToWideChar(pTagField->GetFieldValue(), ZUTF8);
			//		m_id3.title.SetData(cwh.GetWideChar(), cwh.GetWideCharLength());
			//	}
			//	else
			//		m_id3.title.SetData(pTagField->GetFieldValue(), strlen(pTagField->GetFieldValue()));*/
				SetAudioInfo("TITLE", pTagField->GetFieldValue());
			}


			pTagField = pAPETag->GetTagField(APE_TAG_FIELD_ARTIST);
			if (pTagField)
			{
				SetAudioInfo("ARTIST", pTagField->GetFieldValue());

			}


			pTagField = pAPETag->GetTagField(APE_TAG_FIELD_ALBUM);
			if (pTagField)
			{
				SetAudioInfo("ALBUM", pTagField->GetFieldValue());

			}


			pTagField = pAPETag->GetTagField(APE_TAG_FIELD_YEAR);
			if (pTagField)
			{
				SetAudioInfo("YEAR", pTagField->GetFieldValue());
			}


			pTagField = pAPETag->GetTagField(APE_TAG_FIELD_COMMENT);
			if (pTagField)
			{
				SetAudioInfo("COMMENT", pTagField->GetFieldValue());

			}


			pTagField = pAPETag->GetTagField(APE_TAG_FIELD_GENRE);
			if (pTagField)
			{
				SetAudioInfo("GENRE", pTagField->GetFieldValue());

			}


		}
		return 0;
	}
	int ApeDecoder::Read(BYTE* buffer, DWORD dwSizeToRead, DWORD* sizeReaded)
	{
		BYTE *buf = buffer;
		unsigned int samplesNeed = dwSizeToRead;
		*sizeReaded = 0;
		int nRetVal = 0;

		while (samplesNeed)
		{
			if (m_nWaveDataNum > 0)// we have some data
			{
				unsigned int i;
				if (m_nWaveDataNum >= samplesNeed)
				{
					for (i = 0; i < samplesNeed; i++)
					{
						buf[i] = m_pWaveDataBuffer[i];
					}

					*sizeReaded += samplesNeed;
					m_pWaveDataBuffer = &m_pWaveDataBuffer[samplesNeed];
					m_nWaveDataNum -= samplesNeed;
					samplesNeed = 0;
				}
				else
				{
					for (i = 0; i < m_nWaveDataNum; i++)
					{
						buf[i] = m_pWaveDataBuffer[i];
					}
					*sizeReaded += m_nWaveDataNum;
					samplesNeed -= m_nWaveDataNum;
					buf = &buf[m_nWaveDataNum];
					m_pWaveDataBuffer = (BYTE*)m_pWaveDataAlloc.get()->getData();
					m_nWaveDataNum = 0;
				}
			}
			else // decode data
			{
				if (m_current_blocks < m_total_blocks)
				{
					int nBlocksRetrieved;// 1024 * blockalign
					nRetVal = m_pAPEDecompress->GetData((char*)m_pWaveDataAlloc.get()->getData(), APE_BLOCKS_NUM, &nBlocksRetrieved);
					m_current_blocks += nBlocksRetrieved;
					if (ERROR_SUCCESS != nRetVal)
					{
						return AudioError::FailToDecodeData;//E_FAIL;
					}
					m_pWaveDataBuffer = (BYTE*)m_pWaveDataAlloc.get()->getData();
					m_nWaveDataNum = nBlocksRetrieved * m_block_algin;
				}
				else
				{
					return AudioError::FailToRead;
				}
			}
		}
		mCurrentPosition += *sizeReaded;
		return 0;
	}
	int ApeDecoder::Reset()
	{
		m_current_blocks = 0;
		mCurrentPosition = 0;
		m_nWaveDataNum = 0;
		m_pAPEDecompress->Seek(0);
		return 0;
	}
	int ApeDecoder::Seek(float duration)
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
			m_nWaveDataNum = 0;
			mCurrentPosition = seekSize;
			unsigned int mcBlock = seekSize / m_block_algin;
			if (mcBlock > m_total_blocks)
			{
				return AudioError::SeekDurationOutOfRange;
			}
			int num = m_pAPEDecompress->Seek(mcBlock);
			m_current_blocks = mcBlock;
		}
		return 0;
	}
	int ApeDecoder::Close()
	{
		if (m_pAPEDecompress)
		{
			delete m_pAPEDecompress;
		}
		m_total_blocks = 0;
		m_current_blocks = 0;
		m_pAPEDecompress = NULL;
		m_block_algin = 0;
		return 0;
	}

	void ApeDecoder::SetAudioInfo(const char* key, const char* value)
	{
		mAudioInfo.Put(key, value);
	}
}