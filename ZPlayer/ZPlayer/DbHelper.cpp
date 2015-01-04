#include "DbHelper.h"
#include <FileUtil.h>
#include <SpecialFolder.h>
#include <string>
#include <hash_map>
#include "SQL.h"
#include <Datetime.h>


DbHelper::DbHelper()
{
	veda::SpecialFolder sf;
	mDbFile = veda::FileUtil::getSpecialFolderPath(sf.RoamingAppData)->c_str();
	mDbFile.append(L"\\ZPlayer\\data\\");
	if (!veda::FileUtil::directoryExists(mDbFile.c_str()))
	{
		veda::FileUtil::createDirectoryRecursive(mDbFile.c_str());
	}
	mDbFile.append(L"music.db");
	checkTables();
}


DbHelper::~DbHelper()
{
}

Sqlite3ConnectionPtr DbHelper::getConnection()
{
	auto connPtr = make_shared<Sqlite3Connection>(mDbFile.c_str());
	connPtr->open();
	return connPtr;
}
void DbHelper::returnConnection(Sqlite3ConnectionPtr& conn)
{
	conn->close();
	conn.reset();
}
void DbHelper::loadAllPlayList(Vector<shared_ptr<Playlist>> &arr)
{
	arr.clear();
	static wchar_t* PL_NAME_SQL = L"SELECT UUID,NAME FROM PLAYLIST";
	auto& conn = getConnection();

	Sqlite3StatementPtr stmt = conn->prepare(PL_NAME_SQL);
	Sqlite3ResultSetPtr rs = stmt->executeQuery();
	while (rs->hasNext())
	{
		arr.add(make_shared<Playlist>((const wchar_t*)rs->getText16(2),rs->getInteger(1)));
	}
	rs->close();
	stmt->close();
	for (auto& pl : arr)
	{
		loadPlaylistMusics(conn,pl);
	}
	returnConnection(conn);
}
void DbHelper::loadPlaylistMusics(Sqlite3ConnectionPtr& conn, shared_ptr<Playlist>& pl)
{
	static wchar_t* PL_MUSICS_SQL = L"SELECT a.UUID,a.FULL_PATH,a.IS_CUE,a.ARTIST,a.ALBUM,a.TITLE,a.START_TIME,a.END_TIME,a.LAST_MODIFIED_TIME,a.LAST_SIZE,b.DISPLAY_ORDER FROM MUSIC_META_DATA a JOIN PLAYLIST_MUSICS b ON a.UUID=b.MUSIC_ID AND b.PARENT_ID=? ORDER BY b.DISPLAY_ORDER";

	auto& stmt = conn->prepare(PL_MUSICS_SQL);
	stmt->bindInteger(1, pl->getPlaylistId());
	auto& rs = stmt->executeQuery();
	while (rs->hasNext())
	{
		auto& musicInfo = make_shared<MusicInfo>();
		
		musicInfo->id = rs->getInteger(1);
		musicInfo->fullPath = (const wchar_t*)rs->getText16(2);
		musicInfo->isCue = (1 == rs->getInteger(3));
		musicInfo->artist = (const wchar_t*)rs->getText16(4);
		musicInfo->album = (const wchar_t*)rs->getText16(5);
		musicInfo->title = (const wchar_t*)rs->getText16(6);
		musicInfo->start = rs->getDouble(7);
		musicInfo->end = rs->getDouble(8);
		//musicInfo->lastModifiedTime = rs->getInt64(9);
		//musicInfo->lastSize = rs->getInt64(10);
		musicInfo->order = rs->getDouble(11);
		musicInfo->isUpdated = false;
		pl->addMusicInfo(musicInfo);
	}
	rs->close();
	stmt->close();
}
void DbHelper::updatePlaylists(Vector<shared_ptr<Playlist>> &arr)
{
	auto& conn = getConnection();
	for (auto& pl : arr)
	{
		updatePlaylist(conn, pl);
	}
	returnConnection(conn);
}
void DbHelper::updatePlaylist(Sqlite3ConnectionPtr& conn, shared_ptr<Playlist>& pl)
{
	static wchar_t* UP_ORDER_SQL = L"UPDATE PLAYLIST_MUSICS SET DISPLAY_ORDER=? WHERE PARENT_ID=? AND MUSIC_ID = ?";
	if (pl->isModified())
	{
		size_t size = pl->getPlaylistSize();
		for (auto i = 0; i < size; i++)
		{
		
			MusicInfo& mi = pl->getMusicInfo(i);
			if (mi.isUpdated)
			{
				updateMusic(conn, mi);
				auto& stmt = conn->prepare(UP_ORDER_SQL);
				stmt->bindDouble(1, mi.order);
				stmt->bindInteger(2,pl->getPlaylistId());
				stmt->bindInteger(3, mi.id);
				stmt->executeUpdate();
				stmt->close();
				mi.isUpdated = false;
			}
			
		}
	}
}

