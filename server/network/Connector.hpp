/****************************************************************************
 * PWRD socket's reactor library
 * Copyright (c) 2008 by Huang RuiGuang(jiangrg1981@gmail.com)
 *
 * Permission to use, copy, modify, distribute and sell this software.
 *****************************************************************************/

#ifndef __SOCKET_CONNECTOR_H
#define __SOCKET_CONNECTOR_H

#include <SocketType.hpp>

using namespace PWRD::Network;

namespace PWRD{

	namespace Network{

		class Stream;

		class Address;

		class  Connector {

			public:

				Connector(void);

				~Connector(void);

				void Connect(const Address& remoteAddr, Stream& s);
		};

	}
}

#endif

