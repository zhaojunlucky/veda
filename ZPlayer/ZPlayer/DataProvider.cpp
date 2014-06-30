#include "DataProvider.h"

namespace zpl
{
	DataProvider::DataProvider()
	{
	}


	DataProvider::~DataProvider()
	{
	}

	void DataProvider::SavePlayList(const vector<struct PlayListModel>& playListData)
	{

	}
	void DataProvider::SaveMusicList(const string& playListName, vector<MediaModel>& mediaList)
	{

	}
	void DataProvider::LoadPlayList(vector<struct PlayListModel>& playListData)
	{
		// for testing fakelist1, fakelist2
		playListData.push_back(PlayListModel("1", "fakelist1"));
		playListData.push_back(PlayListModel("2", "fakelist2"));
	}
	void DataProvider::LoadMusicList(const string& playListName, MusicListModel& pl)
	{
		MediaModel m1;
		m1.af = audio::AudioFormat::Ape;
		m1.file = "jay.ape";
		m1.title = "jay";
		m1.alblum = "ddd";
		MediaModel m2 = m1;
		m2.file = "fei.ape";
		m2.title = "fei";
		pl.AddMedia(m1);
		pl.AddMedia(m2);
	}

}
