#include <cassert>
#include "Exception.hpp"

#include "Epoll.hpp"

namespace PWRD{

	namespace Event{

		Epoll::Epoll(int size)
		{
			assert(size != 0);

			epfd_ = epoll_create(size);

			if (epfd_ == -1)

				throw Exception("Create epoll failed, ");


			size_ = size;

			evts_ = new struct epoll_event[size];

			gettimeofday(&before_, NULL);

		}

		Epoll::~Epoll()
		{
			close(epfd_);

			delete[] evts_;

		}

		void Epoll::DispatchEvent()
		{
			int fds = epoll_wait(epfd_, evts_, size_, 1000); 

			if (fds == -1){

				if (errno == EINTR)
					return;

				throw Exception("Epoll epoll_wait failed, ");

			}

			for (int i = 0; i < fds; ++i)
			{

				EventHandler* handler = reinterpret_cast<EventHandler*>(evts_[i].data.ptr);

				if (evts_[i].events & EventHandler::READ_MASK)
				{

					if (handler->Receive() == -1)

						handler->Close();

				}

				if (evts_[i].events & EventHandler::WRITE_MASK)
				{

					if (handler->Send() == -1){

						Trace("TRACE SENDSENDSENDSENDSENDSENDSENDSENSEND");

						handler->Close();

					}


				}
			}

			//timer: gettimeofday
			gettimeofday(&now_, NULL);

			if(now_.tv_sec - before_.tv_sec >= INTERVAL){

				TimeQ::iterator iter = TimerQueue::timeq().begin();

				//Note("TimeQueue: sum=%d, handler=%p, silde=%d", TimerQueue::timeq().size(), handler, iter->second);
				for(; iter != TimerQueue::timeq().end(); ){

					EventHandler* handler = iter->first;	


					iter->second = iter->second - INTERVAL;

					if(0 == (iter->second % HEARTBEAT)){

						//heartbeat

						if(NULL != handler){

							handler->SendHeartbeat();

						}

					}

					bool flag = false;

					TimeQ::iterator it = iter;

					it++;


					if(iter->second - INTERVAL < 0){


						if(NULL != handler){

							handler->Timeout(flag);						
						}

						iter->second = TimerQueue::threshold();

					}

					iter = it;
				}

				gettimeofday(&before_, NULL);

			}

		}

		void Epoll::Register(EventHandler* eh, ReactorMask mask) {

			//if (!OperateHandler(EPOLL_CTL_ADD, eh, mask | EPOLLET)){
			if (!OperateHandler(EPOLL_CTL_ADD, eh, mask)){

				throw Exception("Register failed, ");

			}

		}

		void Epoll::Remove(EventHandler* eh){

			//if (!OperateHandler(EPOLL_CTL_DEL, eh, ALL_EVENTS_MASK | EPOLLET))
			if (!OperateHandler(EPOLL_CTL_DEL, eh, EventHandler::ALL_EVENTS_MASK))

				throw Exception("Remove failed, ");

		}

		void Epoll::EnableMask(EventHandler* eh, ReactorMask mask) {

			//if (!OperateHandler(EPOLL_CTL_MOD, eh, mask | EPOLLET))
			if (!OperateHandler(EPOLL_CTL_MOD, eh, mask))

				throw Exception("EnableMask failed, ");

		}

		void Epoll::DisableMask(EventHandler* eh, ReactorMask mask) {

			if (!OperateHandler(EPOLL_CTL_DEL, eh, mask))

				throw Exception("DisableMask failed, ");

		}

		}

	}

