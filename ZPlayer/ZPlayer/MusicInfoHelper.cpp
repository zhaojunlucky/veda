#include "MusicInfoHelper.h"
#include <DecoderFactory.hpp>
#include <ZString.h>
using namespace audio;
#include <taglib/fileref.h>

MusicInfoHelper::MusicInfoHelper()
{
}


MusicInfoHelper::~MusicInfoHelper()
{
}

bool MusicInfoHelper::isSupportedMediaFile(const wchar_t* file)
{
	bool support = true;
	AudioFormat af = DecoderFactory::DetectMediaType(file);
	if (af == AudioFormat::Unknown)
	{
		support = isCue(file);
	}
	return support;
}

void MusicInfoHelper::parseMedia(veda::Vector<MusicInfoPtr>& vec, const wchar_t* file)
{
	if (isCue(file))
	{
		parseCue(vec, file);
	}
	else
	{
		parseFile(vec, file);
	}

}
void MusicInfoHelper::parseCue(veda::Vector<MusicInfoPtr>& vec, const wchar_t* file)
{
	CueSheet cue;
	cue.parse(file);
	for (size_t i = 0; i < cue.getMusicCount(); i++)
	{
		vec.add(cue.get(i));
	}
}
bool MusicInfoHelper::isCue(const wchar_t* file)
{
	veda::String tmp(file);
	auto& lower = tmp.toLowercase();
	return lower->endWith(L".cue");
}

void MusicInfoHelper::parseFile(veda::Vector<MusicInfoPtr>& vec, const wchar_t* file)
{
	if (isSupportedMediaFile(file))
	{
		TagLib::FileRef f(file);
		auto& musicInfo = std::make_shared<MusicInfo>();
		musicInfo->fullPath = file;
		musicInfo->album = f.tag()->album().toCWString();
		musicInfo->artist = f.tag()->artist().toCWString();
		musicInfo->end = f.audioProperties()->length();
		musicInfo->start = 0;
		musicInfo->id = -1;
		musicInfo->isCue = false;
		musicInfo->title = f.tag()->title().toCWString();
		if (musicInfo->title.getSize() == 0)
		{
			String filePath = file;
			size_t i = filePath.getSize() - 1;
			for (; i >= 1; i--)
			{
				auto c = filePath[i];
				if (c == '\\' || c == '/')
				{
					break;
				}
			}
			musicInfo->title = filePath.subString(i + 1, filePath.rfind(L'.') - i - 1)->c_str();
		}
		musicInfo->isUpdated = true;
		
		vec.add(musicInfo);
	}
}