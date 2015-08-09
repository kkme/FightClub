#include <FightResultService.hpp>

namespace PWRD{

	namespace FC{

		/*=========================================================
		 * @protected
		 =========================================================*/
		int FightResultService::init(){

			return 1;

		}

		int FightResultService::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/
		int FightResultService::Process(boost::shared_ptr<C2S_FightResult> _item UNUSED, EventHandler* _handler){

			Note("New C2S_FightResult: roleid=%s, froleid=%s", _item->roleid().c_str(), _item->froleid().c_str());

			//int roleid = StringTool::Str2Int(_item->roleid());

			//int froleid = StringTool::Str2Int(_item->froleid());

			EventHandler* buddy = Registry::QueryHandler(_item->froleid());

			if(NULL == buddy){
			
				Error("Can't Find Buddy!");

				//+++++++++++++++++++++++++++++++++++++
				//Add NoT Found Status, and send back
				//+++++++++++++++++++++++++++++++++++++

				return -1;


			}

			boost::shared_ptr<S2C_FightResult> response(new S2C_FightResult());

			response->set_roleid(_item->roleid());

			response->set_froleid(_item->froleid());

			response->set_win(_item->win());

			response->set_type(_item->type());

			response->set_equipment(_item->equipment());

			char* buf = new char[response->ByteSize()];

			*buf = 0;

			//Send
			Head head;

			head.type = FIGHTRESULT;

			head.version = 1;

			*buf = 0;

			head.length = response->ByteSize();

			//Win
			if(_item->win()){
			
				response->SerializeToArray(buf, head.length);


				if(ESTABLISHED == _handler->Connected()){

					_handler->Send(head, buf, head.length);

				}

				response->set_roleid(_item->froleid());

				response->set_froleid(_item->roleid());

				response->set_win(false);


				response->SerializeToArray(buf, head.length);

				if(ESTABLISHED == buddy->Connected()){

					buddy->Send(head, buf, head.length);

				}
			}
			//Lose
			else{

				response->SerializeToArray(buf, head.length);

				if(ESTABLISHED == _handler->Connected()){

					_handler->Send(head, buf, head.length);

				}

				response->set_roleid(_item->froleid());

				response->set_froleid(_item->roleid());

				response->set_win(true);

				response->set_type(_item->type());

				response->set_equipment(_item->equipment());

				response->SerializeToArray(buf, head.length);

				if(ESTABLISHED == buddy->Connected()){

					buddy->Send(head, buf, head.length);
					
				}

			}

			delete buf;

			return 1;


		}

	}

}
