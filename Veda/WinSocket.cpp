#include "stdafx.h"
#include "WinSocket.h"

namespace veda
{
	WinSocket::WinSocket()
	{
		init();
	}


	WinSocket::~WinSocket()
	{
	}

	void WinSocket::init()
	{
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;

		wVersionRequested = MAKEWORD(2, 2);

		err = WSAStartup(wVersionRequested, &wsaData);

		if (err != 0)
		{
			throw NetException(L"fail to init socket library");
		}

		if (LOBYTE(wsaData.wVersion) != 2 ||
			HIBYTE(wsaData.wVersion) != 2)
		{
			WSACleanup();
			throw NetException(L"fail to init socket library");
		}
	}
}

