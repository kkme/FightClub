#include <PKStatService.hpp>

namespace PWRD{

	namespace FC{

		/*=========================================================
		 * @protected
		 =========================================================*/
		int PKStatService::init(){

			return 1;

		}

		int PKStatService::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/
		int PKStatService::Process(boost::shared_ptr<C2S_PKStat> _item UNUSED, EventHandler* _handler){

			boost::shared_ptr<S2C_PKStat> response(new S2C_PKStat());

			Note("PKStat: rolename=%s", _item->roleid().c_str());

			//Registry
			boost::shared_ptr<Gamer_t> gamer = Registry::Get(_item->roleid());

			//Cache Get
			boost::shared_ptr<Player> player = PlayerCache::Get(_item->roleid());

			if(NULL == gamer.get()){

				int roleid = StringTool::Str2Int(_item->roleid());

				player = SQLImpl::Get(roleid);

				//PlayerCache
				PlayerCache::Registe(player);

				//Registry
				Gamer_t agamer(_item->roleid(), _handler, player->GetPKLevel(), player->GetRankLevel());

				Registry::Registe(agamer);

				gamer = Registry::Get(_item->roleid());

				Note("~~~~~~~~~~~~~~Refresh Stat~~~~~~~~~~~~~");

			}

			response->set_roleid(_item->roleid());

			response->set_stat(gamer->stat);

			//Send
			Head head;

			head.type = PKSTAT;

			head.version = 1;

			head.length = response->ByteSize();

			char* buf = new char[head.length];

			*buf = 0;

			response->SerializeToArray(buf, head.length);

			if(ESTABLISHED == _handler->Connected()){

				_handler->Send(head, buf, head.length);

			}
			else{

				Error("Connection lost: roleid=%s", _item->roleid().c_str());

			}

			delete buf;

			return 1;

		}//Process


	}//FC

}//PWRD
