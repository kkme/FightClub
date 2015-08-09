#include <QTEService.hpp>

namespace PWRD{

	namespace FC{

		/*=========================================================
		 * @protected
		 =========================================================*/
		int QTEService::init(){

			return 1;

		}

		int QTEService::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/
		int QTEService::Process(boost::shared_ptr<C2S_QTE> _item UNUSED, EventHandler* _handler UNUSED){

			Note("QTE: roleid=%s, froleid=%s", _item->roleid().c_str(), _item->froleid().c_str());

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

			boost::shared_ptr<S2C_QTE> qte(new S2C_QTE());

			qte->set_roleid(_item->roleid());

			qte->set_froleid(_item->froleid());

				for(int index=0; index < _item->qte_size(); index++){
			
				QTE_Beat* beat = qte->add_qte();

				//beat->set_boxing(_item->qte(index).boxing());

				beat->set_hp(_item->qte(index).hp());

				beat->set_during(_item->qte(index).during());

			}

			Note("QTE: roleid=%d, froleid=%d", roleid, froleid);

			char* buf = new char[qte->ByteSize()];

			*buf = 0;

			//Send
			Head head;

			head.type = QTE;

			head.version = 1;

			*buf = 0;

			head.length = qte->ByteSize();

			qte->SerializeToArray(buf, head.length);
			
			if(ESTABLISHED == buddy->Connected()){

				buddy->Send(head, buf, head.length);

			}

			delete buf;

			return 1;


		}

	}

}
