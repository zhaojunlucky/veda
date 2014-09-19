#pragma once
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"WS2_32.lib")

#include "NetException.h"

namespace veda
{
	enum AddressFamily
	{
		UnSpecified = AF_UNSPEC,
		IPv4 = AF_INET,
		IPv6 = AF_INET6,
		Blueteeth = AF_BTH
	};

	enum SocketType
	{
		ST_TCP = SOCK_STREAM,
		ST_UDP = SOCK_DGRAM,
		ST_RAW = SOCK_RAW
	};

	enum SocketProtocol
	{
		SP_ICMP = IPPROTO_ICMP,
		SP_IGMP = IPPROTO_IGMP,
		SP_TCP = IPPROTO_TCP,
		SP_UDP = IPPROTO_UDP,
		SP_ICMPv6 = IPPROTO_ICMPV6
	};
	class WinSocket
	{
	public:
		WinSocket();
		~WinSocket();
	private:
		void init();
	};
}


