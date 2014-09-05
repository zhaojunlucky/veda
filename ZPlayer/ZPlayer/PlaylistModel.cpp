#include "PlaylistModel.h"


Playlist::Playlist(const wchar_t* name)
	:mPlaylistName(name), id(-1)
{

}

Playlist::Playlist(const wchar_t* name, int id)
	:mPlaylistName(name), id(-1)
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
}
const MusicInfo& Playlist::getMusicInfo(size_t index) const
{
	return *mPlaylist[index].get();
}
void Playlist::remove(size_t index)
{
	mPlaylist.removeAt(index);
}
void Playlist::clear()
{
	mPlaylist.clear();
}
void Playlist::setName(const wchar_t* name)
{
	mPlaylistName = name;
}
int Playlist::getId() const
{
	return id;
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