#ifndef _TASKIMPL_HPP

#define _TASKIMPL_HPP

#include <Task.hpp>

#include <EventPipeHandler.hpp>

#include <map>

using namespace std;

using namespace Schedule;

namespace PWRD{

	namespace Schedule{

		class TaskImpl{

			public:

				TaskImpl(string &_json, Reactor& _reactor):json_(_json), reactor_(_reactor){ init(); }

				virtual ~TaskImpl(){ fini(); }

				virtual void run();

				Task* task(){ return task_; }

				EventHandler* eventHandler(){ return eventHandler_; }



			protected:

				virtual int init();

				virtual int fini();



			private:

				Task *task_;

				string json_;

				Reactor &reactor_;

				EventHandler *eventHandler_;



		};

	}

}

#endif

