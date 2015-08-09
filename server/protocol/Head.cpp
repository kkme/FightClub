#include <Head.hpp>

namespace PWRD{

	//===================================================================
	//HeadImpl
	//===================================================================
	int HeadImpl::CheckProtocol(Head &_head){

		if(REGISTRY == _head.type || FIGHTING == _head.type || FIGHTRESULT == _head.type || HA == _head.type){


			if(_head.length < 0){

				Error("Invaild Head length: length=%d", _head.type);

			}

			if(BUFSIZE < _head.length){

				Error("Message's length beyond the BUFSIZE=%d: head.length=%d", BUFSIZE, _head.length);

				return 0;


			}


			return 1;

		}
		else if(HA == _head.type){

			Trace("TRACE Receive a HA pakage");

			return HA;

		}

		Error("Invaild Head type: type=%d", _head.type);

		return -1;

	}

}
