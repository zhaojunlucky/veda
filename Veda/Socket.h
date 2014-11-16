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
		IPEndPointPtr getLocalEndPoint() const;
		IPEndPointPtr getRemoteEndPoint() const;

		void bind(const IPEndPoint& ep);
		void bind(IPAddress& ip, int port);
		void bind(const String& ip, int port);
		
		void connect(const IPEndPoint& ep);
		void connect(IPAddress& ip, int port);
		void connect(const String& ip, int port);

		void recieve(char* buf, int pos, int bytes, SocketFlags socketFlags);

		void recieveFrom(char* buf, int pos, int bytes, SocketFlags socketFlags, IPEndPoint* from);
		
		void send(const char* buf, int pos, int bytes, SocketFlags socketFlags);

		void sendTo(const char* buf, int pos, int bytes, SocketFlags socketFlags, const IPEndPoint& from);
		void listen();
		SocketPtr accept();
		
		void shutdown();
		void close();
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


