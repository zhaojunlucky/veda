#pragma once
#include "MediaModel.h"
#include "MusicListModel.h"
#include "PlayListModel.h"
namespace zpl
{
	class DataProvider
	{
	public:
		DataProvider();
		~DataProvider();

		void SavePlayList(const vector<struct PlayListModel>& playListData);
		void SaveMusicList(const string& playListName, vector<MediaModel>& mediaList);
		void LoadPlayList(vector<struct PlayListModel>& playListData);
		void LoadMusicList(const string& playListName, MusicListModel& pl);

	};

}

