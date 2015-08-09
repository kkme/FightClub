/**
 * Epoll.h
 * Manager epoll IO model.
 * Author: HuangRuiGuang
 */

#ifndef __EPOLL_H
#define __EPOLL_H

#include <sys/epoll.h>

#include <Daemon.hpp>

#include <SocketDef.hpp>

#include <EventHandler.hpp>

#include <TimerQueue.hpp>

using namespace PWRD;

using namespace PWRD::Event;

namespace PWRD{

	namespace Event{

		typedef struct timeval TimeVal;

		class Epoll {

			public:

				Epoll(int size);

				~Epoll();

				void DispatchEvent();

				void Register(EventHandler* eh, ReactorMask mask);

				void Remove(EventHandler* eh);

				/**
				 * @brief enable masks.
				 */
				void EnableMask(EventHandler* eh, ReactorMask mask);

				void DisableMask(EventHandler* eh, ReactorMask mask);

			private:

				inline bool OperateHandler(int op, EventHandler* eh, ReactorMask mask) {

					struct epoll_event evt;

					evt.data.ptr = eh;

					evt.events = mask;

					return epoll_ctl(epfd_, op, eh->GetHandle(), &evt) != -1;

				}

			private:

				int epfd_;

				int size_;

				TimeVal now_;

				TimeVal before_;

				struct epoll_event *evts_;

		};
	}
}

#endif