void DbHelper::updatePlayMusicOrder(long pl, veda::Vector<MusicInfoPtr>& musics)
{
	static wchar_t* SQL = L"UPDATE PLAYLIST_MUSICS SET DISPLAY_ORDER=? WHERE PARENT_ID=? AND MUSIC_ID = ?";
	auto& conn = getConnection();
	conn->beginTransaction();
	for (auto& m : musics)
	{
		auto stmt = conn->prepare(SQL);
		stmt->bindDouble(1, m->order);
		stmt->bindInt64(2, pl);
		stmt->bindInt64(3, m->id);
		stmt->executeUpdate();
		stmt->close();
	}
	conn->commitTransaction();
	returnConnection(conn);
}
long DbHelper::addMusic(MusicInfo& musicInfo)
{
	auto& conn = getConnection();
	auto id = addMusic(conn, musicInfo);
	returnConnection(conn);
	return id;
}

long DbHelper::addMusic(Sqlite3ConnectionPtr& conn, MusicInfo& musicInfo)
{
	static wchar_t *INSERT_MUSIC_SQL = L"INSERT OR IGNORE INTO MUSIC_META_DATA(FULL_PATH,IS_CUE,ARTIST,ALBUM,TITLE,START_TIME,END_TIME,LAST_MODIFIED_TIME,LAST_SIZE) VALUES(?,?,?,?,?,?,?,?,?)";
	auto& stmt = conn->prepare(INSERT_MUSIC_SQL);
	stmt->bindText16(1, musicInfo.fullPath.c_str(), -1);
	stmt->bindInteger(2, musicInfo.isCue ? 1 : 0);
	stmt->bindText16(3, musicInfo.artist.c_str(), -1);
	stmt->bindText16(4, musicInfo.album.c_str(), -1);
	stmt->bindText16(5, musicInfo.title.c_str(), -1);
	stmt->bindDouble(6, musicInfo.start);
	stmt->bindDouble(7, musicInfo.end);
	stmt->bindInt64(8, 0);
	stmt->bindInt64(9, 0);
	stmt->executeUpdate();
	stmt->close();

	long id = conn->getLastInsertRowId();
	if (id == 0)
	{
		static wchar_t* MUSIC_QUERY = L"SELECT UUID FROM MUSIC_META_DATA WHERE FULL_PATH=? AND START_TIME = ? AND END_TIME = ?";
		auto& queryStmt = conn->prepare(MUSIC_QUERY);
		queryStmt->bindText16(1, musicInfo.fullPath.c_str(), -1);
		queryStmt->bindDouble(2, musicInfo.start);
		queryStmt->bindDouble(3, musicInfo.end);
		auto& rs = queryStmt->executeQuery();
		rs->hasNext();
		id = rs->getInt64(1);
		rs->close();
		queryStmt->close();
	}
	musicInfo.id = id;
	musicInfo.isUpdated = false;
	return id;
}
void DbHelper::addMusics(veda::Vector<MusicInfoPtr>& vec)
{
	auto& conn = getConnection();
	conn->beginTransaction();
	for (auto& m : vec)
	{
		m->id = addMusic(conn, *m.get());
	}
	conn->commitTransaction();
	returnConnection(conn);
}

void DbHelper::removeMusicFromPl(long pl, long mId)
{
	static wchar_t* SQL = L"DELETE FROM PLAYLIST_MUSICS WHERE PARENT_ID=? AND MUSIC_ID=?";
	auto& conn = getConnection();
	auto& stmt = conn->prepare(SQL);
	stmt->bindInteger(1, pl);
	stmt->bindInteger(2, mId);
	stmt->executeUpdate();
	stmt->close();
	returnConnection(conn);
}
void DbHelper::removeMusicFromDb(long mId)
{
	static wchar_t* SQL = L"DELETE FROM MUSIC_META_DATA WHERE UUID=?";
	auto& conn = getConnection();
	auto& stmt = conn->prepare(SQL);
	stmt->bindInteger(1, mId);
	stmt->executeUpdate();
	stmt->close();
	returnConnection(conn);
}
void DbHelper::updateMusic(Sqlite3ConnectionPtr& conn,const MusicInfo& musicInfo)
{
	static wchar_t *UPDATE_MUSIC_SQL = L"UPDATE MUSIC_META_DATA SET FULL_PATH=?,IS_CUE=?,ARTIST=?,ALBUM=?,TITLE=?,START_TIME=?,END_TIME=?,LAST_MODIFIED_TIME=?,LAST_SIZE=? WHERE UUID=?";
	auto& stmt = conn->prepare(UPDATE_MUSIC_SQL);
	stmt->bindText16(1, musicInfo.fullPath.c_str(), -1);
	stmt->bindInteger(2, musicInfo.isCue ? 1 : 0);
	stmt->bindText16(3, musicInfo.artist.c_str(), -1);
	stmt->bindText16(4, musicInfo.album.c_str(), -1);
	stmt->bindText16(5, musicInfo.title.c_str(), -1);
	stmt->bindDouble(6, musicInfo.start);
	stmt->bindDouble(7, musicInfo.end);
	stmt->bindInt64(8, 0);
	stmt->bindInt64(9, 0);
	stmt->bindInteger(10, musicInfo.id);
	stmt->executeUpdate();
	stmt->close();
}

