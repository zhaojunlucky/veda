#pragma once
#include "Decoder.h"
#include <Exia\common\InternalBuffer.hpp>
#include <FLAC\stream_decoder.h>
#include <FLAC\metadata.h>
#include <memory>

namespace audio
{
	class __declspec(dllexport) FlacDecoder :
		public Decoder
	{
	public:
		FlacDecoder();
		virtual ~FlacDecoder();

		virtual int Open(const wchar_t* file);
		virtual int Read(BYTE* buffer, DWORD dwSizeToRead, DWORD* sizeReaded);
		virtual int Reset();
		virtual int Seek(float duration);
		virtual int Close();
	private:
		void SetAudioInfo(const char* key, const char* value, size_t length);
	private:
		FLAC__StreamDecoder *decoder;
		FLAC__StreamDecoderInitStatus init_status;
		static void error_callback(const FLAC__StreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status, void *client_data);
		static void metadata_callback(const FLAC__StreamDecoder *decoder, const FLAC__StreamMetadata *metadata, void *client_data);
		static FLAC__StreamDecoderWriteStatus write_callback(const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client_data);
		long metaDataSize;
		unsigned int m_nWaveDataNum;		// number of samples in samples buffer
		std::shared_ptr<common::InternalBuffer<BYTE>> m_pWaveDataAlloc;
		BYTE* m_pWaveDataBuffer;
	};
}


