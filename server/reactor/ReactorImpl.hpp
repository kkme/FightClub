#ifndef __REACTOR_IMPL_H
#define __REACTOR_IMPL_H

#include <Epoll.hpp>

using namespace PWRD;

using namespace PWRD::Event;

class Epoll;

namespace PWRD{

	namespace Event{


		class ReactorImpl
		{
			public:
				ReactorImpl(int size);

				void Run();

				void Register(EventHandler* eh, ReactorMask mask);

				void Remove(EventHandler* eh);

				void EnableMask(EventHandler* eh, ReactorMask mask);

				void DisableMask(EventHandler* eh, ReactorMask mask);

			private:

				std::auto_ptr<Epoll> epoll_;
		};
	}
}

#endif 

