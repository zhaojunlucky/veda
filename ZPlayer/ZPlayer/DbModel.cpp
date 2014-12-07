#include "DbModel.h"


DbModel::DbModel()
{
	mDbFile = "E:\\Documents\\Projects\\GitHub\\veda\\ZPlayer\\x64\\Debug\\data\\music.db";
}


DbModel::~DbModel()
{
}

DbModel* DbModel::getInstance()
{
	if (instance == 0)
	{
		static DbModel dbModel;
		instance = &dbModel;
	}
	return instance;
}

long DbModel::addMusic(MusicDetailsInfo& music)
{
	Sqlite3ConnectionPtr conn = getConnection();
	Sqlite3StatementPtr stmt = conn->prepare(MUSIC_INSERT_SQL);
	stmt->bindText16(1, music.fullPath.c_str(), music.fullPath.getSize(), SQLITE_STATIC);
	stmt->bindText16(2, music.artist.c_str(), music.artist.getSize(), SQLITE_STATIC);
	stmt->bindText16(3, music.alblum.c_str(), music.alblum.getSize(), SQLITE_STATIC);
	stmt->bindText16(4, music.title.c_str(), music.title.getSize(), SQLITE_STATIC);
	stmt->bindInt64(5, music.isCue?1:0);
	stmt->bindInt64(6, music.end - music.start);
	stmt->bindInt64(7, music.lastModifiedTime);
	stmt->bindInt64(8, music.lastSize);
	stmt->executeUpdate();
	stmt->close();
	conn->close();
}
void DbModel::updateMusic(MusicDetailsInfo& music)
{

}
void DbModel::deleteMusic(MusicDetailsInfo& music)
{

}
void DbModel::deleteMusic(long musicId)
{

}
long DbModel::addPlaylist(const char* name)
{

}
void DbModel::addMusicForPlaylist(long pl, long musicId)
{

}
void DbModel::deletePlaylistMusic(long pl, long musicId)
{

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