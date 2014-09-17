#pragma once
#include "ID3v2Exception.h"
#include "ID3v2Base.h"
#include "ID3v2Header.h"
#include <ZString.h>
using namespace veda;

namespace audio
{
	namespace id3v2
	{
		class ID3v2ExtendedHeader3
		{
		public:
			ID3v2ExtendedHeader3(ID3v2Header3* header);
			virtual ~ID3v2ExtendedHeader3();
			void parse(const char buf[10]);
			unsigned int getSize() const;
			bool isCRCPresent() const;
			void setExtHeaderData(const char* data);
			const char* getCRCData() const;
		protected:
			void parse();
		private:
			unsigned int mSize;
			AString mExtHeaderData;
			ID3v2Header3* mHeader;
			AString mData;
			bool mCRCPresent;
			AString mCRCData;
			unsigned int mSizeOfPadding;
		};

		class ID3v2ExtendedHeader4
		{
		public:
			ID3v2ExtendedHeader4(ID3v2Header4* header);
			virtual ~ID3v2ExtendedHeader4();
			void parse(const char buf[6]);
			void setExtHeaderData(const char* data);
			unsigned int getSize() const;
			bool isUpdate() const;
			bool isCRCPresent() const;
			bool isRestrictions() const;
			short getTagSizeRestrictionsFlag() const;
			short getTextSizeRestrictionsFlag() const;
			short getImageEncodingRestrictionsFlag() const;
			short getImageSizeRestrictionsFlag() const;
		protected:
			void parse();
		private:
			unsigned int mSize;
			AString mExtHeaderData;
			AString mData;
			ID3v2Header4* mHeader;
			size_t mNumberOfFlagBytes;
			bool mTagIsUpdate;
			bool mCRCPresent;
			bool mIsTagRestrictions;
			short mTagSizeRt;
			short mTextEncRt;
			short mTextSizeRt;
			short mImageEncRt;
			short mImageSizeRt;
			AString mCRCData;
		};

	}
}