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
	
	while ((line = reader.ReadLine()) != NULL)
	{
		LOG_INFO(logger) << line << endl;
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
