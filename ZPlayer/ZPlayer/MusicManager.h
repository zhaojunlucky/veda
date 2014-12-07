#pragma once

#include <hash_map>
#include <time.h>
#include "Base.h"

class MusicManager
{
public:
	MusicManager();
	~MusicManager();
	const MusicDetailsInfo& getMusicDetail(long musicId);
private:
	std::hash_map<long, MusicDetailsInfo> mMusicMap;
};