long DbHelper::addPlaylist(const String& name)
{
	static wchar_t* INSERT_PL = L"INSERT INTO PLAYLIST([NAME],CREATE_TIME,LAST_MODIFIED_TIME) VALUES(?,?,?)";
	auto& conn = getConnection();
	veda::Datetime now;
	auto& stmt = conn->prepare(INSERT_PL);
	stmt->bindText16(1, name.c_str(), -1);
	stmt->bindInt64(2, now.getTime());
	stmt->bindInt64(3, now.getTime());
	stmt->executeUpdate();
	stmt->close();
	long id = conn->getLastInsertRowId();
	returnConnection(conn);
	return id;
}
void DbHelper::removePlaylist(long id)
{
	static wchar_t* DEL_PL_MUSICS_SQL = L"DELETE FROM PLAYLIST_MUSICS WHERE PARENT_ID=?";
	static wchar_t* DEL_PL_SQL = L"DELETE FROM PLAYLIST WHERE UUID=?";
	auto& conn = getConnection();
	auto& stmt = conn->prepare(DEL_PL_MUSICS_SQL);
	stmt->bindInteger(1, id);
	stmt->executeUpdate();
	stmt->close();
	
	
	stmt = conn->prepare(DEL_PL_SQL);
	stmt->bindInteger(1, id);
	stmt->executeUpdate();
	stmt->close();
	returnConnection(conn);
}

long DbHelper::queryMusic(const String& fullpath, int start, int end)
{
	long id = -1;
	static wchar_t* QUERY_SQL = L"SELECT UUID FROM MUSIC_META_DATA WHERE FULL_PATH =? AND START_TIME=? AND END_TIME=?";
	auto& conn = getConnection();
	auto& stmt = conn->prepare(QUERY_SQL);
	stmt->bindText16(1, fullpath.c_str(), -1);
	stmt->bindDouble(2, start);
	stmt->bindDouble(3, end);
	auto& rs = stmt->executeQuery();
	if (rs->hasNext())
	{
		id = rs->getInteger(1);
	}
	rs->close();
	stmt->close();
	returnConnection(conn);
	return id;
}

void DbHelper::checkTables()
{
	auto& conn = getConnection();

	static wchar_t* TABLE_QUERY = L"SELECT tbl_name FROM sqlite_master WHERE type = 'table'";
	auto& stmt = conn->prepare(TABLE_QUERY);
	auto& rs = stmt->executeQuery();
	std::hash_map<std::wstring, bool> map;
	while (rs->hasNext())
	{
		std::wstring table = (wchar_t*)rs->getText16(1);
		map[table] = true;
	}
	rs->close();
	stmt->close();

	if (map.find(L"MUSIC_META_DATA") == map.end())
	{
		auto& stmt = conn->prepare(MUSIC_META_DATA);
		stmt->executeUpdate();
		stmt->close();
		stmt = conn->prepare(MUSIC_INDEX);
		stmt->executeUpdate();
		stmt->close();
	}
	bool addDefault = false;
	if (map.find(L"PLAYLIST") == map.end())
	{
		auto& stmt = conn->prepare(PLAYLIST);
		stmt->executeUpdate();
		stmt->close();
		addDefault = true;
	}
	if (map.find(L"PLAYLIST_MUSICS") == map.end())
	{
		auto& stmt = conn->prepare(PLAYLIST_MUSICS);
		stmt->executeUpdate();
		stmt->close();
		stmt = conn->prepare(MUSIC_PL_INDEX);
		stmt->executeUpdate();
		stmt->close();
	}
	if (map.find(L"PLAY_HISTORY") == map.end())
	{
		auto& stmt = conn->prepare(PLAY_HISTORY);
		stmt->executeUpdate();
		stmt->close();
	}
	returnConnection(conn);
	if (addDefault)
	{
		String defaultPl = L"Default";
		addPlaylist(defaultPl);
	}
}

void DbHelper::addMusicToPl(long pl, long musicId, float order)
{
	auto& conn = getConnection();
	addMusicToPl(conn, pl, musicId, order);
	returnConnection(conn);
}
void DbHelper::addMusicToPl(Sqlite3ConnectionPtr& conn, long pl, long musicId, float order)
{
	static wchar_t* INSERT_SQL = L"INSERT OR REPLACE INTO PLAYLIST_MUSICS(PARENT_ID,MUSIC_ID,DISPLAY_ORDER) VALUES(?,?,?)";
	auto& stmt = conn->prepare(INSERT_SQL);
	stmt->bindInt64(1, pl);
	stmt->bindInt64(2, musicId);
	stmt->bindDouble(3, order);
	stmt->executeUpdate();
	stmt->close();
}
void DbHelper::addMusicsToPl(long pl, veda::Vector<std::pair<long, float>>& musicOrder)
{
	auto& conn = getConnection();
	for (auto& p : musicOrder)
	{
		addMusicToPl(conn, pl, p.first, p.second);
	}
	returnConnection(conn);
}