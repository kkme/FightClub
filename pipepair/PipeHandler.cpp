#include <PipeHandler.hpp>

namespace PWRD{

	namespace Event{

		/*
		 * @protected
		 */
		int PipeHandler::init(){

			*buf_ = 0;

			xmlbuilder_ = new ConfBuilder();

			assert(NULL != xmlbuilder_);

			return 1;

		}

		int PipeHandler::fini(){

			delete xmlbuilder_;

			return 1;

		}

		/*
		 * @public
		 */
		int PipeHandler::Open(int _intra){

			ReactorService::Instance()->Register(this, EventHandler::READ_MASK);

			Note("PipeHandler Register: infd=%d", infd_);

			TimerQueue::Register(this, _intra);

			return 1;

		}

		int PipeHandler::Receive(){

			int len = 0;

			//Note("==========================================");

			int bytes = read(infd_, &len, sizeof(int));

			assert(sizeof(int) == bytes);

			bytes = read(infd_, buf_, len);

			if(0 == bytes){

				Error("File descriptor was closed: fd=%s", infd_);

				return -1;

			}
			else if(-1 == bytes){

				if(EAGAIN == errno || EINTR == errno){

					return 0;

				}

			}
			else{

				buf_[bytes] = 0;


				Note("Receive#############: buf=%s", buf_);

				path_.assign(buf_);

				xmlbuilder_->set_file(path_);

				//Load XML
				xmlbuilder_->Load();

				//Compare the two maps
				ScriptMap& xmap = xmlbuilder_->scripts();

				ScriptMap::iterator xit = xmap.begin();

				RuntimeMap* rmap = Registry::rmap();

				RuntimeMap::iterator rit = rmap->begin();

				//ProgMap in the RuntimeMap 
				for(; xit != xmap.end(); xit++){

					if(rmap->end() != rmap->find(xit->first)){

						Trace("TRACE Shell exists!: shell=%s", (xit->first).c_str());


					}
					else{ 

						//New Shell
						Note("New Shell coming: shell=%s, timeout=%d", (xit->first).c_str(), xit->second);

						//Get pair: <type, timer>
						Pair pair = xit->second;

						//To add timer, server
						EventPipeHandler* handler = new EventPipeHandler(pair.first, xmlbuilder_->path(), xit->first, pair.second, xmlbuilder_->ip()); //type, shell, timer, taskid, server

						assert(NULL != handler);

						handler->Open();

						
					}


				}

				//RuntimeMap in the ProMap
				for(; rit != rmap->end(); rit++){
					
					if(xmap.end() != xmap.find(rit->first)){

						Trace("TRACE Shell exists!: shell=%s", (rit->first).c_str());

					}
					else{
						
						Registry::Erase(rit->first);

					}

				}

			}

			return 1;



		}

		int PipeHandler::Send(){

			return 1;

		}

		int PipeHandler::Close(){

			return 1;

		}

		int PipeHandler::Timeout(bool& _flag UNUSED){

			Note("===================Timeout====================");

			return 1;
		}


	}//Event

}//PWRD
