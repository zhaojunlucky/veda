#pragma once
#include "MediaModel.h"
namespace zpl
{
	class MusicListModel
	{
	public:
		MusicListModel();
		virtual ~MusicListModel();

		void Add(const char* file);
		void AddCue(const char* file, float start, float end);
		void AddMedia(const MediaModel& media);
		size_t MusicCount() const;
		const MediaModel& GetMedia(unsigned int index) const;
	private:

		std::vector<struct MediaModel> mList;
	};
}
