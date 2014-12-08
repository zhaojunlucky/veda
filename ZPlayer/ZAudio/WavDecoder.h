#pragma once
#include "Decoder.h"
#include <MMSystem.h>
#include <memory>
#include <Exia\common\InternalBuffer.hpp>
namespace audio
{
	class __declspec(dllexport) WavDecoder :
		public Decoder
	{
	public:
		WavDecoder();
		virtual ~WavDecoder();

		virtual int Open(const wchar_t* file);
		virtual int Read(BYTE* buffer, DWORD dwSizeToRead, DWORD* sizeReaded) ;
		virtual int Reset() ;
		virtual int Seek(float duration) ;
		virtual int Close();

	private:
		HRESULT ReadMMIO();
	private:
		HMMIO m_hmmio;       // MM I/O handle for the WAVE
		MMCKINFO m_ck;          // Multimedia RIFF chunk
		MMCKINFO m_ckRiff;      // Use in opening a WAVE file
		MMIOINFO m_mmioinfoOut;
		std::shared_ptr<common::InternalBuffer<CHAR>> m_pResourceBuffer;
		std::shared_ptr<common::InternalBuffer<wchar_t>> fileBuffer;
	};
}


