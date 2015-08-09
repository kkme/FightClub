#include <HardBeatService.hpp>

namespace PWRD{

	namespace FC{

		/*=========================================================
		 * @protected
		 =========================================================*/
		int HardBeatService::init(){

			return 1;

		}

		int HardBeatService::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/
		int HardBeatService::Process(boost::shared_ptr<C2S_HardBeat> _item UNUSED, EventHandler* _handler UNUSED){

			Note("HardBeat: roleid=%s, froleid=%s", _item->roleid().c_str(), _item->froleid().c_str());

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

			boost::shared_ptr<S2C_HardBeat> response(new S2C_HardBeat());

			response->set_roleid(_item->roleid());

			response->set_froleid(_item->froleid());

			Beat* beat = response->mutable_beat();

			assert(NULL != beat);

			beat->set_hp(_item->beat().hp());

			beat->set_animation(_item->beat().animation());


			//response->set_boxing(_item->boxing());

			//response->set_hp(_item->hp());

			//response->set_item(_item->item());

			char* buf = new char[response->ByteSize()];

			*buf = 0;

			//Send
			Head head;

			head.type = HARDBEAT;

			head.version = 1;

			*buf = 0;

			head.length = response->ByteSize();

			response->SerializeToArray(buf, head.length);
			
			if(ESTABLISHED == buddy->Connected()){

				buddy->Send(head, buf, head.length);

			}

			delete buf;

			return 1;


		}

	}

}
