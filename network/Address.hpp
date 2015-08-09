/****************************************************************************
 * PWRD socket's reactor library
 * Copyright (c) 2008 by Huang RuiGuang(jiangrg1981@gmail.com)
 *
 * Permission to use, copy, modify, distribute and sell this software.
 *****************************************************************************/

#ifndef __SOCKET_ADDRESS_H
#define __SOCKET_ADDRESS_H

#include <fcntl.h>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace PWRD{

	namespace Network{

		class  Address{

			public:

				Address();

				Address(u_short port);

				Address(const std::string& ip, u_short port);

				Address(u_long ip, u_short port);

				~Address(void);

				void Set(u_short port);

				void Set(u_long ip, u_short port);

				void Set(const std::string& ip, u_short port);

				std::string IP() const;

				u_long NetIP() const;

				u_short Port() const;

				u_short NetPort() const;

				const sockaddr_in& Sockaddr() const;

				void Sockaddr(const sockaddr_in& sin);	

			private:

				sockaddr_in addr_;
		};

	}
}

#endif
