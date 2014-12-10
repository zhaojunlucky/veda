#pragma once
#include <ZString.h>
#include <Vector.h>
using namespace veda;

enum PlayMode
{
	RepeatAll,
	// shuffle always is the last
	Shuffle
};

struct MusicInfo
{
	String fileName;
	String fullPath;
	String artist;
	String alblum;
	String title;
	bool isCue;
	int start;
	int end;
};
