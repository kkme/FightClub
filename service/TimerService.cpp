#include <TimerSerivce.hpp>

namespace PWRD{

	namespace MoM{

		void TimerSerivce::Run(){

			Trace("TRACE TimerSerivce Run");

			service_.run();

		}

	}

}
