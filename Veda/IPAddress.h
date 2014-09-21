#pragma once
#include "WinSocket.h"

namespace veda
{
	class IPAddress
	{
	public:
		IPAddress();
		IPAddress(const String& ip);
		IPAddress(const IPAddress& ipadd);
		~IPAddress();

		void parse(const String& ip);

		const void* getAddressInfo() const;
		operator const void*()const;
		AddressFamily getAddressFamily() const;
		IPAddress& operator=(const IPAddress& ipadd);
	private:
		in6_addr mAddInfo6; 
		in_addr mAddInfo4;
		AddressFamily mAf;
	};
}


