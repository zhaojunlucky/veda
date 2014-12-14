#pragma once
#include "Base.h"
#include <Vector.h>
#include "Logger.h"
extern Logger logger;
#include <File.h>
class CueSheet
{
public:
	CueSheet();
	~CueSheet();
	void parse(const wchar_t* file);
	size_t getMusicCount() const;
	MusicInfoPtr& get(size_t index);
	const MusicInfoPtr& get(size_t index) const;
private:
	veda::Vector<MusicInfoPtr> mMusics;
};

