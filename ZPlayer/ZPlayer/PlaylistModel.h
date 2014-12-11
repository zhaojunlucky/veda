#pragma once
#include <ZString.h>
#include <Vector.h>
#include <BufferedFileReader.h>
using namespace veda;
#include <memory>
using namespace std;


#include "Base.h"
#include "ZPLException.h"

class Playlist
{
public:
	Playlist(const wchar_t* filePath);
	const wchar_t* getPlaylistName() const;
	size_t getPlaylistSize() const;
	void addMusicInfo(shared_ptr<MusicInfo> musicInfo);
	const MusicInfo& getMusicInfo(size_t index) const;
	void remove(size_t index);
	void clear();
	void setName(const wchar_t* name);
	bool isModified() const;

	void load();
	void save();
private:
	String mFilePath;
	String mPlaylistName;
	Vector<shared_ptr<MusicInfo>> mPlaylist;
	bool mIsModified;
};
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

