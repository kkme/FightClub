#include <TimeDelayService.hpp>

namespace PWRD{

	namespace FC{

		/*=========================================================
		 * @protected
		 =========================================================*/
		int TimeDelayService::init(){

			return 1;

		}

		int TimeDelayService::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/
		int TimeDelayService::Process(boost::shared_ptr<C2S_TimeStamp> _item UNUSED, EventHandler* _handler){

			boost::shared_ptr<S2C_TimeStamp> timestamp(new S2C_TimeStamp());

			timestamp->set_timestamp(_item->timestamp());


			Note("TimeStamp: time=%s", _item->timestamp().c_str());

			//Send
			Head head;

			head.type = TIMEDELAY;

			head.version = 1;

			char* buf = new char[BUFSIZ];

			*buf = 0;

			head.length = timestamp->ByteSize();

			timestamp->SerializeToArray(buf, head.length);

			_handler->Send(head, buf, head.length);

			delete buf;

			return 1;


		}

	}

}
