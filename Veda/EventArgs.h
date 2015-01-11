#pragma once
#include "ZString.h"
namespace veda
{
	class VEDA_EXPORT EventArgs
	{
	public:
		EventArgs();
		EventArgs(const wchar_t* type) :mEventType(type){}
		~EventArgs();
		const String& getEventType() const{ return mEventType; }
	private:
		String mEventType;
	};
}


