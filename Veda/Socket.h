#pragma once
#include <memory>
#include "WinSocket.h"
#include "IPEndPoint.h"
#include <Winsock2.h>

namespace veda
{
	class Socket;
	typedef std::shared_ptr<Socket> SocketPtr;
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
		const IPEndPoint* getLocalEndPoint() const;

		void bind(const IPEndPoint& ep);
		void bind(IPAddress& ip, int port);
		void bind(const String& ip, int port);
		
		void listen();
		SocketPtr accept();
		
	private:
		void makeSocket();
		void bind();
	private:
		AddressFamily mAF;
		SocketType mST;
		SocketProtocol mSP;
		SOCKET mSocket;
		IPEndPoint* mEP;
	};
}


