#pragma once

#define SQL_STR static wchar_t*

SQL_STR MUSIC_META_DATA = L"CREATE TABLE MUSIC_META_DATA (\
					   \"UUID\"  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \
					   \"FULL_PATH\"  TEXT NOT NULL, \
					   \"IS_CUE\"  INTEGER DEFAULT 0, \
					   \"ARTIST\"  TEXT DEFAULT \"\", \
					   \"ALBUM\"  TEXT DEFAULT \"\", \
					   \"TITLE\"  TEXT DEFAULT \"\", \
					   \"START_TIME\"  REAL DEFAULT 0, \
					   \"END_TIME\"  REAL DEFAULT - 1, \
					   \"LAST_MODIFIED_TIME\"  INTEGER, \
					   \"LAST_SIZE\"  INTEGER DEFAULT 0)";

SQL_STR MUSIC_INDEX = L"CREATE UNIQUE INDEX musicIndex \
ON \"main\".\"MUSIC_META_DATA\" (\"FULL_PATH\" ASC, \"START_TIME\" ASC, \"END_TIME\" ASC)";

SQL_STR PLAYLIST = L"CREATE TABLE PLAYLIST (\
								\"UUID\"  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \
								\"NAME\"  TEXT NOT NULL, \
								\"CREATE_TIME\"  INTEGER, \
								\"LAST_MODIFIED_TIME\"  INTEGER)";
SQL_STR PLAYLIST_MUSICS = L"CREATE TABLE PLAYLIST_MUSICS (\
						   \"UUID\"  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \
						   \"PARENT_ID\"  INTEGER NOT NULL, \
						   \"MUSIC_ID\"  INTEGER NOT NULL, \
						   \"DISPLAY_ORDER\"  REAL DEFAULT 0, \
						   	CONSTRAINT \"fkey0\" FOREIGN KEY(\"PARENT_ID\") REFERENCES \"PLAYLIST\" (\"UUID\"), \
							CONSTRAINT \"fkey1\" FOREIGN KEY(\"MUSIC_ID\") REFERENCES \"MUSIC_META_DATA\" (\"UUID\"))";

SQL_STR PLAY_HISTORY = L"CREATE TABLE PLAY_HISTORY (\
						\"UUID\"  INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,\
						\"MUSIC_ID\"  INTEGER,\
						\"PLAY_COUNT\"  INTEGER)";
