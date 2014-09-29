#include "stdafx.h"
#include "IPEndPoint.h"

namespace veda
{
	IPEndPoint::IPEndPoint(const String&ip, int port)
	{
		mAdd = new IPAddress;
		mAdd->parse(ip);
		mPort = port;
		mAdd->setPort(port);
	}
	IPEndPoint::IPEndPoint(const IPAddress&ip, int port)
		:mPort(port)
	{
		mAdd = new IPAddress;
		*mAdd = ip;
		mAdd->setPort(port);
	}
	IPEndPoint::IPEndPoint(const IPEndPoint& ip)
	{
		*this = std::move(ip);
	}
	IPEndPoint::IPEndPoint(IPEndPoint&& ip)
	{
		mAdd = new IPAddress;
		*this = ip;
	}
	IPEndPoint::~IPEndPoint()
	{
		if (mAdd != 0)
		{
			delete mAdd;
		}
	}

	AddressFamily IPEndPoint::getAddressFamily() const
	{
		return mAdd->getAddressFamily();
	}
	const IPAddress& IPEndPoint::getIPAddress() const
	{
		return *mAdd;
	}
	int IPEndPoint::getPort() const
	{
		return mPort;
	}
	void IPEndPoint::set(const IPAddress&ip, int port)
	{
		*mAdd = ip;
		mPort = port;
		mAdd->setPort(port);
	}
	void IPEndPoint::set(const String&ip, int port)
	{
		mAdd->parse(ip);
		mPort = port;
		mAdd->setPort(port);
	}
	IPEndPoint& IPEndPoint::operator = (const IPEndPoint& ip)
	{
		if (this != &ip)
		{
			*mAdd = *ip.mAdd;
			mPort = ip.mPort;
		}
		return *this;
	}

	IPEndPoint& IPEndPoint::operator = (IPEndPoint&& ip)
	{
		if (this != &ip)
		{
			mAdd = ip.mAdd;
			mPort = ip.mPort;
			ip.mAdd = 0;
		}
		return *this;
	}
}
