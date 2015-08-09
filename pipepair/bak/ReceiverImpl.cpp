#include <ReceiverImpl.hpp>

namespace PWRD{

	namespace Monitor{

		/*
		 * @public
		 */
		void ReceiverImpl::Run(){

			while(recvq_->AsyncWait() < 0){

				Error("");

				continue;
			
			}

			string* str = recvq_->Dequeue();

			Trace("Receive reqeust: str=%s", str->c_str());

			if(NULL != str ){
			
				Taske *task = new Task(str);

				if(NULL == task){

					Error("New Task failed!");

					return;
				
				}

				EventPipeHandler* ep = new EventPipeHandler(task, resultq_);

				if(NULL = ep){
				
					Error("New EventPipeHandler failed!");

					return;

				}

				Request& request = task->request();

				int id = requset.id();

				Registry::Instance()->Register(id, ep);

				int intra = request.intra();

				if(intra < 0) intra = MONITORINTRA;

				TimerQueue::Instance()->Register(ep, intra);
			
			}

			
		}

		/*
		 * @protected
		 */
		int ReceiverImpl::init(){

			return 1;
		
		}

		int ReceiverImpl::fini(){
		
			return 1;
		}
	
	}
	
}
