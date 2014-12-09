#pragma once
#include "Base.h"
#include <sqlite.h>
using namespace sqlite3;
#include <Datetime.h>

class DbModel
{
public:
	~DbModel();
	DbModel* DbModel::getInstance()
	{
		if (instance == 0)
		{
			static DbModel dbModel;
			instance = &dbModel;
		}
		return instance;
	}
	long addMusic(MusicDetailsInfo& music);
	void updateMusic(MusicDetailsInfo& music);
	void deleteMusic(MusicDetailsInfo& music);
	void deleteMusic(long musicId);
	long addPlaylist(const wchar_t* name);
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

