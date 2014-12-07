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