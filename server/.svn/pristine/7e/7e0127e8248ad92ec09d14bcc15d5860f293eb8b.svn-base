#include <FriendListService.hpp>

namespace PWRD{

	namespace FC{

		/*=========================================================
		 * @protected
		 =========================================================*/
		int FriendListService::init(){

			return 1;

		}

		int FriendListService::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/
		int FriendListService::Process(boost::shared_ptr<C2S_Friend> _item UNUSED, EventHandler* _handler){

			Note("New C2S_FriendList: roleid=%s", _item->roleid().c_str());

			//int roleid = StringTool::Str2Int(_item->roleid());
			
			boost::shared_ptr<S2C_Friend> friends(new S2C_Friend());

			//New Property
			boost::shared_ptr<Player> player = PlayerCache::Get(_item->roleid());

			if(NULL == player.get()){
				/*
				 * Add Not Found here
				 */

				int roleid = StringTool::Str2Int(_item->roleid());

				player = SQLImpl::Get(roleid);

				//PlayerCache
				PlayerCache::Registe(player);

				Note("~~~~~~~~~~~~~~Refresh Friend~~~~~~~~~~~~~");
				
			}

			friends->set_roleid(_item->roleid());

			String fs = player->GetFriends();

			if(_item->has_num()){
				
				Note("===============Friends: %s=============", fs.GetKeys(_item->num()).c_str());

				friends->set_flist(fs.GetKeys(_item->num()));

			}
			else if(_item->has_index()){

				Note("===============Friends: %s=============", fs.GetKeys(_item->index(), _item->length()).c_str());

				friends->set_flist(fs.GetKeys(_item->index(), _item->length()));

			}
			else{
				
				Note("===============Friends: %s=============", fs.GetKeys().c_str());

				friends->set_flist(fs.GetKeys());

			}

			Head head;

			head.type = FRIENDLIST;

			head.version = 1;

			head.length = friends->ByteSize();

			char* buf = new char[friends->ByteSize()];

			*buf = 0;

			friends->SerializeToArray(buf, head.length);

			if(ESTABLISHED == _handler->Connected()){
			
				_handler->Send(head, buf, head.length);

			}

			delete buf;

			return 1;

		}

	}

}
