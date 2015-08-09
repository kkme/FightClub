#include <Request.hpp>

namespace PWRD{

	namespace ActiveObject{


		int Request::init(){

			buf_ = NULL;

			if(NULL == buffer_){

				Error("Request buf is NULL");

				return -1;


			}
			else{

				if(len_ > BUFSIZE){

					Error("Recieve a huge package: buf=%p, len=%d", buffer_, len_);

					return -1;

				}

				Trace("TRACE Request Init: buf=%p, len=%d", buffer_, len_);

				//buf_ = Stringpool::Instance()->construct(buffer_, len_);
				buf_ = new string(buffer_, len_);

			}

			
			return 1;
		}

		int Request::fini(){
			
			if(NULL != buf_){

				delete buf_;

				//Stringpool::Instance()->destroy(buf_);

				buf_ = NULL;
				
			}

			return 1;
		}

		bool Request::Call(){

			Trace("TRACE Request Call");

			if(!record_.ParseFromString(*buf_)){

				Error("Parse the LogRecord failed");

				return -1;

			}


			ActiveLogRecord::Log(record_.type(), record_.server(), record_.process(), record_.message());

			return true;

		}

	}

}
