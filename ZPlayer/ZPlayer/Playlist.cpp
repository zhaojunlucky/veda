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
void Playlist::addMusicInfo(shared_ptr<MusicInfo> musicInfo)
{
	mPlaylist.add(musicInfo);
	mIsModified = true;
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
	mPlaylist.removeAt(index);
	mIsModified = true;
}
void Playlist::clear()
{
	mPlaylist.clear();
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