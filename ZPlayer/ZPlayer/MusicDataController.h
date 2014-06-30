#pragma once
#include "MusicListModel.h"
#include "MediaModel.h"
#include "PlayListModel.h"
#include "DataProvider.h"

namespace zpl
{
	class MusicDataController
	{
	public:
		MusicDataController();
		~MusicDataController();

		void LoadDataFromDb();

		size_t PlayListCount() const;
		const struct PlayListModel& GetPlayListData(size_t index) const;

		const MusicListModel& GetMusicList(const string& name) const;

		void RemovePlayList(const string& name);
		void ChangePlayListOrder(const string& name, size_t newOrder);
		void RemoveMusic(const string& name, size_t index);
		void ClearMusics(const string& name);
		void LoadMusicList(const string& name);
	private:
		vector<struct PlayListModel> mPlayListData;
		hash_map<string, std::shared_ptr<MusicListModel>> mMusicLists;
		DataProvider mDP;
	};

}

