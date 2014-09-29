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
		int getLength() const;
		operator const void*()const;
		AddressFamily getAddressFamily() const;
		IPAddress& operator=(const IPAddress& ipadd);
	private:
		friend class IPEndPoint;
		void setPort(int port);
	private:
		sockaddr_in6 mAddInfo6;
		sockaddr_in mAddInfo4;
		AddressFamily mAf;
	};
}


