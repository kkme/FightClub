#include <RegisteService.hpp>

namespace PWRD{

	namespace FC{

		/*=========================================================
		 * @protected
		 =========================================================*/
		int RegisteService::init(){

			return 1;

		}

		int RegisteService::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/
		int RegisteService::Process(boost::shared_ptr<C2S_Registe> _item UNUSED, EventHandler* _handler){

			boost::shared_ptr<S2C_Registe> response(new S2C_Registe());

			Note("Registe: rolename=%s, uuid=%s", _item->rolename().c_str(), _item->uuid().c_str());

			//Init DB
			int roleid = SQLImpl::Init(_item->uuid(), _item->rolename(), Time::Now());

			SQLImpl::InitOther(roleid);

			boost::shared_ptr<Player> player = SQLImpl::Get(roleid);

			PlayerCache::Registe(player);

			string roleidstr = StringTool::Int2Str(roleid);

			response->set_roleid(roleidstr);

			//Registry
			Gamer_t gamer(roleidstr, _handler, player->GetPKLevel(), player->GetRankLevel());

			Registry::Registe(gamer);

			//Send
			Head head;

			head.type = REGISTRY;

			head.version = 1;

			head.length = response->ByteSize();

			char* buf = new char[head.length];

			*buf = 0;

			response->SerializeToArray(buf, head.length);

			if(ESTABLISHED == _handler->Connected()){

				_handler->Send(head, buf, head.length);

			}
			else{

				Error("Connection lost: roleid=%d, rolename=%s, uuid=%s", roleid, _item->rolename().c_str(), _item->uuid().c_str());

			}

			delete buf;

			return 1;

		}//Process


	}//FC

}//PWRD
