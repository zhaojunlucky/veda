#pragma once
#include <vector>
#include <Decoder.h>
#include <DecoderFactory.hpp>
#include <string>

using namespace std;

namespace zpl
{
	struct MediaModel
	{
		MediaModel()
		{
			isCue = false;
		}
		MediaModel(const MediaModel& m)
		{
			Copy(m);
		}
		void MediaType()
		{
			af = audio::DecoderFactory::DetectMediaType(file.c_str());
		}
		std::string file;
		std::string title;
		std::string alblum;
		audio::AudioFormat af;
		struct CueInfo
		{
			CueInfo()
			{

			}
			CueInfo(const CueInfo& cueInfo)
			{
				Copy(cueInfo);
			}
			float start;
			float end;
			bool operator==(const CueInfo& cue)
			{
				return start == cue.start && end == cue.end;
			}
			CueInfo& operator=(const CueInfo& cueInfo)
			{
				if (this != &cueInfo){
					Copy(cueInfo);
				}
				return *this;
			}
		private:
			void Copy(const const CueInfo& cueInfo)
			{
				start = cueInfo.start;
				end = cueInfo.end;
			}
		}cueInfo;
		bool isCue;

		bool operator == (const MediaModel& m)
		{
			return file == m.file && isCue == m.isCue && cueInfo == m.cueInfo;
		}
		MediaModel& operator=(const MediaModel&m)
		{
			if (this != &m)
			{
				Copy(m);
			}
			return *this;
		}
	private:
		void Copy(const MediaModel& m)
		{
			file = m.file;
			title = m.title;
			alblum = m.alblum;
			isCue = m.isCue;
			cueInfo = m.cueInfo;
			af = m.af;
		}
	};
}