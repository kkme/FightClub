#ifndef __TIMERQUEUE_HPP
#define __TIMERQUEUE_HPP

#include <map>
using namespace std;

#include <Daemon.hpp>
#include <Global.hpp>
#include <EventHandler.hpp>

using namespace PWRD;
using namespace PWRD::Event;


#define INTERVAL 5

#define HEARTBEAT 5

#define DEFAULTTIMER 15

namespace PWRD{

	namespace Event{

		typedef map<EventHandler*, int> TimeQ;

		class TimerQueue{

			public:

				static TimerQueue* Instance();

				static void Register(EventHandler* _handle, int _intra = DEFAULTTIMER);

				static void Remove(EventHandler* _handle);

				static TimeQ& timeq(){ return timeq_; }

				static int threshold(){ return threshold_; }

				static void Set(int _threshold);

				static void Start(void);

			private:

				static void Run(void);

				static TimeQ timeq_;

				static int threshold_;

				static TimerQueue *instance_;
		};


	}


}

#endif
