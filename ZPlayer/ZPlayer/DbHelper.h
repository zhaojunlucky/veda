#pragma once
#include <sqlite.h>
using namespace sqlite3;
#include <ZString.h>
#include <Vector.h>

using namespace veda;
#include "Playlist.h"
class DbHelper
{
public:
	DbHelper();
	~DbHelper();
	//static DbHelper* getInstance()
	//{
	//	if (instance == NULL)
	//	{
	//		static DbHelper dbHelper;
	//		instance = &dbHelper;
	//	}
	//	return instance;
	//}


	Sqlite3ConnectionPtr getConnection();
	void returnConnection(Sqlite3ConnectionPtr& conn);
	void loadAllPlayList(Vector<shared_ptr<Playlist>> &arr);
	void loadPlaylistMusics(Sqlite3ConnectionPtr& conn, shared_ptr<Playlist>& pl);
	void updatePlaylists(Vector<shared_ptr<Playlist>> &arr);
	void updatePlaylist(Sqlite3ConnectionPtr& conn, shared_ptr<Playlist>& pl);
	long addMusic(MusicInfo& musicInfo);
	void removeMusicFromPl(long pl, long mId);
	void removeMusicFromDb(long mId);
	void updateMusic(Sqlite3ConnectionPtr& conn, const MusicInfo& musicInfo);
	long addPlaylist(const String& name);
	void removePlaylist(long id);
	long queryMusic(const String& fullpath, bool isCue, int start, int end);
private:
	static DbHelper* instance;
	String mDbFile;
};

