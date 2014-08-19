#include "stdafx.h"
#include "ID3v2ExtendedHeader.h"

namespace audio
{
	namespace id3v2
	{
		ID3v2ExtendedHeader::ID3v2ExtendedHeader(ID3v2Header* header)
			:mSize(0), mHeader(header)
		{
		}


		ID3v2ExtendedHeader::~ID3v2ExtendedHeader()
		{
		}

		void ID3v2ExtendedHeader::parse(const char buf[10])
		{
			mExtHeaderData.reserve(10);

			for (size_t i = 0; i < 10; i++)
			{
				mExtHeaderData.push_back(buf[i]);
			}
			parse();
		}
		unsigned int ID3v2ExtendedHeader::getSize() const
		{
			return mSize;
		}

		void ID3v2ExtendedHeader::parse()
		{
			const char* p = mExtHeaderData.c_str();

			// invalid tag size
			if (p[0] >= 0x80 || p[1] >= 0x80 || p[2] >= 0x80 || p[3] >= 0x80)
			{
				throw ID3v2Exception("Invalid tag size.");
			}

			mSize = BigEndian2UInt(p);
			

		}

	}
}