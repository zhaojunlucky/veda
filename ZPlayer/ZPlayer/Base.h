#pragma once
#include <ZString.h>
#include <Vector.h>
using namespace veda;
#include <memory>

enum PlayMode
{
	RepeatAll,
	// shuffle always is the last
	Shuffle
};

struct MusicInfo
{
	long id;
	String fileName;
	String fullPath;
	String artist;
	String album;
	String title;
	bool isCue;
	int start;
	int end;
	float order;
	bool isUpdated;
};

typedef std::shared_ptr<MusicInfo> MusicInfoPtr;