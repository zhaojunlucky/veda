#pragma once
#include <ZString.h>
#include "ID3v2Base.h"
#include "ID3v2Exception.h"

using namespace veda;
namespace audio
{
	namespace id3v2
	{
		class ID3v2Footer
		{
		public:
			ID3v2Footer();
			~ID3v2Footer();
			void parse(const char buf[10]);
			unsigned int getMajorVer() const;
			unsigned int getRevisionVer() const;
			unsigned int getSize() const;
		protected:
			AString mFooter;
			unsigned int mMajorVer;
			unsigned int mRevisionVer;
			unsigned int mSize;
		};

	}
}