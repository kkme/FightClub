#include <FightRequestService.hpp>

namespace PWRD{

	namespace FC{

		/*=========================================================
		 * @protected
		 =========================================================*/
		int FightRequestService::init(){

			return 1;

		}

		int FightRequestService::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/
		int FightRequestService::Process(boost::shared_ptr<C2S_FightRequest> _item UNUSED, EventHandler* _handler){


			Note("FightRequest : roleid=%s, froleid=%s", _item->roleid().c_str(), _item->froleid().c_str());

			//int roleid = StringTool::Str2Int(_item->roleid());

			//int froleid = StringTool::Str2Int(_item->froleid());

			boost::shared_ptr<S2C_FightRequest> response(new S2C_FightRequest());

			EventHandler* buddy = Registry::QueryHandler(_item->froleid());

			if(NULL == buddy){
			
				Error("Can't Find Buddy!");

				//+++++++++++++++++++++++++++++++++++++
				//Add NoT Found Status, and send back
				//+++++++++++++++++++++++++++++++++++++

				return -1;

			}

			response->set_roleid(_item->roleid());

			response->set_froleid(_item->froleid());

			char* buf = new char[response->ByteSize()];

			*buf = 0;

			//Send
			Head head;

			head.type = FIGHTREQUEST;

			head.version = 1;

			*buf = 0;

			head.length = response->ByteSize();

			response->SerializeToArray(buf, head.length);

			if(ESTABLISHED == _handler->Connected()){

				_handler->Send(head, buf, head.length);
			
			}

			if(ESTABLISHED == Registry::QueryHandler(_item->froleid())->Connected()){

				buddy->Send(head, buf, head.length);

			}

			delete buf;

			return 1;


		}

	}

}
