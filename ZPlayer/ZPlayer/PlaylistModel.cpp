#include "PlaylistModel.h"
#include <taglib/fileref.h>
#include "DbHelper.h"


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

void PlaylistModel::loadData()
{
	DbHelper db;// = DbHelper::getInstance();
	db.loadAllPlayList(mPlaylists);
}