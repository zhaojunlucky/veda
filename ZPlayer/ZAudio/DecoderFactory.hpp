#pragma once
#include "Decoder.h"
#include "ApeDecoder.h"
#include "FlacDecoder.h"
#include "MP3Decoder.h"
#include "WavDecoder.h"
#include "common.h"

namespace audio
{
	class DecoderFactory
	{
	public:
		static Decoder* CreateDecoderByFile(const wchar_t* file)
		{
			if (NULL == file)
			{
				return 0;
			}
			Decoder* d = 0;
			std::wstring str = file;
			std::size_t pos = str.rfind(L".");
			if (pos != std::string::npos)
			{
				std::wstring extension = str.substr(pos + 1);
				if (wcsicmp(extension.c_str(), L"mp3") == 0)
				{
					d = new MP3Decoder;
				}
				else if (wcsicmp(extension.c_str(), L"flac") == 0)
				{
					d = new FlacDecoder;
				}
				else if (wcsicmp(extension.c_str(), L"ape") == 0)
				{
					d = new ApeDecoder;
				}
				else if (wcsicmp(extension.c_str(), L"wav") == 0)
				{
					d = new WavDecoder;
				}
			}
			return d;
		}

		static Decoder* CreateDecoderByFile(const char* file)
		{
			if (NULL == file)
			{
				return 0;
			}
			eio::StringConvertInternal sci;
			return CreateDecoderByFile(sci.Char2Wchar(file,strlen(file)));
		}

		static AudioFormat DetectMediaType(const wchar_t* file)
		{
			if (NULL == file)
			{
				return AudioFormat::Unknown;
			}
			std::wstring str = file;
			std::size_t pos = str.rfind(L".");
			AudioFormat af = AudioFormat::Unknown;
			if (pos != std::string::npos)
			{
				std::wstring extension = str.substr(pos + 1);
				if (wcsicmp(extension.c_str(), L"mp3"))
				{
					af = MP3;
				}
				else if (wcsicmp(extension.c_str(), L"flac"))
				{
					af = Flac;
				}
				else if (wcsicmp(extension.c_str(), L"ape"))
				{
					af = Ape;
				}
				else if (wcsicmp(extension.c_str(), L"wav"))
				{
					af = Wav;
				}
			}
			return af;
		}

		static AudioFormat DetectMediaType(const char* file)
		{
			if (NULL == file)
			{
				return AudioFormat::Unknown;
			}
			eio::StringConvertInternal sci;
			return DetectMediaType(sci.Char2Wchar(file,strlen(file)));
		}
	};

}