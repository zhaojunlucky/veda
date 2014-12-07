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
	String artist;
	String alblum;
	bool isCue;
	int start;
	int end;
	time_t lastModifiedTime;
	long lastSize;
};