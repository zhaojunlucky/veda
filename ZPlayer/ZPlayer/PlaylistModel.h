#pragma once
#include <ZString.h>
#include <Vector.h>
#include <BufferedFileReader.h>
using namespace veda;
#include <memory>
using namespace std;


#include "Base.h"
#include "ZPLException.h"
#include "Playlist.h"

class PlaylistModel
{
public:
	PlaylistModel();
	~PlaylistModel();
	size_t getPlaylistCount() const;
	Playlist* getPlaylist(size_t index);
	Playlist* getPlaylist(const wchar_t* PlaylistName);
	void addPlaylist(shared_ptr<Playlist> Playlist);
	void remove(const wchar_t* PlaylistName);
protected:
	size_t findIndexByName(const wchar_t* PlaylistName) const;
private:
	Vector<shared_ptr<Playlist>> mPlaylists;
	Vector<String> mRemovedPlaylist;
};

