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
	//stmt->bindText(1, music.fileName, str.getSize(), SQLITE_STATIC);
	//stmt->bindText(2, f.tag()->artist().toCString(), f.tag()->artist().length(), SQLITE_STATIC);
	//stmt->bindText(3, f.tag()->album().toCString(), f.tag()->album().length(), SQLITE_STATIC);
	//stmt->bindText(4, f.tag()->title().toCString(), f.tag()->title().length(), SQLITE_STATIC);
	//stmt->bindInt64(5, 0);
	//stmt->bindInt64(6, f.audioProperties()->length());
	//stmt->bindInt64(7, fi.lastModifiedTime);
	//stmt->bindInt64(8, fi.fileSize);
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