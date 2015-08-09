#include <FightResponseService.hpp>

namespace PWRD{

	namespace FC{

		/*=========================================================
		 * @protected
		 =========================================================*/
		int FightResponseService::init(){

			return 1;

		}

		int FightResponseService::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/
		int FightResponseService::Process(boost::shared_ptr<C2S_FightResponse> _item UNUSED, EventHandler* _handler){

			Note("FightResposne: roleid=%s, froleid=%s", _item->roleid().c_str(), _item->froleid().c_str());

			//int roleid = StringTool::Str2Int(_item->roleid());

			//int froleid = StringTool::Str2Int(_item->froleid());

			EventHandler* buddy = Registry::QueryHandler(_item->roleid());

			//assert(_handler != buddy);

			if(NULL == buddy){
			
				Error("Can't Find Buddy!");

				//+++++++++++++++++++++++++++++++++++++
				//Add NoT Found Status, and send back
				//+++++++++++++++++++++++++++++++++++++

				return -1;


			}

			boost::shared_ptr<S2C_FightResponse> response(new S2C_FightResponse());

			response->set_roleid(_item->roleid());

			response->set_froleid(_item->froleid());

			response->set_ido(_item->ido());

			char* buf = new char[response->ByteSize()];

			*buf = 0;

			Head head;

			head.type = FIGHTRESPONSE;

			head.version = 1;

			*buf = 0;

			head.length = response->ByteSize();

			response->SerializeToArray(buf, head.length);

			if(!_item->ido()){
			
				Note("Player refused! roleid=%s, froleid=%s", _item->roleid().c_str(), _item->froleid().c_str());

			}

			Note("Fight begin: roleid=%s, froleid=%s", _item->roleid().c_str(), _item->froleid().c_str());

			//Send Back
			if(ESTABLISHED == _handler->Connected()){

				_handler->Send(head, buf, head.length);

			}

			//Send to Buddy
			if(ESTABLISHED == buddy->Connected()){

				response->set_roleid(_item->froleid());

				response->set_froleid(_item->roleid());

				head.length = response->ByteSize();

				response->SerializeToArray(buf, head.length);

				buddy->Send(head, buf, head.length);

			}

			delete buf;

			return 1;


		}

	}

}
