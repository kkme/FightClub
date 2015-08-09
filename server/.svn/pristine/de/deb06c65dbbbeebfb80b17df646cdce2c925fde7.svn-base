#include <Scheduler.hpp>
#include <Memorypool.hpp>

namespace PWRD{

	namespace ActiveObject{

		void Scheduler::Dispatch(){

			while(true){

				if(activeq_->AsyncWait() < 0){

					continue;

				}

				//Trace("TRACE Scheduler Run: errno=%d, errmsg=%s", errno, strerror(errno));

				Request *req = activeq_->Dequeue();
				
				if(NULL != req){
					
					req->Call();

					//Note("DEL Addr=%p", req);

					//delete this int Call
					//Memorypool::Instance()->destroy(req);

					delete req;

					req = NULL;
				}

			}

		}

	}

}
