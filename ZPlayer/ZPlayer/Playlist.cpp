#include "Playlist.h"
Playlist::Playlist(const wchar_t* playlistName)
	:mPlaylistName(playlistName), mId(-1), mIsModified(false)
{

}

Playlist::Playlist(const wchar_t* playlistName, long id)
	: mPlaylistName(playlistName), mId(id), mIsModified(false)
{

}

const wchar_t* Playlist::getPlaylistName() const
{
	return mPlaylistName.c_str();
}
size_t Playlist::getPlaylistSize() const
{
	return mPlaylist.getLength();
}
bool Playlist::addMusicInfo(shared_ptr<MusicInfo> musicInfo)
{
	if (mMap.find(musicInfo->id) == mMap.end())
	{
		mPlaylist.add(musicInfo);
		mMap[musicInfo->id] = true;
		mIsModified = true;
		return true;
	}
	return false;
}

void Playlist::addMusicInfos(veda::Vector<MusicInfoPtr>& musicInfos, bool removeExisting)
{
	veda::Vector<size_t> removedIndexs;
	for (size_t i = 0; i < musicInfos.getLength(); i++)
	{
		auto& m = musicInfos[i];
		if (!addMusicInfo(m))
		{
			removedIndexs.add(i);
		}
	}
	if (removeExisting)
	{
		for (auto& it = removedIndexs.cbegin(); it != removedIndexs.cend(); ++it)
		{
			musicInfos.removeAt(*it);
		}
	}
	
}

const MusicInfo& Playlist::getMusicInfo(size_t index) const
{
	return *mPlaylist[index].get();
}
MusicInfo& Playlist::getMusicInfo(size_t index)
{
	return *mPlaylist[index].get();
}
void Playlist::remove(size_t index)
{
	auto it = mMap.find(mPlaylist[index]->id);
	if (it != mMap.end())
	{
		mMap.erase(it);
	}
	mPlaylist.removeAt(index);
	mIsModified = true;
}
void Playlist::clear()
{
	mPlaylist.clear();
	mMap.clear();
}
void Playlist::setName(const wchar_t* name)
{
	mPlaylistName = name;
	mIsModified = true;
}



bool Playlist::isModified() const
{
	return mIsModified;
}

long Playlist::getPlaylistId() const
{
	return mId;
}