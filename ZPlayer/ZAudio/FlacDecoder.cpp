#include "stdafx.h"
#include "FlacDecoder.h"
#include <stdio.h>
#include <ZString.h>

namespace audio
{
	FlacDecoder::FlacDecoder()
	{
		m_pWaveDataAlloc.reset(new common::InternalBuffer<BYTE>(10240));
	}


	FlacDecoder::~FlacDecoder()
	{
	}

	int FlacDecoder::Open(const wchar_t* file)
	{
		Decoder::Open(file);
		veda::AString tmp;
		tmp.from(file, wcslen(file));
		

		FILE *afile = fopen(tmp.c_str(), "r");
		long len = 0;
		if (afile)
		{
			fseek(afile, 0, SEEK_END);
			len = ftell(afile);
			fclose(afile);
		}
	
		if (NULL == (decoder = FLAC__stream_decoder_new()))
		{
			return AudioError::FailToInitialized;//E_FAIL;// ??
		}
		(void)FLAC__stream_decoder_set_md5_checking(decoder, true);
		init_status = FLAC__stream_decoder_init_file(decoder, tmp.c_str(), write_callback, metadata_callback, error_callback, /*client_data=*/this);
		if (FLAC__STREAM_DECODER_INIT_STATUS_OK != init_status)
		{
			return AudioError::FailToOpenFile;//E_FAIL;
		}
		metaDataSize = 0;
		// process metadata

		FLAC__bool ok = FLAC__stream_decoder_process_until_end_of_metadata(decoder);

		if (!ok)
		{
			return AudioError::FailToDecodeData;//E_FAIL;
		}

		metaDataSize = len - metaDataSize;
		if (metaDataSize >= 0)
		{
			mWaveInfo.bitrate = 8.0 * metaDataSize / mWaveInfo.durationTime / 1000.0;
		}
		return 0;
	}
	int FlacDecoder::Read(BYTE* buffer, DWORD dwSizeToRead, DWORD* sizeReaded)
	{
		unsigned int samplesNeed = dwSizeToRead;
		//unsigned int sampleHave = 0;
		*sizeReaded = 0;
		BYTE *buf = buffer;
		while (samplesNeed)
		{
			if (m_nWaveDataNum) // we have some data
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
					m_pWaveDataBuffer = (BYTE*)m_pWaveDataAlloc.get();
					m_nWaveDataNum = 0;
				}
			}
			else
			{
				// decode data
				FLAC__bool ok = FLAC__stream_decoder_process_single(decoder);
				if (!ok)
				{
					return AudioError::FailToDecodeData;//E_FAIL;
				}
				if (FLAC__STREAM_DECODER_END_OF_STREAM == FLAC__stream_decoder_get_state(decoder))
					break;
			}
		}
		mCurrentPosition += *sizeReaded;

		return 0;
	}
	int FlacDecoder::Reset()
	{
		m_nWaveDataNum = 0;
		mCurrentPosition = 0;
		if (false == FLAC__stream_decoder_seek_absolute(decoder, 0))
		{
			return AudioError::FailToReset;//E_FAIL;
		}

		if (FLAC__STREAM_DECODER_SEEK_ERROR == FLAC__stream_decoder_get_state(decoder))
		{
			if (false == FLAC__stream_decoder_flush(decoder))
			{
				return AudioError::FailToReset;//E_FAIL;
			}

			if (false == FLAC__stream_decoder_reset(decoder))
			{
				return AudioError::FailToReset;//E_FAIL;
			}
		}
		return 0;
	}
	int FlacDecoder::Seek(float duration)
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
			unsigned int samples = (unsigned int)((float)mWaveInfo.waveFormatex.nSamplesPerSec * (float)duration);
			//if(0 == samples)
			//{
			//	samples = 1;
			//}
			m_nWaveDataNum = 0;
			if (false == FLAC__stream_decoder_seek_absolute(decoder, samples))
			{
				return AudioError::FailToSeek;//E_FAIL;
			}

			if (FLAC__STREAM_DECODER_SEEK_ERROR == FLAC__stream_decoder_get_state(decoder))
			{
				if (false == FLAC__stream_decoder_flush(decoder))
				{
					return AudioError::FailToSeek;//E_FAIL;
				}

				if (false == FLAC__stream_decoder_reset(decoder))
				{
					return AudioError::FailToSeek;//E_FAIL;
				}
			}
		}

		return 0;
	}
	int FlacDecoder::Close()
	{
		if (NULL != decoder)
		{
			FLAC__stream_decoder_delete(decoder);
		}
		decoder = NULL;
		return 0;
	}


	void FlacDecoder::error_callback(const FLAC__StreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status, void *client_data)
	{

	}

	void FlacDecoder::metadata_callback(const FLAC__StreamDecoder *decoder, const FLAC__StreamMetadata *metadata, void *client_data)
	{
		FlacDecoder *flac = (FlacDecoder*)client_data;
		flac->metaDataSize += metadata->length;
		if (FLAC__METADATA_TYPE_STREAMINFO == metadata->type)
		{
			flac->mWaveInfo.waveSize = (DWORD)(metadata->data.stream_info.total_samples * metadata->data.stream_info.channels
				* (metadata->data.stream_info.bits_per_sample / 8));

			flac->mWaveInfo.durationTime = (float)metadata->data.stream_info.total_samples / (float)metadata->data.stream_info.sample_rate;

			flac->mWaveInfo.waveFormatex.nChannels = metadata->data.stream_info.channels;
			flac->mWaveInfo.waveFormatex.nBlockAlign = metadata->data.stream_info.channels * (metadata->data.stream_info.bits_per_sample / 8);
			flac->mWaveInfo.waveFormatex.wFormatTag = 1;
			flac->mWaveInfo.waveFormatex.nSamplesPerSec = metadata->data.stream_info.sample_rate;
			flac->mWaveInfo.waveFormatex.wBitsPerSample = metadata->data.stream_info.bits_per_sample;
			flac->mWaveInfo.waveFormatex.nAvgBytesPerSec = flac->mWaveInfo.waveFormatex.nBlockAlign * metadata->data.stream_info.sample_rate;
			flac->mWaveInfo.waveFormatex.cbSize = 0;

		}
		else if (FLAC__METADATA_TYPE_VORBIS_COMMENT == metadata->type)
		{
			int entrynr = FLAC__metadata_object_vorbiscomment_find_entry_from(metadata, 0, "TITLE");
			if (-1 != entrynr)
			{
				FLAC__StreamMetadata_VorbisComment_Entry  & e = metadata->data.vorbis_comment.comments[entrynr];
				flac->SetAudioInfo("TITLE", (char*)e.entry, e.length);
			
			}
			

			entrynr = FLAC__metadata_object_vorbiscomment_find_entry_from(metadata, 0, "ARTIST");
			if (-1 != entrynr)
			{
				FLAC__StreamMetadata_VorbisComment_Entry  & e = metadata->data.vorbis_comment.comments[entrynr];
				flac->SetAudioInfo("ARTIST", (char*)e.entry, e.length);

			}
			

			entrynr = FLAC__metadata_object_vorbiscomment_find_entry_from(metadata, 0, "ALBUM");
			if (-1 != entrynr)
			{
				FLAC__StreamMetadata_VorbisComment_Entry  & e = metadata->data.vorbis_comment.comments[entrynr];
				flac->SetAudioInfo("ALBUM", (char*)e.entry, e.length);

			}
			


			entrynr = FLAC__metadata_object_vorbiscomment_find_entry_from(metadata, 0, "GENRE");
			if (-1 != entrynr)
			{
				FLAC__StreamMetadata_VorbisComment_Entry  & e = metadata->data.vorbis_comment.comments[entrynr];
				flac->SetAudioInfo("GENRE", (char*)e.entry, e.length);

			}


		}
		else if (FLAC__METADATA_TYPE_PICTURE == metadata->type)
		{
			const FLAC__StreamMetadata_Picture *pic = &metadata->data.picture;
			if (FLAC__STREAM_METADATA_PICTURE_TYPE_MEDIA == pic->type || FLAC__STREAM_METADATA_PICTURE_TYPE_LEAD_ARTIST == pic->type
				|| FLAC__STREAM_METADATA_PICTURE_TYPE_ARTIST == pic->type)
			{
				if (0 == _stricmp(pic->mime_type, "image/png") || 0 == _stricmp(pic->mime_type, "image/jpeg")
					|| 0 == _stricmp(pic->mime_type, "image/bmp") || 0 == _stricmp(pic->mime_type, "image/jpg"))
				{
					/*flac->m_id3.id3Bitmap->height = pic->height;
					flac->m_id3.id3Bitmap->width = pic->width;
					unsigned int w;
					unsigned int h;
					flac->m_id3.id3Bitmap->hbm = DecodePicture(pic->mime_type, (char*)pic->data, pic->data_length, &w, &h);*/
				}
			}

		}
	}

	FLAC__StreamDecoderWriteStatus FlacDecoder::write_callback(const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client_data)
	{

		FlacDecoder *flac = (FlacDecoder*)client_data;

		if (flac->mWaveInfo.waveFormatex.nSamplesPerSec != frame->header.sample_rate)
		{
			return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;//
		}
		if (flac->mWaveInfo.waveFormatex.wBitsPerSample != frame->header.bits_per_sample)
		{
			return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;//
		}
		if (flac->mWaveInfo.waveFormatex.nChannels != frame->header.channels)
		{
			return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE; // skip this frame
		}
		unsigned int frameBytes = frame->header.blocksize * 4;// always use 16 bit

		if (frameBytes > flac->m_pWaveDataAlloc->GetBufferSize())
		{
			flac->m_pWaveDataAlloc.reset(new common::InternalBuffer<BYTE>(frameBytes));
		}

		//detect if stereo or mono
		unsigned int right = 0;
		switch (frame->header.channels)
		{
		case 1: //mono 
			right = 0;
			break;

		case 2: //stereo
			right = 1;
			break;
		default:
			return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
		}

		// set data
		/*switch(frame->header.bits_per_sample)
		{
		case 24:
		{
		unsigned int i;
		unsigned int j;
		BYTE *buf = (BYTE*)flac->m_pSamplesAlloc;
		for(i = 0, j = 0; i < frame->header.blocksize; i++, j += 2)
		{
		buf[j] = buffer[0][i] >> 8;
		buf[j + 1] = buffer[right][i] >> 8;
		}
		}
		break;

		case 16:
		{
		unsigned int i;
		unsigned int j = 0;
		BYTE *buf = (BYTE*)flac->m_pSamplesAlloc;
		//for(i = 0, j = 0; i < frame->header.blocksize; i++, j += 2)
		//{
		//	buf[j] = buffer[0][i];
		//	buf[j + 1] = buffer[right][i];
		//}
		for(i = 0; i < frame->header.blocksize, j < frameBytes; i++)
		{
		buf[j++] = buffer[0][i];
		buf[j++] = buffer[0][i] >> 8;
		buf[j++] = buffer[1][i];
		buf[j++] = buffer[1][i] >> 8;
		}
		}
		break;

		case 8:
		{
		unsigned int i;
		unsigned int j;
		BYTE *buf = (BYTE*)flac->m_pSamplesAlloc;
		for(i = 0, j = 0; i < frame->header.blocksize; i++, j += 2)
		{
		buf[j] = buffer[0][i] << 8;
		buf[j + 1] = buffer[right][i] << 8;
		}
		}
		break;

		default:
		return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
		}*/

		unsigned int i;
		unsigned int j = 0;
		BYTE *buf = (BYTE*)flac->m_pWaveDataAlloc.get();
		//for(i = 0, j = 0; i < frame->header.blocksize; i++, j += 2)
		//{
		//	buf[j] = buffer[0][i];
		//	buf[j + 1] = buffer[right][i];
		//}
		for (i = 0; i < frame->header.blocksize, j < frameBytes; i++)
		{
			buf[j++] = buffer[0][i];
			buf[j++] = buffer[0][i] >> 8;
			buf[j++] = buffer[1][i];
			buf[j++] = buffer[1][i] >> 8;
		}

		flac->m_pWaveDataBuffer = (BYTE*)flac->m_pWaveDataAlloc.get();
		flac->m_nWaveDataNum = frameBytes;//frame->header.blocksize * 4;
		return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
	}

	void FlacDecoder::SetAudioInfo(const char* key, const char* value, size_t length)
	{
		for (size_t i = 0; i < length; i++)
		{
			if (value[i] == '=')
			{
				mAudioInfo.Put(key, &value[++i]);
			}
		}
	}
}