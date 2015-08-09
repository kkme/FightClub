#include <PropertyService.hpp>

namespace PWRD{

	namespace FC{

		/*=========================================================
		 * @protected
		 =========================================================*/
		int PropertyService::init(){

			return 1;

		}

		int PropertyService::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/

		int PropertyService::Process(boost::shared_ptr<C2S_Property> _item UNUSED, EventHandler* _handler){


			Note("New Property Request: roleid=%s",  _item->roleid().c_str());

			//int roleid = StringTool::Str2Int(_item->roleid());

			//New Property
			boost::shared_ptr<S2C_Property> property(new S2C_Property());

			boost::shared_ptr<Player> player = PlayerCache::Get(_item->roleid());

			if(NULL == player.get()){
				/*
				 * Add Not Found here
				 */
				int roleid = StringTool::Str2Int(_item->roleid());

				player = SQLImpl::Get(roleid);

				PlayerCache::Registe(player);
				
			}

			property->set_roleid(_item->roleid());

			property->set_rolename(player->GetRoleName());

			property->set_pklevel(player->GetPKLevel());

			property->set_pkexp(player->GetPKExp());

			property->set_ranklevel(player->GetRankLevel());

			property->set_rankexp(player->GetRankExp());

			property->set_money(player->GetMoney());

			property->set_gold(player->GetGold());

			property->set_items(player->GetItems().Serialize());

			//Note("Items: %s", player->GetItems().Serialize().c_str());

			property->set_equips(player->GetEquips().Serialize());

			//Note("Equips: %s", player->GetEquips().Serialize().c_str());

			property->set_buffs(player->GetBuffs().Serialize());

			//Note("Buffs: %s", player->GetBuffs().Serialize().c_str());

			//Send
			Head head;

			head.type = PROPERTY;

			head.version = 1;

			head.length = property->ByteSize();

			char* buf = new char[head.length];

			*buf = 0;

			property->SerializeToArray(buf, head.length);

			if(ESTABLISHED == _handler->Connected()){
			
				_handler->Send(head, buf, head.length);

			}


			delete buf;

			return 1;


		}

	}

}
