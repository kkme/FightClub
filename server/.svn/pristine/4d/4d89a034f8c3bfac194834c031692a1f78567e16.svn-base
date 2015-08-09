#include <AddFriendService.hpp>

namespace PWRD{

	namespace FC{

		/*=========================================================
		 * @protected
		 =========================================================*/
		int AddFriendService::init(){

			return 1;

		}

		int AddFriendService::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/
		int AddFriendService::Process(boost::shared_ptr<C2S_AddFriend> _item UNUSED, EventHandler* _handler){

			Note("New C2S_AddFriend: roleid=%s", _item->roleid().c_str());

			//int roleid = StringTool::Str2Int(_item->roleid());
			
			/*
			boost::shared_ptr<Friend_t> friend_t(new Friend_t());

			char* buf = new char[friend_pb->ByteSize()];

			*buf = 0;

			Head head;

			head.length = friend_pb->ByteSize();

			friend_pb->SerializeToArray(buf, head.length);

			if(ESTABLISHED == Registry::Query(roleid)){

				_handler->Send(head, buf, head.length);

			}

			delete buf;
			*/

			return 1;

		}

	}

}
