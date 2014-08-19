#pragma once
#include "ID3v2Exception.h"
#include "ID3v2Base.h"
#include "ID3v2Header.h"
#include <string>
using namespace std;
namespace audio
{
	namespace id3v2
	{
		class ID3v2ExtendedHeader
		{
		public:
			ID3v2ExtendedHeader(ID3v2Header* header);
			virtual ~ID3v2ExtendedHeader();
			void parse(const char buf[10]);
			unsigned int getSize() const;
			bool isUpdate() const;
			bool isCRCPresent() const;
			bool isRestrictions() const;
		protected:
			void parse();
		private:
			unsigned int mSize;
			string mExtHeaderData;
			ID3v2Header* mHeader;
			size_t mNumberOfFlagBytes;
		};

	}
}