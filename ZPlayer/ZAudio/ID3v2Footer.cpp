#include "stdafx.h"
#include "ID3v2Footer.h"

namespace audio
{
	namespace id3v2
	{
		ID3v2Footer::ID3v2Footer()
		{
		}


		ID3v2Footer::~ID3v2Footer()
		{
		}

		void ID3v2Footer::parse(const char buf[10])
		{
			if (buf[0] == '3' && buf[1] == 'D' && buf[2] == 'I')
			{
				mMajorVer = buf[3];
				mRevisionVer = buf[4];
				const char* p = &buf[6];
				mSize = BigEndian2UInt(p);
			}
			else
			{
				throw ID3v2Exception("footer identifier is not '3DI'");
			}
		}
		unsigned int ID3v2Footer::getMajorVer() const
		{
			return mMajorVer;
		}
		unsigned int ID3v2Footer::getRevisionVer() const
		{
			return mRevisionVer;
		}
		unsigned int ID3v2Footer::getSize() const
		{
			return mSize;
		}
	}
}
