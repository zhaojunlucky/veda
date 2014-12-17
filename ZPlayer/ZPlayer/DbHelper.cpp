#include "DbHelper.h"


DbHelper::DbHelper()
{
	mDbFile = L"E:\\Documents\\Projects\\GitHub\\veda\\ZPlayer\\x64\\Debug\\data\\music.db";
}


DbHelper::~DbHelper()
{
}

Sqlite3ConnectionPtr& DbHelper::getConnection()
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
	static wchar_t* PL_MUSICS_SQL = L"SELECT a.UUID,a.FULL_PATH,a.IS_CUE,a.ARTIST,a.ALBUM,a.TITLE,a.START_TIME,a.END_TIME,a.LAST_MODIFIED_TIME,a.LAST_SIZE,b.ORDER FROM MUSIC_META_DATA a JOIN PLAYLIST_MUSICS b ON a.UUID=b.MUSIC_ID AND b.PARENT_ID=? ORDER BY b.ORDER";

	auto& stmt = conn->prepare(PL_MUSICS_SQL);
	stmt->bindInteger(1, pl->getPlaylistId());
	auto& rs = stmt->executeQuery();
	while (rs->hasNext())
	{
		auto& musicInfo = make_shared<MusicInfo>();
		
		musicInfo->id = rs->getInteger(1);
		musicInfo->fullPath = (const wchar_t*)rs->getText16(2);
		musicInfo->isCue = (1 == rs->getInteger(3));
		musicInfo->artist = (const wchar_t*)rs->getText16(3);
		musicInfo->album = (const wchar_t*)rs->getText16(4);
		musicInfo->title = (const wchar_t*)rs->getText16(5);
		musicInfo->start = rs->getDouble(6);
		musicInfo->end = rs->getDouble(7);
		//musicInfo->lastModifiedTime = rs->getInt64(8);
		//musicInfo->lastSize = rs->getInt64(9);
		musicInfo->order = rs->getDouble(10);
		musicInfo->isUpdated = false;
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
	static wchar_t* UP_ORDER_SQL = L"UPDATE PLAYLIST_MUSICS SET ORDER=? WHERE PARENT_ID=? AND MUSIC_ID = ?";
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
long DbHelper::addMusic(MusicInfo& musicInfo)
{
	static wchar_t *INSERT_MUSIC_SQL = L"INSERT INTO MUSIC_META_DATA(FULL_PATH,IS_CUE,ARTIST,ALBUM,TITLE,START_TIME,END_TIME,LAST_MODIFIED_TIME,LAST_SIZE) VALUES(?,?,?,?,?,?,?,?,?)";
	auto& conn = getConnection();
	auto& stmt = conn->prepare(INSERT_MUSIC_SQL);
	stmt->bindText16(1, musicInfo.fullPath.c_str(), musicInfo.fullPath.getSize());
	stmt->bindInteger(2, musicInfo.isCue?1:0);
	stmt->bindText16(3, musicInfo.artist.c_str(), musicInfo.artist.getSize());
	stmt->bindText16(4, musicInfo.album.c_str(), musicInfo.album.getSize());
	stmt->bindText16(5, musicInfo.title.c_str(), musicInfo.title.getSize());
	stmt->bindDouble(6, musicInfo.start);
	stmt->bindDouble(7, musicInfo.end);
	stmt->bindInt64(8, 0);
	stmt->bindInt64(9, 0);
	stmt->executeUpdate();
	stmt->close();

	long id = conn->getLastInsertRowId();
	returnConnection(conn);
	return id;
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
	stmt->bindText16(1, musicInfo.fullPath.c_str(), musicInfo.fullPath.getSize());
	stmt->bindInteger(2, musicInfo.isCue ? 1 : 0);
	stmt->bindText16(3, musicInfo.artist.c_str(), musicInfo.artist.getSize());
	stmt->bindText16(4, musicInfo.album.c_str(), musicInfo.album.getSize());
	stmt->bindText16(5, musicInfo.title.c_str(), musicInfo.title.getSize());
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
	static wchar_t* INSERT_PL = L"INSERT INTO PLAYLIST(NAME,CREATE_TIME,LAST_MODIFIED_TIME)";
	auto& conn = getConnection();
	auto& stmt = conn->prepare(INSERT_PL);
	stmt->bindText16(1, name.c_str(), name.getSize());
	stmt->bindInt64(2, 0);
	stmt->bindInt64(3, 0);
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

long DbHelper::queryMusic(const String& fullpath, bool isCue, int start, int end)
{
	long id = -1;
	static wchar_t* QUERY_SQL = L"SELECT UUID FROM MUSIC_META_DATA WHERE FULL_PATH =? AND IS_CUE=? AND START_TIME=? AND END_TIME=?";
	auto& conn = getConnection();
	auto& stmt = conn->prepare(QUERY_SQL);
	stmt->bindText16(1, fullpath.c_str(), fullpath.getSize());
	stmt->bindInteger(2, isCue?1:0);
	stmt->bindDouble(3, start);
	stmt->bindDouble(4, end);
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