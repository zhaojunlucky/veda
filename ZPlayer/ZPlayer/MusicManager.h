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
	void addMuiscToPlayList(MusicDetailsInfo& musicInfo,long plId);
	void addPlayList(const wchar_t* name);
	void removeMusicFormPL(MusicDetailsInfo& musicInfo, long plId);
private:
	std::hash_map<long, MusicDetailsInfo> mMusicMap;
};

