#include "stdafx.h"
#include "ID3v2Header.h"

namespace audio
{
	namespace id3v2
	{
		ID3v2Header::ID3v2Header()
		{
		}


		ID3v2Header::~ID3v2Header()
		{
		}

		void ID3v2Header::parse(const char buf[10])
		{
			mHeaderStr.reserve(10);
			for (size_t i = 0; i < 10; i++)
			{
				mHeaderStr.push_back(buf[i]);
			}
			parse();
		}
		unsigned int ID3v2Header::getMajorVersion() const
		{
			return mMajorVer;
		}
		unsigned int ID3v2Header::getRevisionVersion() const
		{
			return mRevisionVer;
		}
		void ID3v2Header::setMajorVersion(unsigned int m)
		{
			mMajorVer = m;
		}
		void ID3v2Header::setRevisionVersion(unsigned int r)
		{
			mRevisionVer = r;
		}
		bool ID3v2Header::isUnsynchronisation() const
		{
			return mIsUnsynchronisation;
		}
		void ID3v2Header::setUnsynchronisation(bool v)
		{
			mIsUnsynchronisation = v;
		}
		bool ID3v2Header::isExtendedHeader() const
		{
			return mIsExtendedHeader;
		}
		void ID3v2Header::setExtendedHeader(bool v)
		{
			mIsExtendedHeader = v;
		}
		bool ID3v2Header::isExperimentalIndicator() const
		{
			return mIsExperimentalIndicator;
		}
		void ID3v2Header::setExperimentalIndicator(bool v)
		{
			mIsExperimentalIndicator = v;
		}
		bool ID3v2Header::isFooterPresent() const
		{
			return mIsFooterPresent;
		}
		void ID3v2Header::setFooterPresent(bool v)
		{
			mIsFooterPresent = v;
		}

		unsigned int ID3v2Header::getTagSize() const
		{
			return mTotalSize - 10 - mIsFooterPresent?10:0;
		}

		void ID3v2Header::parse()
		{
			const char* p = mHeaderStr.c_str();
			
			if (strncmp(p, ID3, 3) != 0)
			{
				throw ID3v2Exception("Not a valid id3 header.");
			}

			if (p[3] == 0xFF || p[4] == 0xFF)
			{
				throw ID3v2Exception("Invalid major version or revision number.");
			}

			// invalid tag size
			if (p[6] >= 0x80 || p[7] >= 0x80 || p[8] >= 0x80 || p[9] >= 0x80)
			{
				throw ID3v2Exception("Invalid tag size.");
			}


			mMajorVer = p[3];
			mRevisionVer = p[4];

			char flag = p[5];
			mIsUnsynchronisation = GetBit(flag, 7);
			mIsExtendedHeader = GetBit(flag,6);
			mIsExperimentalIndicator = GetBit(flag,5);
			mIsFooterPresent = GetBit(flag,4);

			const char* sizePtr = &p[6];
			mTotalSize = (((sizePtr[0] & 0x7F) << 21) | ((sizePtr[1] & 0x7F) << 14) | ((sizePtr[2] & 0x7F) << 7) | (sizePtr[3] & 0x7F));
		}
	}
}
