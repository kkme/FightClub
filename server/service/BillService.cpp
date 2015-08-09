#include <BillService.hpp>

namespace PWRD{

	namespace FC{

		/*=========================================================
		 * @protected
		 =========================================================*/
		int BillService::init(){

			return 1;

		}

		int BillService::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/
		int BillService::Process(boost::shared_ptr<C2S_Bill> _item UNUSED, EventHandler* _handler){

			boost::shared_ptr<S2C_Bill> response(new S2C_Bill());

			boost::shared_ptr<S2C_Gold> resgold(new S2C_Gold());

			//Cache Get
			int roleid = StringTool::Str2Int(_item->roleid());

			boost::shared_ptr<Player> player = PlayerCache::Get(_item->roleid());

			if(NULL == player.get()){

				player = SQLImpl::Get(roleid);

				//PlayerCache
				PlayerCache::Registe(player);

				Note("~~~~~~~~~~~~~~Refresh Bill~~~~~~~~~~~~~");

			}

			//Update Gold
			int gold = player->GetGold();

			//Begin Add some JSON Code
			gold -= 10;
			//End Add some JSON Code
			
			player->SetGold(gold);
			SQLImpl::UpdateGold(roleid, gold);

			//Update Item
			String items = player->GetItems();
			items.SetTotal(_item->itemid(), _item->num());
			player->SetItems(items);
			SQLImpl::InsertBill(roleid, Time::Now(), _item->itemid(), _item->num(), 1, 10);

			//Send Buy Status
			Head head;

			head.type = BILL;
			head.version = 1;

			response->set_roleid(_item->roleid());
			response->set_status(1);

			head.length = response->ByteSize();

			char* buf = new char[head.length];
			*buf = 0;

			response->SerializeToArray(buf, head.length);

			if(ESTABLISHED == _handler->Connected()){

				_handler->Send(head, buf, head.length);
			
			}
			else{

				Error("Connection lost: roleid=%d", roleid);
			
			}

			delete buf;

			//Send Gold
			resgold->set_roleid(_item->roleid());
			resgold->set_gold(gold);

			head.type = GOLD;
			head.version = 1;
			head.length = resgold->ByteSize();

			buf = new char[head.length];
			*buf = 0;

			resgold->SerializeToArray(buf, head.length);

			if(ESTABLISHED == _handler->Connected()){

				_handler->Send(head, buf, head.length);
			
			}
			else{

				Error("Connection lost: roleid=%d", roleid);
			}

			delete buf;

			return 1;

		}//Process


	}//FC

}//PWRD
