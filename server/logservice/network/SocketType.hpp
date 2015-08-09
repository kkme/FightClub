#ifndef __SOCKET_SOCKET_TYPE_H
#define __SOCKET_SOCKET_TYPE_H

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netinet/in.h>

namespace PWRD{

	namespace Network{

		struct  StreamType
		{
			static int Family();
			static int SocketType();
			static int Protocol();
		};

		struct  DatagramType
		{
			static int Family();
			static int SocketType();
			static int Protocol();
		};
	}
}

#endif

