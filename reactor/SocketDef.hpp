#ifndef __SOCKET_DEF_H
#define __SOCKET_DEF_H

#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>

namespace PWRD{

	typedef int Handle; 
	typedef socklen_t SockLen;

	const Handle INVALID_HANDLE = -1;
	const int FAILED = -1; 

#define PWRD_MSG_NOSIGNAL MSG_NOSIGNAL

#define RWOULDBLOCK EWOULDBLOCK // R is 'Result'

	// EPOLLIN&EPOLLOUT etc. isn't POSIX, it's correct that moving its to Epoll/
	typedef __uint32_t ReactorMask; 
	enum 
	{
		COMMON_READ_MASK = EPOLLIN,
		COMMON_WRITE_MASK = EPOLLOUT
	};

	inline void CloseSocket(Handle s);
	inline int GetLastError();
}

#include "./SocketDef.inl"

#endif

