#include "TaskImpl.hpp"

namespace PWRD{

	namespace Schedule{

		int TaskImpl::init(){

			task_ = new Task(json_);

			if(NULL == task_){

				logs.write_log(NORMAL, "create new task failed!");

				return -1;

			}



			eventHandler_ = new EventPipeHandler(task_->request());

			if(NULL == eventHandler_){

				logs.write_log(NORMAL, "create new eventpipehandler failed!");

				return -1;

			}

			return 1;

		}



		int TaskImpl::fini(){

			if(NULL != task_){

				delete task_;

			}

			reactor_.Remove(eventHandler_);

			return 1;

		}



		void TaskImpl::run(){

			reactor_.Register(eventHandler_, EventHandler::READ_MASK | EventHandler::WRITE_MASK);

			eventHandler_->Start();

		}

	}

}

