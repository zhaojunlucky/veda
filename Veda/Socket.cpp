#include "stdafx.h"
#include "Socket.h"

namespace veda
{
	Socket::Socket()
		:mAF(AddressFamily::UnSpecified), mSocket(INVALID_SOCKET)
	{

	}

	Socket::Socket(AddressFamily af, SocketType st, SocketProtocol sp)
		:mAF(af), mST(st), mSP(sp)
	{
		makeSocket();
	}

	Socket::Socket(const Socket& socket)
	{
		*this = socket;
	}

	Socket::~Socket()
	{
	}
	Socket::operator SOCKET()
	{
		return mSocket;
	}
	SOCKET Socket::getSocket() const
	{
		return mSocket;
	}
	Socket &Socket::operator=(const Socket& s)
	{
		if (this != &s)
		{
			mAF = s.mAF;
			mST = s.mST;
			mSP = s.mSP;
			mSocket = s.mSocket;
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

	void Socket::close()
	{
		closesocket(mSocket);
		mSocket = INVALID_SOCKET;
	}
}