#include "EventHandler.hpp"

namespace PWRD{
	namespace Event{

		int EventHandler::Receive() {

			return 0;
		}

		int EventHandler::Send() {

			return 0;

		}

		int EventHandler::Send(Head& _head UNUSED, const char* _buf UNUSED, int length UNUSED) {

			return 0;

		}


		int EventHandler::Close() {

			return 0;

		}

		int EventHandler::Execute(){

			return 0;

		}

		int EventHandler::Timeout(bool&){

			return 0;

		}

		void EventHandler::Start(){

		}
	}
}

