/****************************************************************************
 * PWRD socket's reactor library
 * Copyright (c) 2008 by Huang RuiGuang(jiangrg1981@gmail.com)
 *
 * Permission to use, copy, modify, distribute and sell this software.
 *****************************************************************************/

#ifndef __SOCKET_STREAM_H
#define __SOCKET_STREAM_H

#include <SocketType.hpp>
#include <BasicSocket.hpp>

using namespace PWRD::Network;

namespace PWRD{

	namespace Network{

		class  Stream : public BasicSocket<StreamType> {

			public:

				Stream(void);

				~Stream(void);

				/**
				 * @brief, use 'block' io, send @length count bytes.
				 *  if sent succefully, the sent bytes must is @length, otherwise occur error.        
				 * @return, sent bytes; if error occured, throw PWRD::Exception exception.
				 */
				int SendN(const char* buffer, int length);

				/**
				 * @brief, use 'block' io, receive @length bytes.
				 * @return, if return value > 0, is received bytes; 
				 *  == 0, the remote peer is close.
				 *  Occur error, throw PWRD::Exception exception.
				 */
				int ReceiveN(char* buffer, int length);

				/**
				 * @brief, 'nonblock' io, try to send @length bytes.
				 * @return, >0, is sent bytes; 
				 *  == -1, the TCP stack buffer is full and sending is blocking;
				 *  occur error, throw PWRD::Exception. 
				 */
				int Send(const char* buffer, int length);

				/**
				 * @brief, 'nonblock' io, try to receive @length bytes.
				 * @return, > 0, is received bytes;
				 *  == 0, the remove peer is close;
				 *  == -1, the TCP receive buffer is empty, receiving action returns immediately. 
				 *  occur error, throw PWRD::Exception.
				 */
				int Receive(char* buffer, int length);
		};

	}
}

#endif

