#include "CueSheet.h"

CueSheet::CueSheet()
{
}


CueSheet::~CueSheet()
{
}

void CueSheet::parse(const wchar_t* file)
{
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
		else if (str->startWith(L"INDEX") && isIndex01(str))
		{
			if (trackNode != NULL)
			{
				auto node = new CueSheetTreeNode;
				node->nodeData = std::move(*str.get());
				node->nodeKey = L"INDEX";
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

bool CueSheet::isIndex01(const StringPtr& indexStr)
{
	auto& str = indexStr->subString(5)->trimLeft();
	return str->startWith(L"01") || str->startWith(L"1");
}
void CueSheet::parse()
{
	
}
