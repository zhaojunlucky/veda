#pragma once
#include <Vector.h>
#include "Base.h"
#include "CueSheet.h"
class MusicInfoHelper
{
public:
	MusicInfoHelper();
	~MusicInfoHelper();
	bool isSupportedMediaFile(const wchar_t* file);

	void parseMedia(veda::Vector<MusicInfoPtr>& vec, const wchar_t* file);
	void parseCue(veda::Vector<MusicInfoPtr>& vec, const wchar_t* file);
	bool isCue(const wchar_t* file);
private:
	void parseFile(veda::Vector<MusicInfoPtr>& vec, const wchar_t* file);
};

