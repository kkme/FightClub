#include "EventHandler.hpp"

#include "ReactorImpl.hpp"

namespace PWRD{

	namespace Event{

		ReactorImpl::ReactorImpl(int size) : epoll_(new Epoll(size)) { }

		void ReactorImpl::Run() {

			while (true)

				epoll_->DispatchEvent();

		}

		void ReactorImpl::Register(EventHandler* eh, ReactorMask mask){

			epoll_->Register(eh, mask);

		}

		void ReactorImpl::Remove(EventHandler* eh) {

			epoll_->Remove(eh);

		}

		void ReactorImpl::EnableMask(EventHandler* eh, ReactorMask mask){

			epoll_->EnableMask(eh, mask);

		}

		void ReactorImpl::DisableMask(EventHandler* eh, ReactorMask mask){

			epoll_->DisableMask(eh, mask);

		}

	}

}

