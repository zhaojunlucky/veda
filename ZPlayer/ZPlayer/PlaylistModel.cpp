#include "PlaylistModel.h"


Playlist::Playlist(const wchar_t* name)
	:mPlaylistName(name), id(-1), mIsModified(false)
{

}

Playlist::Playlist(const wchar_t* name, int id)
	: mPlaylistName(name), id(-1), mIsModified(false)
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

void Playlist::addWithoutModify(shared_ptr<MusicInfo> musicInfo)
{
	mPlaylist.add(musicInfo);
	mIsModified = true;
}
const MusicInfo& Playlist::getMusicInfo(size_t index) const
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
int Playlist::getId() const
{
	return id;
}

bool Playlist::isModified() const
{
	return mIsModified;
}

PlaylistModel::PlaylistModel()
{

}
PlaylistModel::~PlaylistModel()
{

}
size_t PlaylistModel::getPlaylistCount() const
{
	return mPlaylists.getLength();
}
Playlist* PlaylistModel::getPlaylist(size_t index)
{
	return mPlaylists.at(index).get();
}
Playlist* PlaylistModel::getPlaylist(const wchar_t* PlaylistName)
{
	return getPlaylist(findIndexByName(PlaylistName));
}
void PlaylistModel::addPlaylist(shared_ptr<Playlist> Playlist)
{
	mPlaylists.add(Playlist);
}
void PlaylistModel::remove(const wchar_t* PlaylistName)
{
	mPlaylists.removeAt(findIndexByName(PlaylistName));
	mRemovedPlaylist.add(std::move(String(PlaylistName)));
}
size_t PlaylistModel::findIndexByName(const wchar_t* PlaylistName) const
{
	for (size_t i = 0; i < mPlaylists.getLength(); ++i)
	{
		if (wcscmp(mPlaylists[i]->getPlaylistName(), PlaylistName) == 0)
		{
			return i;
		}
	}
	throw "playlist name is not found";
}