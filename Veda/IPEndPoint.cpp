#include "stdafx.h"
#include "IPEndPoint.h"

namespace veda
{
	IPEndPoint::IPEndPoint(const String&ip, int port)
	{
		mAdd.parse(ip);
		mPort = port;
	}
	IPEndPoint::IPEndPoint(const IPAddress&ip, int port)
		:mAdd(ip), mPort(port)
	{

	}
	IPEndPoint::IPEndPoint(const IPEndPoint& ip)
	{
		*this = ip;
	}
	IPEndPoint::~IPEndPoint()
	{

	}

	AddressFamily IPEndPoint::getAddressFamily() const
	{
		return mAdd.getAddressFamily();
	}
	const IPAddress& IPEndPoint::getIPAddress() const
	{
		return mAdd;
	}
	int IPEndPoint::getPort() const
	{
		return mPort;
	}
	void IPEndPoint::set(const IPAddress&ip, int port)
	{
		mAdd = ip;
		mPort = port;
	}
	void IPEndPoint::set(const String&ip, int port)
	{
		mAdd.parse(ip);
		mPort = port;
	}
	IPEndPoint& IPEndPoint::operator = (const IPEndPoint& ip)
	{
		if (this != &ip)
		{
			mAdd = ip.mAdd;
			mPort = ip.mPort;
		}
		return *this;
	}
}
