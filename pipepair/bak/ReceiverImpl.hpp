#ifndef __RECEIVEIMPL_HPP
#define __RECEIVEIMPL_HPP

#include <TaskImpl.hpp>

#include <Registry.hpp>

#include <MonitorMQ.hpp>

#include <TimerQueue.hpp>

using namespace PWRD::RTL;

using namespace PWRD::Monitor;

#define MONITORINTRA 300

namespace PWRD{

	namespace Monitor{

		class ReceiverImpl{

			public:

				ReceiverImpl(ActiveQueue<string*>* _recvq, ActiveQueue<string*>* _resultq):recvq_(_recvq), resultq_(_resultq){ init(); };

				virtual ~ReceiverImpl(){ fini(); };

				void Run();

			protected:

				int init();

				int fini();

			private:

				ActiveQueue<string*>* recvq_;
		
				ActiveQueue<string*>* resultq_;

		};
	
	}

}
#endif
