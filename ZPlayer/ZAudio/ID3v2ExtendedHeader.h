#pragma once
#include "ID3v2Exception.h"
#include "ID3v2Base.h"
#include <string>
using namespace std;
namespace audio
{
	namespace id3v2
	{
		class ID3v2ExtendedHeader
		{
		public:
			ID3v2ExtendedHeader();
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
		};

	}
}