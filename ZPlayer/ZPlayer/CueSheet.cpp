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
	Vector<StringPtr> cueDatas;
	while ((line = reader.ReadLine()) != NULL)
	{
		LOG_INFO(logger) << line << endl;
		String tmp = line;
		auto& str = tmp.trim();
		if (str->startWith(L"FILE"))
		{
			cueDatas.add(str);
		}
		else if (str->startWith(L"TRACK"))
		{
			cueDatas.add(str);
		}
		else if (str->startWith(L"TITLE"))
		{
			cueDatas.add(str);
		}
		else if (str->startWith(L"PERFORMER"))
		{
			cueDatas.add(str);
		}
		else if (str->startWith(L"INDEX") && isIndex01(str))
		{
			cueDatas.add(str);
		}
		else if (str->startWith(L"CATALOG"))
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

		}
		
	}
	reader.close();

	parse(cueDatas);
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
void CueSheet::parse(const Vector<StringPtr>& cueDatas)
{
	for (size_t i = 0; i < cueDatas.getLength(); i++)
	{
		auto& str = cueDatas[i];
		if (str->startWith(L"FILE"))
		{
			size_t count = str->rfind('"') - 1;
			auto p = str->subString(1, count);
			String filePath = mDirPath;
			filePath.append(*p.get());
			
			
		}
	}
}
