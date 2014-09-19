#pragma once
#include "WinSocket.h"

namespace veda
{
	class IPAddress
	{
	public:
		IPAddress();
		IPAddress(const String& ip, short port);
		~IPAddress();
	private:
		ADDRINFOT mAddInfo;
	};
}


