#include "stdafx.h"
#include "IPAddress.h"

namespace veda
{
	IPAddress::IPAddress()
		:mAf(AddressFamily::UnSpecified)
	{

	}
	IPAddress::IPAddress(const String& ip)
	{
		parse(ip);
	}

	IPAddress::IPAddress(const IPAddress& ipadd)
	{
		*this = ipadd;
	}
	IPAddress::~IPAddress()
	{
		
	}

	void IPAddress::parse(const String& ip)
	{
		int ret = 1;
		if (ip.find('.') != ip.npos)
		{
			mAf = AddressFamily::IPv4;
			ret = InetPton(mAf, ip.c_str(), &mAddInfo4);
		}
		else
		{
			mAf = AddressFamily::IPv6;
			ret = InetPton(mAf, ip.c_str(), &mAddInfo6);
		}
		String mes;
		if (ret == 0)
		{
			mes.format(_T("'%s' is not a valid ipv4 or ipv6 address."), ip.c_str());
			throw NetException(mes);
		}
		else if (ret == -1)
		{
			getSocketErrorMessage(WSAGetLastError(), mes);
			throw NetException(mes);
		}
	}

	const void* IPAddress::getAddressInfo() const
	{
		if (mAf == AddressFamily::IPv6)
		{
			return (void*)&mAddInfo6;
		}
		else if (mAf == AddressFamily::IPv4)
		{
			return (void*)&mAddInfo4;
		}
		else
		{
			return 0;
		}
	}

	int IPAddress::getLength() const
	{
		if (mAf == AddressFamily::IPv6)
		{
			return sizeof(mAddInfo6);
		}
		else
		{
			return sizeof(mAddInfo4);
		}
	}
	IPAddress::operator const void*()const
	{
		return getAddressInfo();
	}
	AddressFamily IPAddress::getAddressFamily() const
	{
		return mAf;
	}

	IPAddress& IPAddress::operator = (const IPAddress& ipadd)
	{
		if (this != ipadd)
		{
			mAf = ipadd.mAf;
			if (mAf == AddressFamily::IPv4)
			{
				memcpy(&mAddInfo4, &ipadd.mAddInfo4, sizeof(mAddInfo4));
			}
			else if (mAf == AddressFamily::IPv6)
			{
				memcpy(&mAddInfo6, &ipadd.mAddInfo6, sizeof(mAddInfo6));
			}
		}
		return *this;
	}

	void IPAddress::setPort(int port)
	{
		if (mAf == AddressFamily::IPv4)
		{
			mAddInfo4.sin_port = htons(port);
		}
		else if (mAf == AddressFamily::IPv6)
		{
			mAddInfo6.sin6_port = htons(port);
		}
	}
}
