#include "Playlist.h"
#include "DbHelper.h"
#include "ZPLException.h"
#include <utility>
Playlist::Playlist(const wchar_t* playlistName)
	:mPlaylistName(playlistName), mId(-1), mIsModified(false)
{

}

Playlist::Playlist(const wchar_t* playlistName, long id)
	: mPlaylistName(playlistName), mId(id), mIsModified(false)
{

}

const wchar_t* Playlist::getPlaylistName() const
{
	return mPlaylistName.c_str();
}
size_t Playlist::getPlaylistSize() const
{
	return mPlaylist.getLength();
}
bool Playlist::addMusicInfo(shared_ptr<MusicInfo> musicInfo)
{
	if (musicInfo->order == MAX_ORDER)
	{
		throw ZPLException(L"Invalid music order.");
	}
	if (mMap.find(musicInfo->id) == mMap.end())
	{
		mPlaylist.add(musicInfo);
		mMap[musicInfo->id] = true;
		mIsModified = true;
		return true;
	}
	return false;
}

void Playlist::addMusicInfos(veda::Vector<MusicInfoPtr>& musicInfos, bool removeExisting)
{
	auto lastOrder = -1000000.0f;
	if (mPlaylist.getLength() > 0)
	{
		lastOrder = mPlaylist[mPlaylist.getLength() - 1]->order;
	}
	veda::Vector<size_t> removedIndexs;
	veda::Vector<std::pair<long, float>> musicOrder;
	for (size_t i = 0; i < musicInfos.getLength(); i++)
	{
		auto& m = musicInfos[i];
		if (m->order == MAX_ORDER)
		{
			lastOrder += 1;
			m->order = lastOrder;
		}
		if (!addMusicInfo(m))
		{
			removedIndexs.add(i);
		}
		else
		{
			musicOrder.add(std::make_pair(m->id, lastOrder));
		}
	}
	DbHelper::getInstance()->addMusicsToPl(mId, musicOrder);
	if (removeExisting)
	{
		for (auto& it = removedIndexs.cbegin(); it != removedIndexs.cend(); ++it)
		{
			musicInfos.removeAt(*it);
		}
	}
	
}

const MusicInfo& Playlist::getMusicInfo(size_t index) const
{
	return *mPlaylist[index].get();
}
MusicInfo& Playlist::getMusicInfo(size_t index)
{
	return *mPlaylist[index].get();
}
void Playlist::remove(size_t index)
{
	DbHelper::getInstance()->removeMusicFromPl(mId, mPlaylist[index]->id);
	auto it = mMap.find(mPlaylist[index]->id);
	if (it != mMap.end())
	{
		mMap.erase(it);
	}
	mPlaylist.removeAt(index);
	//mIsModified = false;
	
}
void Playlist::clear()
{
	mPlaylist.clear();
	mMap.clear();
}
void Playlist::setName(const wchar_t* name)
{
	mPlaylistName = name;
	mIsModified = true;
}



bool Playlist::isModified() const
{
	return mIsModified;
}

long Playlist::getPlaylistId() const
{
	return mId;
}

void Playlist::exchange(size_t from, size_t to)
{
	auto order = mPlaylist[from]->order;
	mPlaylist[from]->order = mPlaylist[to]->order;
	mPlaylist[to]->order = order;
	veda::Vector<MusicInfoPtr> ve;
	ve.add(mPlaylist[from]);
	ve.add(mPlaylist[to]);
	DbHelper::getInstance()->updatePlayMusicOrder(mId, ve);
	auto p = mPlaylist[from];
	mPlaylist.removeAt(from);
	mPlaylist.add(p, to);
}