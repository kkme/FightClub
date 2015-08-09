/****************************************************************************
 * PWRD socket's reactor library
 * Copyright (c) 2008 by Huang RuiGuang(jiangrg1981@gmail.com)
 *
 * Permission to use, copy, modify, distribute and sell this software.
 *****************************************************************************/

#ifndef __SOCKET_ACCEPTOR_H
#define __SOCKET_ACCEPTOR_H

#include <SocketType.hpp>
#include <BasicSocket.hpp>

using namespace PWRD::Network;

namespace PWRD{

	namespace Network{

		class Stream;

		class  Acceptor : public BasicSocket<StreamType>
		{
			public:

				Acceptor(const Address& addr);

				~Acceptor(void);

				void Accept(Stream& s);

				void Accept(Stream& s, Address& addr);

		};

	}
}

#endif
