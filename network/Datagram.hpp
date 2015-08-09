/****************************************************************************
 * PWRD socket's reactor library
 * Copyright (c) 2008 by Huang RuiGuang(jiangrg1981@gmail.com)
 *
 * Permission to use, copy, modify, distribute and sell this software.
 *****************************************************************************/

#ifndef __SOCKET_BASIC_DATAGRAM_SOCKET
#define __SOCKET_BASIC_DATAGRAM_SOCKET

#include <SocketType.hpp>
#include <BasicSocket.hpp>

using namespace PWRD::Network;

namespace PWRD{

	namespace Network{

		class Address;

		class  Datagram : public BasicSocket<DatagramType>{

			public:

				Datagram();

				Datagram(const Address& addr);

				virtual ~Datagram(void);

				/**
				 * @brief, receive by blocking io. 
				 */
				int ReceiveN(char* buffer, int length);

				int ReceiveN(char* buffer, int length, Address& addr);

				int SendN(const char* buffer, int length, const Address& addr);

				/**
				 * @brief, receive by nonblocking io.
				 */
				int Receive(char* buffer, int length);

				int Receive(char* buffer, int length, Address& addr);

				int Send(const char* buffer, int length, const Address& addr);

		};
	}
}

#endif


