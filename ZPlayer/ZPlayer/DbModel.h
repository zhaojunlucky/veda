#pragma once
#include "Base.h"
#include <sqlite.h>
using namespace sqlite3;
#include <Datetime.h>

const char* PLAYLIST_INSRT_SQL = "INSERT INTO PLAYLIST(NAME,CREATE_TIME,LAST_MODIFIED_TIME) VALUES(?,?,?)";
const char* MUSIC_INSERT_SQL = "INSERT INTO MUSIC_META_DATA(FULL_PATH,IS_CUE,ARTIST,ALBUM,TITLE,START_TIME,END_TIME,LAST_MODIFIED_TIME,LAST_SIZE) VALUES(?,?,?,?,?,?,?,?,?)";
const char* ADD_MUSIC_TO_PLAYLIST = "INSERT INTO PLAYLIST_MUSICS(PARENT_ID,MUSIC_ID) VALUES(?,?)";

class DbModel
{
public:
	~DbModel();
	//static DbModel* getInstance();
	long addMusic(MusicDetailsInfo& music);
	void updateMusic(MusicDetailsInfo& music);
	void deleteMusic(MusicDetailsInfo& music);
	void deleteMusic(long musicId);
	long addPlaylist(const char* name);
	void addMusicForPlaylist(long pl, long musicId);
	void deletePlaylistMusic(long pl, long musicId);
	Sqlite3ConnectionPtr getConnection();
	void returnConnection(Sqlite3ConnectionPtr& conn);
private:
	DbModel();
private:
	AString mDbFile;
	static DbModel* instance;
};

