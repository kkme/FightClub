#include <FileService.hpp>

namespace PWRD{

	namespace Logic{

		/*
		 * @protected
		 */
		int FileService::init(){

			sink_ = new FileSink(outfd_);

			assert(sink_ != NULL);

			return 1;

		}

		int FileService::fini(){

			if(NULL != sink_){

				delete sink_;

			}

			return 1;

		}

		/*
		 * @public
		 */
		void FileService::Run(){

			while(true){

				if(aqueue_->AsyncWait() < 0){

					continue;
				}

				FileBlock* block = aqueue_->Dequeue();

				if(NULL == block){

					Error("File Block is NULL");	

					return;

				}

				sink_->Process(block);

				//return;

			}


		}


	}//MoM

}//PWRD
