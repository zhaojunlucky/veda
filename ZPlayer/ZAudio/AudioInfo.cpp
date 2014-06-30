#include "stdafx.h"
#include "AudioInfo.h"

namespace audio
{
	AudioInfo::AudioInfo()
	{
		EMPTY = "";
	}


	AudioInfo::~AudioInfo()
	{
	}

	void AudioInfo::Put(const char* key, const char* value)
	{
		std::string sk = key;
		std::string sv = value;

		mAudioInfoMap[sk] = sv;
	}

	bool AudioInfo::ContainsKey(const char* key) const
	{
		return (mAudioInfoMap.find(std::string(key)) != mAudioInfoMap.end());
	}

	const char* AudioInfo::Get(const char* key) const
	{
		std::hash_map<std::string, std::string>::const_iterator it = mAudioInfoMap.find(std::string(key));
		if (it != mAudioInfoMap.end())
		{
			return (*it).second.c_str();
		}
		return EMPTY.c_str();
	}

	void AudioInfo::Clear()
	{
		mAudioInfoMap.clear();
	}

}

