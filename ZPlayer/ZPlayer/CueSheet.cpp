#include "CueSheet.h"
#include <Decoder.h>
#include <DecoderFactory.hpp>
using namespace audio;
CueSheet::CueSheet()
{
}


CueSheet::~CueSheet()
{
}

void CueSheet::parse(const wchar_t* file)
{
	mMusics.clear();
	veda::WBufferedFileReader reader(file,true);
	const wchar_t* line = NULL;
	mRoot.clear();
	CueSheetTreeNode* fileNode = NULL;
	CueSheetTreeNode* trackNode = NULL;
	while ((line = reader.ReadLine()) != NULL)
	{
		LOG_INFO(logger) << line << endl;
		String tmp = line;
		auto& str = tmp.trim();
		if (str->startWith(L"FILE"))
		{
			if (fileNode != NULL && trackNode != NULL)
			{
				// add last track node to file node childs
				fileNode->childs.add(std::shared_ptr<CueSheetTreeNode>(trackNode));
				trackNode = NULL;
				mRoot.childs.add(std::shared_ptr<CueSheetTreeNode>(fileNode));
				fileNode = NULL;
			} 
			if (fileNode == NULL)
			{
				// create a new node
				fileNode = new CueSheetTreeNode;
				fileNode->nodeData = std::move(*str.get());
				fileNode->nodeKey = L"FILE";
			}
			else
			{
				// log error
			}
		}
		else if (str->startWith(L"TRACK"))
		{
			if (trackNode != NULL && fileNode != NULL)
			{
				fileNode->childs.add(std::shared_ptr<CueSheetTreeNode>(trackNode));
				trackNode = NULL;
			}
			if (trackNode == NULL)
			{
				// create a new track node
				trackNode = new CueSheetTreeNode;
				trackNode->nodeKey = L"TRACK";
				trackNode->nodeData = std::move(*str.get());
			}
			else
			{
				// log error
			}
		}
		else if (str->startWith(L"TITLE"))
		{
			if (trackNode != NULL)
			{
				auto node = new CueSheetTreeNode;
				node->nodeData = std::move(*str.get());
				node->nodeKey = L"TITLE";
				trackNode->childs.add(std::shared_ptr<CueSheetTreeNode>(node));
			}
			else
			{
				// log error
			}
		}
		else if (str->startWith(L"PERFORMER"))
		{
			if (trackNode != NULL)
			{
				auto node = new CueSheetTreeNode;
				node->nodeData = std::move(*str.get());
				node->nodeKey = L"PERFORMER";
				trackNode->childs.add(std::shared_ptr<CueSheetTreeNode>(node));
			}
			else
			{
				// log error
			}
		}
		else if (str->startWith(L"INDEX") )
		{
			if (trackNode != NULL)
			{
				auto node = new CueSheetTreeNode;
				
				if (isIndex01(str))
				{
					node->nodeKey = L"INDEX01";
				}
				else
				{
					node->nodeKey = L"INDEX00";
				}
				node->nodeData = std::move(*str.get());
				trackNode->childs.add(std::shared_ptr<CueSheetTreeNode>(node));
			}
			else
			{
				// log error
			}
		}
		/*else if (str->startWith(L"CATALOG"))
		{

		}
		else if (str->startWith(L"CDTEXTFILE"))
		{

		}
		else if (str->startWith(L"FLAGS"))
		{

		}
		else if (str->startWith(L"ISRC"))
		{

		}
		else if (str->startWith(L"POSTGAP"))
		{

		}
		else if (str->startWith(L"PREGAP"))
		{

		}
		else if (str->startWith(L"REM"))
		{

		}
		else if (str->startWith(L"SONGWRITER"))
		{

		}*/
		
	}
	// add last track into file node
	if (trackNode != NULL && fileNode != NULL)
	{
		fileNode->childs.add(std::shared_ptr<CueSheetTreeNode>(trackNode));
		trackNode = NULL;
	}
	else
	{
		// log error
	}
	// add last file node into root
	if (fileNode != NULL)
	{
		mRoot.childs.add(std::shared_ptr<CueSheetTreeNode>(fileNode));
		fileNode = NULL;
	}
	else
	{
		// log error
	}
	reader.close();
	parse();
}
size_t CueSheet::getMusicCount() const
{
	return mMusics.getLength();
}
MusicInfoPtr& CueSheet::get(size_t index)
{
	return mMusics[index];
}
const MusicInfoPtr& CueSheet::get(size_t index) const
{
	return mMusics[index];
}

