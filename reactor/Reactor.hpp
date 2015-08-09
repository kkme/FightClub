/****************************************************************************
 * PWRD socket's reactor library
 * Copyright (c) 2008 by Huang RuiGuang(jiangrg1981@gmail.com)
 *
 * Permission to use, copy, modify, distribute and sell this software.
 *****************************************************************************/

#ifndef __REACTOR_H
#define __REACTOR_H

#include "EventHandler.hpp"

#include "ReactorImpl.hpp"

using namespace PWRD::Event;

namespace PWRD{

	namespace Event{

		class Reactor {

			public:

				Reactor(int size = 0);

				~Reactor();

				void Run();

				void Register(EventHandler* eh, ReactorMask mask);

				void Remove(EventHandler* eh);

				void EnableMask(EventHandler* eh, ReactorMask mask);

				void DisableMask(EventHandler* eh, ReactorMask mask);

			private:

				ReactorImpl* impl_;
		};
	}
}

#endif

