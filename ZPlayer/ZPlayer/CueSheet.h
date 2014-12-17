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
	bool isIndex00(const StringPtr& indexStr);
	bool isIndex01(const StringPtr& indexStr);
	void parse();
	void processFileNode(const CueSheetTreeNode* fileNode);
	float parseTime(const String& str);
	void parseString(String& dst, const String& src);
private:
	veda::Vector<MusicInfoPtr> mMusics;
	CueSheetTreeNode mRoot;
	// contains '/' at the end
	String mDirPath;
};

