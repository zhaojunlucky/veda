#include "MusicDataController.h"

namespace zpl
{
	MusicDataController::MusicDataController()
	{
	}


	MusicDataController::~MusicDataController()
	{
	}

	void MusicDataController::LoadDataFromDb()
	{
		mDP.LoadPlayList(mPlayListData);
		for (size_t i = 0; i < mPlayListData.size(); i++)
		{
			LoadMusicList(mPlayListData[i].name);
		}
		// load top 3 play list
		LoadMusicList("Temp");
		LoadMusicList("Most Popular");
		LoadMusicList("History");
	}

	void MusicDataController::LoadMusicList(const string& name)
	{
		std::shared_ptr<MusicListModel> ptr(new MusicListModel);
		mDP.LoadMusicList(name, *ptr.get());
		mMusicLists[name] = ptr;
	}

	size_t MusicDataController::PlayListCount() const
	{
		return mPlayListData.size();
	}
	const struct PlayListModel& MusicDataController::GetPlayListData(size_t index) const
	{
		return mPlayListData[index];
	}

	const MusicListModel& MusicDataController::GetMusicList(const string& name) const
	{
		return *mMusicLists.find(name)->second.get();
	}

	void MusicDataController::RemovePlayList(const string& name)
	{
		hash_map<string, std::shared_ptr<MusicListModel>>::iterator it = mMusicLists.find(name);
		if (it != mMusicLists.end())
		{
			mMusicLists.erase(it);
		}
	}
	void MusicDataController::ChangePlayListOrder(const string& name, size_t newOrder)
	{

	}
	void MusicDataController::RemoveMusic(const string& name, size_t index)
	{

	}
	void MusicDataController::ClearMusics(const string& name)
	{

	}

}
