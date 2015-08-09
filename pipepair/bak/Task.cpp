#include "Task.hpp"

namespace PWRD{

	namespace Schedule{

		int Task::init(){

			if(!request_.parse(json_)){

				Error("request parsed failed: json=%s", json_.c_str());

				return -1;

			}

			return 1;

		}



		int Task::fini(){

			return 1;

		}

	}

}

