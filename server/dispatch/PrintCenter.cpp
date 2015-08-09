#include <PrintCenter.hpp>

namespace PWRD{

	namespace FC{

		PrintCenter* PrintCenter::instance_ = NULL;

		int PrintCenter::hp_ = 10;

		int PrintCenter::hhp_ = 20;

		string PrintCenter::animation_ = "animation_01";

		string PrintCenter::hanimation_ = "animation_01";

		void PrintCenter::Run(){

			while(true){

				Note("PrintCenter Start!");

				while(ActiveQueueSigalton<Packet*>::Queue()->AsyncWait() < 0){

					//Error("ActiveQueueSigalton::Queue()->AsyncWait() failed!");

					continue;

				}

				Packet* packet = ActiveQueueSigalton<Packet*>::Queue()->Dequeue();

				Note("Get a new Packet: type=%d, len=%d", packet->type, packet->len);

				assert(NULL != packet);

				Process((EventHandler*)packet->handler, packet->type, packet->buf, packet->len);

			}

		}

		int PrintCenter::Process(EventHandler* _handler, TYPE _type, const char* _buf, int _len){

			assert(NULL != _handler);

			assert(NULL != _buf);


			if(_len < 0){

				Note("Version is up to date");

				return 1;

			}

			switch (_type){

				case PROPERTY:

				{
						Note("===============PROPERTY===============");

						//Query property
						S2C_Property* item = new S2C_Property();

						if(NULL == item){

							Error("New RegistryItem failed: len=%d",  _len);

							return -1;

						}

						if(!item->ParseFromArray(_buf, _len)){

							Error("Protocol Buffer parse failed!");

							return -1;

						}

						Print(item);

						delete item;
				
				}

					break;

				case PKLIST:

					{
						Note("===============S2C_PKList===============");

						//Query property
						S2C_PKList* item = new S2C_PKList();

						if(NULL == item){

							Error("New S2C_PKList failed: len=%d",  _len);

							return -1;

						}

						if(!item->ParseFromArray(_buf, _len)){

							Error("Protocol Buffer parse failed!");

							return -1;

						}

						Print(item);

					}

					break;

				case PKSTAT:

					{
						Note("===============S2C_PKStat===============");

						//Query property
						S2C_PKStat* item = new S2C_PKStat();

						if(NULL == item){

							Error("New S2C_PKStat failed: len=%d",  _len);

							return -1;

						}

						if(!item->ParseFromArray(_buf, _len)){

							Error("Protocol Buffer parse failed!");

							return -1;

						}

						Print(item);

					}

					break;
				case LOGIN:
					{

						Note("===============LOGIN===============");

						//Query property
						S2C_Login* item = new S2C_Login();

						if(NULL == item){

							Error("New RegistryItem failed: len=%d",  _len);

							return -1;

						}

						if(!item->ParseFromArray(_buf, _len)){

							Error("Protocol Buffer parse failed!");

							return -1;

						}

						Print(item);

						delete item;

					}

					break;

				case REGISTRY:

					{

						Note("===============REGISTRY===============");

						//Query property
						S2C_Registe* item = new S2C_Registe();

						if(NULL == item){

							Error("New RegistryItem failed: len=%d",  _len);

							return -1;

						}

						if(!item->ParseFromArray(_buf, _len)){

							Error("Protocol Buffer parse failed!");

							return -1;

						}

						Print(item);

						delete item;

					}

					break;

				case FRIENDLIST:

					{

						Note("===============FRIENDLIST===============");

						//Query property
						S2C_Friend* item = new S2C_Friend();

						if(NULL == item){

							Error("New RegistryItem failed: len=%d",  _len);

							return -1;

						}

						if(!item->ParseFromArray(_buf, _len)){

							Error("Protocol Buffer parse failed!");

							return -1;

						}

						Print(item);

						delete item;

					}

					break;

				case FIGHTREQUEST:

					{

						Note("===============REQUEST===============");

						//Query property
						C2S_FightRequest* item = new C2S_FightRequest();

						if(NULL == item){

							Error("New RegistryItem failed: len=%d",  _len);

							return -1;

						}

						if(!item->ParseFromArray(_buf, _len)){

							Error("Protocol Buffer parse failed!");

							return -1;

						}

						WriteRequest(item, _handler);

						delete item;

					}

					break;

				case FIGHTRESPONSE:

					{

						Note("===============S2C_RESPONSE===============");

						//Query property
						S2C_FightResponse* item = new S2C_FightResponse();

						if(NULL == item){

							Error("New RegistryItem failed: len=%d",  _len);

							return -1;

						}

						if(!item->ParseFromArray(_buf, _len)){

							Error("Protocol Buffer parse failed!");

							return -1;

						}

						Print(item);	

						delete item;

					}

					break;

				case FIGHTING:

					{
						Note("===============S2C_Fight===============");

						//Query property
						S2C_Fight* item = new S2C_Fight();

						if(NULL == item){

							Error("New S2C_Fight failed: len=%d",  _len);

							return -1;

						}

						if(!item->ParseFromArray(_buf, _len)){

							Error("Protocol Buffer parse failed!");

							return -1;

						}

						WriteFight(item, _handler);

						Print(item);


					}

					break;

				case HARDBEAT:

					{
						Note("===============S2C_HardBeat===============");

						//Query property
						S2C_HardBeat* item = new S2C_HardBeat();

						if(NULL == item){

							Error("New S2C_HardBeat failed: len=%d",  _len);

							return -1;

						}

						if(!item->ParseFromArray(_buf, _len)){

							Error("Protocol Buffer parse failed!");

							return -1;

						}

						WriteHardBeat(item, _handler);

						Print(item);

					}

					break;

				case ITEM:

					{

						Note("===============S2C_Item===============");

						//Query property
						S2C_Item* item = new S2C_Item();

						if(NULL == item){

							Error("New S2C_Item failed: len=%d",  _len);

							return -1;

						}

						if(!item->ParseFromArray(_buf, _len)){

							Error("Protocol Buffer parse failed!");

							return -1;

						}

						Print(item);

						WriteItem(item, _handler);

					}

					break;

				case QTE:
					{

						Note("===============S2C_QTE===============");

						//Query property
						S2C_QTE* item = new S2C_QTE();

						if(NULL == item){

							Error("New S2C_QTE failed: len=%d",  _len);

							return -1;

						}

						if(!item->ParseFromArray(_buf, _len)){

							Error("Protocol Buffer parse failed!");

							return -1;

						}

						Print(item);

						WriteQTE(item, _handler);
					}

					break;

				case BILL:
					{

						Note("===============S2C_Bill===============");

						//Query property
						S2C_Bill* item = new S2C_Bill();

						if(NULL == item){

							Error("New S2C_QTE failed: len=%d",  _len);

							return -1;

						}

						if(!item->ParseFromArray(_buf, _len)){

							Error("Protocol Buffer parse failed!");

							return -1;

						}

						Print(item);

					}

					break;

				case GOLD:
					{

						Note("===============S2C_GOLD===============");

						//Query property
						S2C_Gold* item = new S2C_Gold();

						if(NULL == item){

							Error("New S2C_QTE failed: len=%d",  _len);

							return -1;

						}

						if(!item->ParseFromArray(_buf, _len)){

							Error("Protocol Buffer parse failed!");

							return -1;

						}

						Print(item);

					}

					break;
				case FIGHTRESULT:

					{

						Note("===============S2C_FightResult===============");

						S2C_FightResult* item = new S2C_FightResult();

						if(NULL == item){

							Error("New S2C_FightResult failed: len=%d",  _len);

							return -1;

						}

						if(!item->ParseFromArray(_buf, _len)){

							Error("Protocol Buffer parse failed!");

							return -1;

						}

						Print(item);

					}

					break;

				case VERSION:

				case TIMEDELAY:

				default:

					return -1;

			}                         

			return 0;

		}//Process          

	}//FC

}//PWRD
