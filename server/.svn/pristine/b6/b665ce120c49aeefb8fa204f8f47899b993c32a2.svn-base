/****************************************************************************
 * PWRD socket's reactor library
 * Copyright (c) 2008 by Huang RuiGuang(jiangrg1981@gmail.com)
 *
 * Permission to use, copy, modify, distribute and sell this software.
 *****************************************************************************/

#ifndef __EVENT_HANDLER_H
#define __EVENT_HANDLER_H

#include <Global.hpp>
#include <Daemon.hpp>
#include <Head.hpp>

using namespace PWRD;

namespace PWRD{

	namespace Event{

		typedef __uint32_t ReactorMask; 

		typedef enum{

			ESTABLISHED, 

			ONCONNECT,

			CLOSED,

			CLOSEWAIT,

			NONEXIST


		}CONNSTAT;


		class EventHandler
		{

			public:

				enum 
				{

					COMMON_READ_MASK = EPOLLIN,

					COMMON_WRITE_MASK = EPOLLOUT

				};

				enum
				{
					READ_MASK = COMMON_READ_MASK,

					WRITE_MASK = COMMON_WRITE_MASK,

					ALL_EVENTS_MASK = READ_MASK | WRITE_MASK

				};

				virtual ~EventHandler(){}

				virtual Handle GetHandle() const = 0;

				virtual void Start();

				virtual int Receive();

				virtual int Send();

				virtual int Close();

				virtual int Execute();

				virtual int Timeout(bool&);

				virtual bool Flag(){ return true;}

				virtual CONNSTAT Connected(){ return CLOSED; };

				virtual int Send(Head& _head, const char* _buf, int length);
		};
	}
}

#endif

