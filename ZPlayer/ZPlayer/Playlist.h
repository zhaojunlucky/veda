#pragma once
#include "Base.h"
#include <memory>
#include <hash_map>
using namespace std;
#include <Vector.h>

class Playlist
{
public:
	Playlist(const wchar_t* playlistName);
	Playlist(const wchar_t* playlistName, long id);
	const wchar_t* getPlaylistName() const;
	size_t getPlaylistSize() const;
	void addMusicInfos(veda::Vector<MusicInfoPtr>& musicInfos, bool removeExisting = true);
	bool addMusicInfo(shared_ptr<MusicInfo> musicInfo);
	const MusicInfo& getMusicInfo(size_t index) const;
	MusicInfo& getMusicInfo(size_t index);
	void remove(size_t index);
	void clear();
	void setName(const wchar_t* name);
	bool isModified() const;
	long getPlaylistId() const;
private:
	String mPlaylistName;
	Vector<shared_ptr<MusicInfo>> mPlaylist;
	long mId;
	bool mIsModified;
	hash_map<long, bool> mMap;
};