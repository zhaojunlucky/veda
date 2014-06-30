#pragma once
#include <string>
#include <hash_map>

namespace audio
{
	class __declspec(dllexport) AudioInfo
	{
	public:
		AudioInfo();
		virtual ~AudioInfo();

		void Put(const char* key, const char* value);
		bool ContainsKey(const char* key) const;

		const char* Get(const char* key) const;

		void Clear();
	private:
		std::hash_map<std::string, std::string> mAudioInfoMap;
		std::string EMPTY;
	};
}


