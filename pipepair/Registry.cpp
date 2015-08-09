#include <Registry.hpp>

namespace PWRD{

	namespace Event{
		
		HandlerMap* Registry::hmap_ = NULL;

		RuntimeMap* Registry::rmap_ = NULL;

		SyncQueue<Result*>* Registry::syncq_ = NULL;

		Registry* Registry::instance_ = NULL;

		/*
		 * @protected
		 */
		int Registry::init(){

			hmap_ = new HandlerMap();

			assert(NULL != hmap_);

			syncq_ = new SyncQueue<Result*>();

			assert(NULL != syncq_ );

			rmap_ = new RuntimeMap();

			assert(NULL != rmap_);

			return 1;
		}

		int Registry::fini(){

			if(NULL != hmap_){

				delete hmap_;

			}

			if(NULL != rmap_){
				
				delete rmap_;

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

		void Registry::RegisteHandler(EventHandler* _handler, SHELL& _shell){

			assert(NULL != _handler);

			(*hmap_)[_handler] = _shell;

			return;
			
		}

		void Registry::RemoveHandler(EventHandler* _handler){

			/*
			HandlerMap::iterator iter = hmap->begin();

			for(; iter != hmap->end(); iter++){

				if(){

				}

			}
			*/

			if(hmap_->find(_handler) != hmap_->end()){

				Trace("TRACE Remove the EventHandler: handler=%p", _handler);

				hmap_->erase(_handler);

				return;

			}

			Error("Can't find the EventHandler: handler=%p", _handler);

			return;
			
		}

		void Registry::RegisteRuntime(SHELL& _shell, EventHandler* _handler){

			assert(NULL != _handler);
			
			(*rmap_)[_shell] = _handler;

			return;

		}

		void Registry::RemoveRuntime(SHELL& _shell){

			if(rmap_->find(_shell) != rmap_->end()){

				Trace("TRACE Remove the Shell: shell=%s", _shell.c_str());

				rmap_->erase(_shell);

				return;

			}

			Error("Can't find the EventHandler: shell=%s", _shell.c_str());

			return;

		}

		bool Registry::Erase(SHELL _shell){
			

			HandlerMap::iterator it = hmap_->begin();

			EventHandler* handler = NULL;


			for(; it != hmap_->end(); it++){

				if(!_shell.compare(it->second)){

					Trace("TRACE");
					
					handler = it->first;

					if(NULL != handler){

						Note("Delete a Shell: handler=%p, shell=%s", it->first, (it->second).c_str());

						handler->Close();

						return true;

					}

				}

			}

				
			Error("Can't find the SHELL: shell=%s", _shell.c_str());

			return false;

		}

	}//Event

}//PWRD
