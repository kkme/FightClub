#include <Head.hpp>

namespace PWRD{

	//===================================================================
	//HeadImpl
	//===================================================================
	int HeadImpl::CheckProtocol(Head &_head){

		if(LOG == _head.type || SQL == _head.type || FB == _head.type ){

			Trace("TRACE Receive a LOG pakage");

			if(_head.length < 0){

				Error("Invaild Head length: length=%d", _head.type);

			}

			if(BUFSIZE < _head.length){

				Error("Message's length beyond the BUFSIZE=%d: head.length=%d", BUFSIZE, _head.length);

				return 0;


			}


			return LOG;

		}
		else if(HA == _head.type){

			//Trace("TRACE Receive a HA pakage");

			return HA;

		}

		Error("Invaild Head type: type=%d", _head.type);

		return -1;

	}

}
