#include "DbModel.h"


DbModel::DbModel()
{
	mDbFile = "E:\\Documents\\Projects\\GitHub\\veda\\ZPlayer\\x64\\Debug\\data\\music.db";
}


DbModel::~DbModel()
{
}



long DbModel::addMusic(MusicDetailsInfo& music)
{
	static char* sql = "INSERT INTO MUSIC_META_DATA(FULL_PATH,ARTIST,ALBUM,TITLE,IS_CUE,START_TIME,END_TIME,LAST_MODIFIED_TIME,LAST_SIZE) VALUES(?,?,?,?,?,?,?,?,?)";
	Sqlite3ConnectionPtr conn = getConnection();
	Sqlite3StatementPtr stmt = conn->prepare(sql);
	stmt->bindText16(1, music.fullPath.c_str(), music.fullPath.getSize(), SQLITE_STATIC);
	stmt->bindText16(2, music.artist.c_str(), music.artist.getSize(), SQLITE_STATIC);
	stmt->bindText16(3, music.alblum.c_str(), music.alblum.getSize(), SQLITE_STATIC);
	stmt->bindText16(4, music.title.c_str(), music.title.getSize(), SQLITE_STATIC);
	stmt->bindInt64(5, music.isCue?1:0);
	stmt->bindInt64(6, music.start);
	stmt->bindInt64(7, music.end);
	stmt->bindInt64(8, music.lastModifiedTime);
	stmt->bindInt64(9, music.lastSize);
	stmt->executeUpdate();
	stmt->close();
	long id = conn->getLastInsertRowId();
	conn->close();
	return id;
}
void DbModel::updateMusic(MusicDetailsInfo& music)
{
	static char* sql = "UPDATE MUSIC_META_DATA SET ARTIST=?, ALBUM=?,TITLE=?,START_TIME=?,END_TIME=?,LAST_MODIFIED_TIME=?,LAST_SIZE=?";
	Sqlite3ConnectionPtr conn = getConnection();
	Sqlite3StatementPtr stmt = conn->prepare(sql);
	stmt->bindText16(1, music.artist.c_str(), music.artist.getSize(), SQLITE_STATIC);
	stmt->bindText16(2, music.alblum.c_str(), music.alblum.getSize(), SQLITE_STATIC);
	stmt->bindText16(3, music.title.c_str(), music.title.getSize(), SQLITE_STATIC);
	stmt->bindInt64(4, music.start);
	stmt->bindInt64(5, music.end);
	stmt->bindInt64(6, music.lastModifiedTime);
	stmt->bindInt64(7, music.lastSize);
	stmt->executeUpdate();
	stmt->close();
	conn->close();
}
void DbModel::deleteMusic(MusicDetailsInfo& music)
{
	deleteMusic(music.id);
}
void DbModel::deleteMusic(long musicId)
{
	static char* sql = "DELETE FROM MUSIC_META_DATA WHERE UUID=?";
	Sqlite3ConnectionPtr conn = getConnection();
	Sqlite3StatementPtr stmt = conn->prepare(sql);
	stmt->bindInt64(1, musicId);
	stmt->executeUpdate();
	stmt->close();
	conn->close();
}
long DbModel::addPlaylist(const wchar_t* name)
{
	static char* sql = "INSERT INTO PLAYLIST VALUES(?,?,?)";
	Sqlite3ConnectionPtr conn = getConnection();
	Sqlite3StatementPtr stmt = conn->prepare(sql);
	Datetime d;

	stmt->bindText16(1, name, wcslen(name), SQLITE_STATIC);
	stmt->bindInt64(2, d.getTime());
	stmt->bindInt64(3, d.getTime());
	stmt->executeUpdate();
	stmt->close();
	conn->close();
	return 0;
}
void DbModel::addMusicForPlaylist(long pl, long musicId)
{
	static char* sql = "INSERT INTO PLAYLIST_MUSICS VALUES(?,?)";
	Sqlite3ConnectionPtr conn = getConnection();
	Sqlite3StatementPtr stmt = conn->prepare(sql);

	stmt->bindInt64(1, pl);
	stmt->bindInt64(2, musicId);
	stmt->executeUpdate();
	stmt->close();
	conn->close();
}
void DbModel::deletePlaylistMusic(long pl, long musicId)
{
	static char* sql = "DELETE FROM PLAYLIST_MUSICS WHERE PARENT_ID=? AND MUSIC_ID=?";
	Sqlite3ConnectionPtr conn = getConnection();
	Sqlite3StatementPtr stmt = conn->prepare(sql);

	stmt->bindInt64(1, pl);
	stmt->bindInt64(2, musicId);
	stmt->executeUpdate();
	stmt->close();
	conn->close();
}

Sqlite3ConnectionPtr DbModel::getConnection()
{
	Sqlite3ConnectionPtr conn(make_shared<Sqlite3Connection>(mDbFile.c_str()));
	conn->open();
	return conn;
}

void DbModel::returnConnection(Sqlite3ConnectionPtr& conn)
{
	conn->close();
}