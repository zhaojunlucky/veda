#pragma once
#include <ZString.h>
using namespace veda;
#include <hash_map>

struct MusicDetailsInfo
{
	String fileName;
	String artist;
	String alblum;
	float totalSeconds;
};
class MusicManager
{
public:
	MusicManager();
	~MusicManager();
	const MusicDetailsInfo& getMusicDetail(long musicId);
private:
	std::hash_map<long, MusicDetailsInfo> mMusicMap;
};

