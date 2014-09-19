#pragma once
#include "WinSocket.h"

namespace veda
{
	class Socket
	{
	public:
		Socket();
		Socket(AddressFamily af, SocketType st, SocketProtocol sp);
		Socket(const Socket& socket);
		~Socket();
		operator SOCKET();
		SOCKET getSocket() const;
		Socket &operator=(const Socket& s);
		bool isValid() const;
		void close();
	private:
		void makeSocket();
	private:
		AddressFamily mAF;
		SocketType mST;
		SocketProtocol mSP;
		SOCKET mSocket;
	};
}


