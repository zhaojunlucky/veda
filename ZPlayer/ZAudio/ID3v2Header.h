#pragma once
#include <string>
using namespace std;
#include "ID3v2Exception.h"

namespace audio
{
	namespace id3v2
	{
#define GetBit(value, pos) ( (value >> pos) & 0x01)

		static const char* ID3 = "ID3";
		class ID3v2Header
		{
		public:
			ID3v2Header();
			virtual ~ID3v2Header();
			// throws ID3v2Exception
			void parse(const char buf[10]);
			unsigned int getMajorVersion() const;
			unsigned int getRevisionVersion() const;
			void setMajorVersion(unsigned int m);
			void setRevisionVersion(unsigned int r);
			bool isUnsynchronisation() const;
			void setUnsynchronisation(bool v);
			bool isExtendedHeader() const;
			void setExtendedHeader(bool v);
			bool isExperimentalIndicator() const;
			void setExperimentalIndicator(bool v);
			bool isFooterPresent() const;
			void setFooterPresent(bool v);
			unsigned int getTagSize() const;

		protected:
			void parse();
		private:
			unsigned int mMajorVer;
			unsigned int mRevisionVer;
			string mHeaderStr;
			bool mIsUnsynchronisation;
			bool mIsExtendedHeader;
			bool mIsExperimentalIndicator;
			bool mIsFooterPresent;
			unsigned int mTotalSize;
		};
	}
}


