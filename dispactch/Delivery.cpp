#include <Delivery.hpp>

namespace PWRD{

	namespace Network{

		//static mem
		ActiveQueue<Session_t*>* Delivery::activeq_;

		/*===================================
		 * @protected
		 ==================================*/
		
		int Delivery::init(){
		
			activeq_ = new ActiveQueue<Session_t*>();

			assert(NULL != activeq_);

		}

		int Delivery::fini(){


			delete activeq_;

		}

		/*===================================
		 * @public
		 ==================================*/
		
		Delivery* Delivery::Instance(){

			if(NULL == instance_){

				instance_ = new Delivery();

			}

			return instance_;

		}//Instance

		Session_t* Delivery::Dequeue(){

			return activeq_->Dequeue();
		}

		bool Delivery::Enqueue(Sessoin_t* t){
			
			return activeq_->Enqueue(t);

		}

		int Delivery::AsyncWait(){

			return activeq_->AsyncWait();

		}

		int Delivery::Size(){
			
			return activeq_->Size();

		}

	}//Network

}//PWRD
