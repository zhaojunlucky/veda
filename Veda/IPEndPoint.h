#pragma once
#include <memory>
#include "WinSocket.h"
#include "IPAddress.h"

namespace veda
{
	class IPEndPoint;
	typedef std::shared_ptr<IPEndPoint> IPEndPointPtr;
	class IPEndPoint
	{
	public:
		IPEndPoint(const String&ip, int port);
		IPEndPoint(const IPAddress&ip, int port);
		IPEndPoint(const IPEndPoint& ip);
		IPEndPoint(IPEndPoint&& ip);
		~IPEndPoint();

		AddressFamily getAddressFamily() const;
		const IPAddress& getIPAddress() const;
		int getPort() const;
		void set(const IPAddress&ip, int port);
		void set(const String&ip, int port);
		IPEndPoint& operator=(const IPEndPoint& ip);
		IPEndPoint& operator=(IPEndPoint&& ip);
	private:
		IPAddress *mAdd;
		int mPort;
	};
}


