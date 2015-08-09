#include <Error.hpp>

namespace PWRD{

	namespace Error{

		//===================================================================
		// @private
		//===================================================================
		Error* Error::instance_ = NULL;

		//===================================================================
		// @protected
		//===================================================================
		int Error::init(){

			return 1;

		} //init

		int Error::fini(){

			return 1;

		} //fini

		//===================================================================
		// @public
		//===================================================================
		Error* Error::Instance(){

			if(NULL == instance_){

				instance_ = new Error();

			}

			return instance_;
			

		} //Instance

		int Error::Send(ERRORTYPE _type, EventHandler* _handler){

			S2C_Error error;

			error.set_type = _type;
			
			Head head;

			head.type = ERROR;


			head.version = 1;

			head.length = error.ByteSize();

			char buf[head.length];

			error.SerializeToArray(buf, head.length);

			if(ESTABLISHED == _handler->Connected()){

				_handler->Send(head, buf, head.length);

				Note("Send Error Code: %d", _type);

			}


		} //Send

	} //Error

} //PWRD

