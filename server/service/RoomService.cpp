#include <RoomService.hpp>

namespace PWRD{

	namespace FC{

		/*=========================================================
		 * @protected
		 =========================================================*/
		int RoomService::init(){

			return 1;

		}

		int RoomService::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/
		int RoomService::Process(boost::shared_ptr<C2S_Room> _item UNUSED, EventHandler* _handler){

			boost::shared_ptr<S2C_Room> response(new S2C_Room());

			//Check RoleName & UUID
			if(!_item->roleid().compare("")){

				Error("Illagel Player!");

				return -1;

			}//if


			//Send
			response->set_roleid(_item->roleid());
			response->set_online(Registry::Size());
			Conf* conf = Conf::GetInstance();
			response->set_bulletin(conf->find("Game", "bulletin"));
			response->set_mail(4);

			Head head;

			head.type = ROOM;

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
