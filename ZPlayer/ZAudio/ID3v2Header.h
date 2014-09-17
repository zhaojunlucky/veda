#pragma once
#include "ZString.h"
#include "ID3v2Exception.h"
#include "ID3v2Base.h"

using namespace veda;
namespace audio
{
	namespace id3v2
	{
		class ID3v2Header3
		{
		public:
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
			unsigned int getTagSize() const;

		protected:
			virtual void parse();
		protected:
			unsigned int mMajorVer;
			unsigned int mRevisionVer;
			AString mHeaderStr;
			bool mIsUnsynchronisation;
			bool mIsExtendedHeader;
			bool mIsExperimentalIndicator;
			bool mIsFooterPresent;
			unsigned int mTotalSize;
		};

		class ID3v2Header4 : public ID3v2Header3
		{
		public:
			bool isFooterPresent() const;
			void setFooterPresent(bool v);
		protected:
			virtual void parse();
		protected:
			bool mIsFooterPresent;
		};
	}
}


