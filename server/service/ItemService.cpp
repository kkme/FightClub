#include <ItemService.hpp>

namespace PWRD{

	namespace FC{

		/*=========================================================
		 * @protected
		 =========================================================*/
		int ItemService::init(){

			return 1;

		}

		int ItemService::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/
		int ItemService::Process(boost::shared_ptr<C2S_Item> _item UNUSED, EventHandler* _handler UNUSED){

			Note("Item: roleid=%s, froleid=%s", _item->roleid().c_str(), _item->froleid().c_str());

			int roleid = StringTool::Str2Int(_item->roleid());

			int froleid = StringTool::Str2Int(_item->froleid());

			EventHandler* buddy = Registry::QueryHandler(_item->froleid());

			if(NULL == buddy){

				Error("Can't Find Buddy!");

				//+++++++++++++++++++++++++++++++++++++
				//Add NoT Found Status, and send back
				//+++++++++++++++++++++++++++++++++++++

				return -1;

			}

			boost::shared_ptr<S2C_Item> response(new S2C_Item());

			response->set_roleid(_item->roleid());

			response->set_froleid(_item->froleid());

			response->set_itemid(_item->itemid());

			Note("Item: roleid=%d, froleid=%d", roleid, froleid);

			char* buf = new char[response->ByteSize()];

			*buf = 0;

			//Send
			Head head;

			head.type = ITEM;

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
