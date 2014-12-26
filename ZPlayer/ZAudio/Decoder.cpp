#include "stdafx.h"
#include "Decoder.h"
#include <string.h>
#include <ZString.h>

namespace audio
{
	Decoder::Decoder()
	{
		memset(&mWaveInfo, 0, sizeof(mWaveInfo));
		mCurrentPosition = 0;
	}


	Decoder::~Decoder()
	{
	}

	const wchar_t* Decoder::GetFilePath() const
	{
		return mFile.c_str();
	}
	const WaveInfo& Decoder::getWaveInfo() const
	{
		return mWaveInfo;
	}

	int Decoder::Open(const wchar_t* file)
	{
		mFile = file;
		mCurrentPosition = 0;
		return 0;
	}

	int Decoder::Open(const char* file)
	{
		veda::WString tmp;
		tmp.from(file, strlen(file));
		return Open(tmp.c_str());
	}

	DWORD Decoder::GetWaveSize() const
	{
		return mWaveInfo.waveSize;
	}

	DWORD Decoder::GetCurrentPosition() const
	{
		return mCurrentPosition;
	}

	DWORD Decoder::CalcaulateWaveSize(float duration) const
	{
		return 0 == mWaveInfo.durationTime ? 0 : (DWORD)((float)mWaveInfo.waveSize * duration / mWaveInfo.durationTime);
	}

	float Decoder::CalcalateTime(DWORD waveSize) const
	{
		return 0 == waveSize ? 0 : (float)((double)waveSize * mWaveInfo.durationTime / (double)mWaveInfo.waveSize);
	}
}

