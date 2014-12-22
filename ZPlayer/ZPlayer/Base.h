#pragma once
#include <ZString.h>
#include <Vector.h>
using namespace veda;
#include <memory>
#include <float.h>
#define MAX_ORDER FLT_MAX
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
	float start;
	float end;
	float order;
	bool isUpdated;

	MusicInfo()
	{
		order = MAX_ORDER;
	}
};

typedef std::shared_ptr<MusicInfo> MusicInfoPtr;

class CueSheetTreeNode
{
public:
	String nodeKey;
	String nodeData;
	Vector<std::shared_ptr<CueSheetTreeNode>> childs;

	// empty all nodes data
	void clear()
	{
		nodeKey.clear();
		nodeData.clear();
		childs.clear();
	}
};