#pragma once
#include <ZString.h>
using namespace veda;

enum PlayMode
{
	RepeatAll,
	// shuffle always is the last
	Shuffle
};

struct MusicDetailsInfo
{
	long id;
	String fileName;
	String fullPath;
	String artist;
	String alblum;
	String title;
	bool isCue;
	int start;
	int end;
	time_t lastModifiedTime;
	long lastSize;
};