#pragma once
#include "WinSocket.h"

namespace veda
{
	class Socket
	{
	public:
		Socket(AddressFamily af, SocketType st, SocketProtocol sp);
		Socket(const Socket& socket);
		~Socket();
		operator SOCKET();
		SOCKET getSocket() const;
		AddressFamily getAddressFamily() const;
		SocketType getSocketType() const;
		SocketProtocol getSocketProtocol() const;
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


