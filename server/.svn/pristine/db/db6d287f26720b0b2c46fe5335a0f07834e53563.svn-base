#ifndef __SCHEDULER_HPP
#define __SCHEDULER_HPP

#include <Request.hpp>
#include <ActiveQueue.hpp>

using namespace PWRD::ActiveObject;

namespace PWRD{

	namespace ActiveObject{


		class Scheduler{

			public:

				Scheduler(ActiveQueue<Request*> *_activeq):activeq_(_activeq){}

				virtual ~Scheduler(){ activeq_ = NULL; }

				void Dispatch();

			private:

				ActiveQueue<Request*> *activeq_;


		};

	}

}

#endif
