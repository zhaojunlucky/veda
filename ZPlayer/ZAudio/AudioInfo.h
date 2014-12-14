#pragma once
#include <string>
#include <hash_map>

namespace audio
{
	class AudioInfo
	{
	public:
		__declspec(dllexport) AudioInfo();
		__declspec(dllexport) virtual ~AudioInfo();

		__declspec(dllexport) void Put(const char* key, const char* value);
		__declspec(dllexport) bool ContainsKey(const char* key) const;

		__declspec(dllexport) const char* Get(const char* key) const;

		__declspec(dllexport) void Clear();
	private:
		std::hash_map<std::string, std::string> mAudioInfoMap;
		std::string EMPTY;
	};
}


