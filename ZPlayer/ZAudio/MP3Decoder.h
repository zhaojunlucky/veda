#pragma once
#include "Decoder.h"
#include <libmpg123\mpg123.h>

namespace audio
{
	class __declspec(dllexport) MP3Decoder :
		public Decoder
	{
	public:
		MP3Decoder();
		virtual ~MP3Decoder();

		virtual int Open(const wchar_t* file);
		virtual int Read(BYTE* buffer, DWORD dwSizeToRead, DWORD* sizeReaded);
		virtual int Reset();
		virtual int Seek(float duration);
		virtual int Close();
	private:
		struct mpg123_handle_struct* _handle;
	};

}

