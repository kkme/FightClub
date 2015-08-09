#include <algorithm>
#include "./Reactor.hpp"
#include "./ReactorImpl.hpp"
//#include "./Exception.h"

namespace PWRD{

	namespace Event{

		Reactor::Reactor(int size){

			impl_ = new ReactorImpl(size);

		}

		Reactor::~Reactor(){

			delete impl_;

			impl_ = NULL;

		}

		void Reactor::Run(){

			impl_->Run();

		}

		void Reactor::Register(EventHandler* eh, ReactorMask mask){

			impl_->Register(eh, mask);

		}

		void Reactor::Remove(EventHandler* eh){

			impl_->Remove(eh);

		}

		void Reactor::EnableMask(EventHandler* eh, ReactorMask mask){

			impl_->EnableMask(eh, mask);

		}

		void Reactor::DisableMask(EventHandler* eh, ReactorMask mask){

			impl_->DisableMask(eh, mask);

		}

	}

}
