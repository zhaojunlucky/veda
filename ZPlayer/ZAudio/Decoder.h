#pragma once
#include "common.h"
#include <ZString.h>
#include "AudioInfo.h"
namespace audio
{
	class MP3Decoder;
	class __declspec(dllexport) Decoder
	{
	public:
		Decoder();
		virtual ~Decoder();

		virtual const wchar_t* GetFilePath() const;
		const struct WaveInfo& getWaveInfo() const;
		virtual int Open(const wchar_t* file);
		virtual int Open(const char* file);
		virtual int Read(BYTE* buffer, DWORD dwSizeToRead, DWORD* sizeReaded) = 0;
		virtual int Reset() = 0;
		virtual int Seek(float duration) = 0;
		virtual int Close() = 0;

		const AudioInfo* GetAudioInfo();
		DWORD GetWaveSize() const;
		DWORD GetCurrentPosition() const;
		DWORD CalcaulateWaveSize(float duration) const;
		float CalcalateTime(DWORD waveSize) const;
	protected:
		WaveInfo mWaveInfo;
		veda::String mFile;
		AudioInfo mAudioInfo;
		DWORD mCurrentPosition;
	};
}