bool CueSheet::isIndex00(const StringPtr& indexStr)
{
	auto& str = indexStr->subString(5)->trimLeft();
	return str->startWith(L"01") || str->startWith(L"1");
}

bool CueSheet::isIndex01(const StringPtr& indexStr)
{
	auto& str = indexStr->subString(5)->trimLeft();
	return str->startWith(L"01") || str->startWith(L"1");
}
void CueSheet::parse()
{
	for (auto i = 0; i < mRoot.childs.getLength(); i++)
	{
		auto& fileNode = mRoot.childs[i];
		if (fileNode->nodeKey.equalsIgnoreCase(L"FILE"))
		{
			// visit file node's all tracks
			processFileNode(fileNode.get());
		}
	}
}

void CueSheet::processFileNode(const CueSheetTreeNode* fileNode)
{
	String fullPath = mDirPath;
	parseString(fullPath, fileNode->nodeData);
	float totalTimeSec = 0;
	auto decoder = DecoderFactory::CreateDecoderByFile(fullPath.c_str());
	if (decoder != NULL)
	{
		if (0 == decoder->Open(fullPath.c_str()))
		{
			totalTimeSec = decoder->getWaveInfo().durationTime;
		}
		else
		{
			// log error
		}
		
		delete decoder;
	}
	else
	{
		// log unsupport media
		return;
	}
	// vistit all tracks
	MusicInfo* last = NULL;
	for (auto i = 0; i < fileNode->childs.getLength(); i++)
	{
		auto& trackNode = fileNode->childs[i];
		auto musicInfoPtr = make_shared<MusicInfo>();
		musicInfoPtr->isUpdated = true;
		musicInfoPtr->isCue = true;
		musicInfoPtr->fullPath.append(fullPath);
		musicInfoPtr->id = -1;
		musicInfoPtr->end = 0;
		musicInfoPtr->order = -1;
		for (auto j = 0; j < trackNode->childs.getLength(); j++)
		{
			auto& data = trackNode->childs[j];
			if (data->nodeKey.equalsIgnoreCase(L"TITLE"))
			{
				parseString(musicInfoPtr->title,data->nodeData);
			}
			else if (data->nodeKey.equalsIgnoreCase(L"PERFORMER"))
			{
				parseString(musicInfoPtr->artist, data->nodeData);
			}
			else if (data->nodeKey.equalsIgnoreCase(L"INDEX01"))
			{
				musicInfoPtr->start = parseTime(data->nodeData);
			}
			else if (data->nodeKey.equalsIgnoreCase(L"INDEX00"))
			{
				if (last != NULL)
				{
					last->end = parseTime(data->nodeData);
				}
			}
		}
		if (last != NULL && last->end == 0)
		{
			last->end = musicInfoPtr->start;
		}
		last = musicInfoPtr.get();
		mMusics.add(musicInfoPtr);
	}
	// last one's end time
	last->end = totalTimeSec;
}

float CueSheet::parseTime(const String& str)
{
	String tmp;

	float timeSec = 0;
	size_t start = str.rfind(' ');
	if (start != str.npos  )
	{
		++start;
		if (str.getSize() - start == 8)
		{
			tmp.append(&str[start], 2);
			timeSec += 60 * _wtof(tmp.getData());
			tmp.clear();
			tmp.append(&str[start+3], 2);
			timeSec += _wtof(tmp.getData());
			tmp.clear();
			tmp.append(&str[start+6], 2);
			timeSec +=  _wtof(tmp.getData())/1000;
		}
	}
	return timeSec;
}

void CueSheet::parseString(String& dst, const String& src)
{
	size_t start = src.find('"');
	size_t end = src.rfind('"');
	if (start != src.npos && end != src.npos && start < end)
	{
		for (size_t i = start + 1; i < end; i++)
		{
			dst.append(src[i]);
		}
	}
}