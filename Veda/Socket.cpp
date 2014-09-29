#include "stdafx.h"
#include "Socket.h"

namespace veda
{
	Socket::Socket(AddressFamily af, SocketType st, SocketProtocol sp)
		:mAF(af), mST(st), mSP(sp)
	{
		makeSocket();
		mEP = 0;
	}

	Socket::Socket(const Socket& socket)
	{
		mEP = 0;
		*this = socket;
	}

	Socket::~Socket()
	{
		if (mEP != 0)
		{
			delete mEP;
		}
	}
	Socket::operator SOCKET()
	{
		return mSocket;
	}
	SOCKET Socket::getSocket() const
	{
		return mSocket;
	}
	AddressFamily Socket::getAddressFamily() const
	{
		return mAF;
	}
	SocketType Socket::getSocketType() const
	{
		return mST;
	}
	SocketProtocol Socket::getSocketProtocol() const
	{
		return mSP;
	}
	Socket &Socket::operator=(const Socket& s)
	{
		if (this != &s)
		{
			mAF = s.mAF;
			mST = s.mST;
			mSP = s.mSP;
			mSocket = s.mSocket;
			if (mEP)
			{
				*mEP = *s.mEP;
			}
			else
			{
				mEP = new IPEndPoint(*s.mEP);
			}
		}
		return *this;
	}

	bool Socket::isValid() const
	{
		return (mSocket != INVALID_SOCKET);
	}

	void Socket::makeSocket()
	{
		mSocket = socket(mAF, mST, mSP);
	}

	void Socket::bind(const IPEndPoint& ep)
	{
		if (mEP)
		{
			*mEP = ep;
		}
		else
		{
			mEP = new IPEndPoint(ep);
		}
		bind();
	}

	void Socket::bind(IPAddress& ip, int port)
	{
		if (mEP)
		{
			mEP->set(ip, port);
		}
		else
		{
			mEP = new IPEndPoint(ip,port);
		}
		bind();
	}
	void Socket::bind(const String& ip, int port)
	{
		if (mEP)
		{
			mEP->set(ip, port);
		}
		else
		{
			mEP = new IPEndPoint(ip,port);
		}
		bind();
	}
	void Socket::bind()
	{
		int ret = ::bind(mSocket, (const struct sockaddr*)mEP->getIPAddress().getAddressInfo(), mEP->getIPAddress().getLength());

	}
	void Socket::listen()
	{

	}
	SocketPtr Socket::accept()
	{

	}

	void Socket::close()
	{
		closesocket(mSocket);
		mSocket = INVALID_SOCKET;
	}

	const IPEndPoint* Socket::getLocalEndPoint() const
	{
		return mEP;
	}
}