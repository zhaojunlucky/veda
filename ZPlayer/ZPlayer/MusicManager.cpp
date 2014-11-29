#include "MusicManager.h"


MusicManager::MusicManager()
{
}


MusicManager::~MusicManager()
{
}

const MusicDetailsInfo& MusicManager::getMusicDetail(long musicId)
{
	return mMusicMap.find(musicId)->second;
}
