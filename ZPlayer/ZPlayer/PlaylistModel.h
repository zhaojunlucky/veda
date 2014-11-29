#pragma once
#include <ZString.h>
#include <Vector.h>
using namespace veda;
#include <memory>
using namespace std;
struct MusicInfo
{
	long musicId;
};
class Playlist
{
public:
	Playlist(const wchar_t* name);
	Playlist(const wchar_t* name, int id);
	const wchar_t* getPlaylistName() const;
	size_t getPlaylistSize() const;
	void addMusicInfo(shared_ptr<MusicInfo> musicInfo);
	void addWithoutModify(shared_ptr<MusicInfo> musicInfo);
	const MusicInfo& getMusicInfo(size_t index) const;
	void remove(size_t index);
	void clear();
	void setName(const wchar_t* name);
	int getId() const;
	bool isModified() const;
private:
	String mPlaylistName;
	int id;
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

