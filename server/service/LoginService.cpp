#include <LoginService.hpp>

namespace PWRD{

	namespace FC{

		/*=========================================================
		 * @protected
		 =========================================================*/
		int LoginService::init(){

			return 1;

		}

		int LoginService::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/
		int LoginService::Process(boost::shared_ptr<C2S_Login> _item UNUSED, EventHandler* _handler){

			boost::shared_ptr<S2C_Login> response(new S2C_Login());

			//Check RoleName & UUID
			if(!_item->roleid().compare("")){

				Error("Illagel Player!");

				return -1;

			}//if


			//Cache Get
			int roleid = StringTool::Str2Int(_item->roleid());

			boost::shared_ptr<Player> player = SQLImpl::Get(roleid);


			if(NULL != player.get()){

				//PlayerCache
				PlayerCache::Registe(player);

				//Registry
				Gamer_t gamer(_item->roleid(), _handler, player->GetPKLevel(), player->GetRankLevel());

				Registry::Registe(gamer);

				//Set
				response->set_ok(true);
			}
			else{

				response->set_ok(false);
			
			}

			Head head;

			head.type = LOGIN;

			head.version = 1;

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

			return 1;

		}//Process


	}//FC

}//PWRD
