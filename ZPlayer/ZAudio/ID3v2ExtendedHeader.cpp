#include "stdafx.h"
#include "ID3v2ExtendedHeader.h"

namespace audio
{
	namespace id3v2
	{
		ID3v2ExtendedHeader3::ID3v2ExtendedHeader3(ID3v2Header3* header)
			:mSize(0), mHeader(header)
		{
			
		}


		ID3v2ExtendedHeader3::~ID3v2ExtendedHeader3()
		{
		}

		void ID3v2ExtendedHeader3::parse(const char buf[10])
		{
			mExtHeaderData.append(buf,10);
			parse();
		}
		unsigned int ID3v2ExtendedHeader3::getSize() const
		{
			return mSize;
		}

		void ID3v2ExtendedHeader3::setExtHeaderData(const char* data)
		{
			mData.append(data, mSize);
			mCRCData.append(data, 4);
		}
		const char* ID3v2ExtendedHeader3::getCRCData() const
		{
			return mCRCData.getData();
		}

		void ID3v2ExtendedHeader3::parse()
		{
			const char* p = mExtHeaderData.c_str();

			// invalid tag size
			if (p[0] >= 0x80 || p[1] >= 0x80 || p[2] >= 0x80 || p[3] >= 0x80)
			{
				throw ID3v2Exception("Invalid tag size.");
			}

			mSize = BigEndian2UInt(p);
			mCRCPresent = GetBit(p[4], 7);
			AString str;
			const char*ptr = &p[6];
			mSizeOfPadding = BigEndian2UInt(ptr);
		}

		// 2.4

		ID3v2ExtendedHeader4::ID3v2ExtendedHeader4(ID3v2Header4* header)
			:mHeader(header)
		{

		}
		ID3v2ExtendedHeader4::~ID3v2ExtendedHeader4()
		{

		}
		void ID3v2ExtendedHeader4::parse(const char buf[6])
		{
			mExtHeaderData.append(buf, 6);
		}
		unsigned int ID3v2ExtendedHeader4::getSize() const
		{
			return mSize;
		}
		bool ID3v2ExtendedHeader4::isUpdate() const
		{
			return mTagIsUpdate;
		}
		bool ID3v2ExtendedHeader4::isCRCPresent() const
		{
			return mCRCPresent;
		}
		bool ID3v2ExtendedHeader4::isRestrictions() const
		{
			return mIsTagRestrictions;
		}
		short ID3v2ExtendedHeader4::getTagSizeRestrictionsFlag() const
		{
			return mTagSizeRt;
		}
		short ID3v2ExtendedHeader4::getTextSizeRestrictionsFlag() const
		{
			return mTextSizeRt;
		}
		short ID3v2ExtendedHeader4::getImageEncodingRestrictionsFlag() const
		{
			return mImageEncRt;
		}
		short ID3v2ExtendedHeader4::getImageSizeRestrictionsFlag() const
		{
			return mImageSizeRt;
		}
		void ID3v2ExtendedHeader4::parse()
		{
			const char* p = mExtHeaderData.c_str();
			mSize = BigEndian2UInt(p);
			mNumberOfFlagBytes = p[4];
			if (mNumberOfFlagBytes == 1)
			{
				mTagIsUpdate = GetBit(p[5], 6);
				mCRCPresent = GetBit(p[5], 5);
				mIsTagRestrictions = GetBit(p[5], 4);
			}
			else
			{
				mTagIsUpdate = false;
				mCRCPresent = false;
				mIsTagRestrictions = false;
				mTagSizeRt = -1;
				mTextEncRt = -1;
				mTextSizeRt = -1;
				mImageEncRt = -1;
				mImageSizeRt = -1;
			}
		}

		void ID3v2ExtendedHeader4::setExtHeaderData(const char* data)
		{
			mData.append(data, mSize);
			size_t index = 0;
			if (mTagIsUpdate)
			{
				index++;
			}
			if (mCRCPresent)
			{
				size_t l = mData[index++];
				mCRCData.append(&data[index], l);
			}
			if (mIsTagRestrictions)
			{
				char c = mCRCData[++index];
				mTagSizeRt = (GetBit(c, 7) << 1) | (GetBit(c,6));
				mTextEncRt = GetBit(c, 5);
				mTextSizeRt = (GetBit(c, 4) << 1) | (GetBit(c, 3));
				mImageEncRt = GetBit(c, 2);
				mImageSizeRt = (GetBit(c, 1) << 1) | (GetBit(c, 0));
			}
		}


	}
}