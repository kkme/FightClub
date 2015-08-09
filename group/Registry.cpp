#include <Registry.hpp>

namespace PWRD{

	namespace Event{

		CacheMap*  Registry::chmap_ = NULL;
		
		SessionMap* Registry::sgmap_ = NULL;

		Registry* Registry::instance_ = NULL;

		SyncQueue<Result*>* Registry::syncq_ = NULL;

		/*
		 * @protected
		 */
		int Registry::init(){

			chmap_ = new CacheMap(); 

			sgmap_ = new SessionMap();

			assert(NULL != sgmap_);

			syncq_ = new SyncQueue<Result*>();

			assert(NULL != syncq_);

			return 1;
		}

		int Registry::fini(){

			if(NULL != sgmap_){

				delete sgmap_;

			}

			if(NULL != syncq_)

				delete syncq_;

			return 1;

		}


		/*
		 * @public
		 */
		Registry* Registry::Instance(){

			if(instance_ == NULL){
				
				instance_ = new Registry();

			}

			return instance_;


		}

		void Registry::Initialize(HANDLER _handler, string _uid){

			assert(NULL != _handler);
			
			//load property from db
			Property* property = PropertyImpl::Get(_uid);

			if(NULL = property){

				Error("Can't find the user: uid=%s", _uid.c_str());

				return;

			}

			SG sg = new SessionGroup;

			sg->property = property;

			sg->stat = IDLE;

			sg->uid = _uid;

			mutex_.Lock();

			(*sgmap_)[_handler] = sg;

			mutex_.UnLock();

			return;

		}

		void Registry::RegisteHandler(HANDLER _handler, HANDLER _buddy){

			assert(NULL != _buddy);

			assert(NULL != _handler);

			SG sg = sgmap_[_handler];

			assert(NULL != sg);

			sg->buddy = _buddy;
			
			return;
			
		}

		void Registry::RemoveHandler(HANDLER _handler){

			assert(NULL != _handler);

			mutex_.Lock();

			SG sg = (*sgmap_)[_handler];

			assert(NULL != sg);


			(*sgmap_)[_handler] = NULL;

			sgmap_->erase(_handler);

			mutex_.UnLock();


			//if STAT==FIGHT, tell his buddy, i'm lost
			if(FIGHT == _handler){
				
				HANDLER buddy = sg->buddy;

				assert(NULL != buddy);

				buddy->SendLost();

				//clear buddy's buddy

				SG sgb = (*sgmap_)[buddy];

				assert(NULL != sgb);

				sgb->buddy = NULL;

				sgb->stat = IDLE; 

			}

			assert(NULL != sg->property);

			delete sg->property;

			delete sg;

			return;
			
		}

		void Registry::RegistrCache(string _id, HANDLER _handler){
			
			Note("Register a user: userid=%s, session=%p", _id.c_str(), _handler);

			(*chmap_)[_id] = _handler;

			return;
		}

		void Registry::RemoveCache(string _id){
			

			Note("Remove a user: userid=%s", _id.c_str());

			chmap_->erase(_id);

			return ;
		}

	}//Event

}//PWRD
