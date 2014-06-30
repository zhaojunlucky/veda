#include "stdafx.h"
#include "MusicListModel.h"

namespace zpl
{
	MusicListModel::MusicListModel()
	{

	}


	MusicListModel::~MusicListModel()
	{
	}

	void MusicListModel::Add(const char* file)
	{
		MediaModel m;
		m.file = file;
		AddMedia(m);
	}
	void MusicListModel::AddCue(const char* file, float start, float end)
	{
		MediaModel m;
		m.file = file;
		m.isCue = true;
		m.cueInfo.start = start;
		m.cueInfo.end = end;
		AddMedia(m);
	}
	void MusicListModel::AddMedia(const MediaModel& media)
	{
		mList.push_back(media);
	}

	size_t MusicListModel::MusicCount() const
	{
		return mList.size();
	}

	const MediaModel& MusicListModel::GetMedia(unsigned int index) const
	{
		return mList[index];
	}
}