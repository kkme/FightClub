#ifndef __REACTORSERVICE_HPP
#define __REACTORSERVICE_HPP

#include <Daemon.hpp>
#include <Reactor.hpp>

using namespace PWRD;
using namespace PWRD::Event;

#define REACTORSIZE 50

namespace PWRD{

	namespace Event{

		class ReactorService{

			public:

				static Reactor* Instance(int _size = REACTORSIZE){

					if(NULL == reactor_){

						Trace("TRACE New Reactor Singleton instance");

						reactor_ = new Reactor(_size);

					}

					return reactor_;

				}

			private:

				static Reactor* reactor_;
		};

	}

}

#endif
