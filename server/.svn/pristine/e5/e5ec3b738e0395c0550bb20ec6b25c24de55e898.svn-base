#include <DispatchCenter.hpp>

namespace PWRD{

	DispatchCenter* DispatchService::instance_ = NULL;

	void DispatchCenter::Run(){

		while(true){

			//Note("DispatchCenter Start!");

			while(ActiveQueueSigalton<Packet*>::Queue()->AsyncWait() < 0){

				Error("ActiveQueueSigalton::Queue()->AsyncWait() failed!");

				continue;

			}

			Packet* packet = ActiveQueueSigalton<Packet*>::Queue()->Dequeue();

			//Note("Get a new Packet: type=%d, len=%d", packet->type, packet->len);

			assert(NULL != packet);

			Process((EventHandler*)packet->handler, packet->type, packet->buf, packet->len);

		}

	}

	int DispatchCenter::Process(EventHandler* _handler, TYPE _type, const char* _buf, int _len){

		assert(NULL != _handler);

		assert(NULL != _buf);

		assert(_len > 0);

		switch (_type){

			case MAIL:

				break;

			case LOST:

				break;

			case TIMEDELAY:
				{

					Note("======================TIMEDELAY====================");

					boost::shared_ptr<C2S_TimeStamp> timestemp(new C2S_TimeStamp());

					if(NULL == timestemp){

						Error("New C2S_Registe failed: len=%d",  _len);

						return -1;

					}

					if(!timestemp->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed!");


						return -1;

					}

					Service::ThreadPool().schedule(boost::bind(&TimeDelayService::Process, timestemp, _handler));

				}

				break;

			case VERSION:
				{

					Note("======================VERSION=======================");

					boost::shared_ptr<C2S_Version> res(new C2S_Version());

					if(NULL == res){

						Error("New C2S_Version failed: len=%d",  _len);

						return -1;

					}

					if(!res->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed!");

						return -1;
					}

					Service::ThreadPool().schedule(boost::bind(&VersionService::Process, res, _handler));

				}

				break;

			case REGISTRY:
				{

					Note("======================REGISTRY=======================");

					boost::shared_ptr<C2S_Registe> res(new C2S_Registe());

					if(NULL == res){

						Error("New C2S_Registe failed: len=%d",  _len);

						return -1;

					}

					if(!res->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed!");

						return -1;
					}


					Service::ThreadPool().schedule(boost::bind(&RegisteService::Process, res, _handler));

				}

				break;

			case LOGIN:
				{

					Note("======================LOGIN=======================");

					boost::shared_ptr<C2S_Login> res(new C2S_Login());

					if(NULL == res){

						Error("New C2S_Login failed: len=%d",  _len);

						return -1;

					}

					if(!res->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed!");

						return -1;
					}

					//int roleid = StringTool::Str2Int(res->roleid());

					//Registry
					//Registry::RegisteCache(roleid, _handler);

					Service::ThreadPool().schedule(boost::bind(&LoginService::Process, res, _handler));

				}

				break;

			case ROOM:
				{

					Note("======================LOGIN=======================");

					boost::shared_ptr<C2S_Room> res(new C2S_Room());

					if(NULL == res){

						Error("New C2S_Login failed: len=%d",  _len);

						return -1;

					}

					if(!res->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed!");

						return -1;
					}

					Service::ThreadPool().schedule(boost::bind(&RoomService::Process, res, _handler));

				}

				break;

			case PROPERTY:
				{


					Note("======================PROPERTY=======================");

					//Query property
					boost::shared_ptr<C2S_Property> res(new C2S_Property());

					if(NULL == res){

						Error("New C2S_Registe failed: len=%d",  _len);

						return -1;

					}

					if(!res->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed!");

						return -1;
					}


					Service::ThreadPool().schedule(boost::bind(&PropertyService::Process, res, _handler));
				}

				break;

			case PKLIST:
				{


					Note("======================PKLIST====================");

					//Query PK list
					boost::shared_ptr<C2S_PKList> res(new C2S_PKList());

					res->ParseFromArray(_buf, _len);

					if(NULL == res){

						Error("New C2S_PKList failed: len=%d",  _len);

						return -1;

					}

					if(!res->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed!");

						return -1;
					}

					Service::ThreadPool().schedule(boost::bind(&PKListService::Process, res, _handler));
				}

				break;

			case PKSTAT:
				{

					Note("======================PKSTAT====================");

					//Query PK list
					boost::shared_ptr<C2S_PKStat> res(new C2S_PKStat());

					res->ParseFromArray(_buf, _len);

					if(NULL == res){

						Error("New C2S_PKStat failed: len=%d",  _len);

						return -1;

					}

					if(!res->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed!");

						return -1;
					}

					Service::ThreadPool().schedule(boost::bind(&PKStatService::Process, res, _handler));
				}

				break;

			case FRIENDLIST:
				{

					Note("======================FRIENDLIST====================");

					boost::shared_ptr<C2S_Friend> res(new C2S_Friend());

					if(NULL == res){

						Error("New C2S_Friend failed: len=%d",  _len);

						return -1;

					}

					if(!res->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed!");

						return -1;

					}

					Service::ThreadPool().schedule(boost::bind(&FriendListService::Process, res, _handler));

				}

				break;


			case FIGHTING:
				{

					Note("======================FIGHTING====================");

					//Fighting: Transport
					boost::shared_ptr<C2S_Fight> fight(new C2S_Fight());

					if(NULL == fight){

						Error("New C2S_Fight failed: len=%d",  _len);

						return -1;

					}

					if(!fight->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed: len=%d", _len);

						return -1;
					}


					Service::ThreadPool().schedule(boost::bind(&FightingService::Process, fight, _handler));

				}
				//delete fight;

				break;


			case FIGHTREQUEST:
				{


					Note("======================FIGHTREQUEST=======================");

					//Fight request
					boost::shared_ptr<C2S_FightRequest> request(new C2S_FightRequest());

					if(NULL == request){

						Error("New C2S_FightRequest failed: len=%d",  _len);

						return -1;

					}

					if(!request->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed");

						return -1;
					}

					Service::ThreadPool().schedule(boost::bind(&FightRequestService::Process, request, _handler));
				}

				//delete request;

				break;

			case FIGHTRESPONSE:
				{


					//Fight response
					boost::shared_ptr<C2S_FightResponse> response(new C2S_FightResponse());

					if(NULL == response){

						Error("New C2S_FightResponse failed: len=%d",  _len);

						return -1;

					}

					if(!response->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed");

						return -1;
					}

					Service::ThreadPool().schedule(boost::bind(&FightResponseService::Process, response, _handler));
				}

				//delete response;

				break;


			case FIGHTRESULT:
				{

					Note("======================FIGHTRESULT====================");

					//Fight result
					boost::shared_ptr<C2S_FightResult> result(new C2S_FightResult());

					if(NULL == result){

						Error("New C2S_FightResult failed: len=%d",  _len);

						return -1;

					}

					if(!result->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed!");

						return -1;
					}

					Service::ThreadPool().schedule(boost::bind(&FightResultService::Process, result, _handler));

				}
				//delete result;

				break;

			case ADDFRIENDLIST:
				{

					Note("======================ADDFRIENDLIST====================");

					boost::shared_ptr<C2S_AddFriend> res(new C2S_AddFriend());

					if(NULL == res){

						Error("New C2S_AddFriend failed: len=%d",  _len);

						return -1;

					}

					if(!res->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed!");

						return -1;

					}

					Service::ThreadPool().schedule(boost::bind(&AddFriendService::Process, res, _handler));

				}

				break;

			case QTE:
				{

					Note("======================QTE====================");

					boost::shared_ptr<C2S_QTE> res(new C2S_QTE());

					if(NULL == res){

						Error("New C2S_QTE failed: len=%d",  _len);

						return -1;

					}

					if(!res->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed!");

						return -1;

					}

					Service::ThreadPool().schedule(boost::bind(&QTEService::Process, res, _handler));
				}

				break;

			case ITEM:
				{
					Note("======================ITEM====================");

					boost::shared_ptr<C2S_Item> res(new C2S_Item());

					if(NULL == res){

						Error("New C2S_AddFriend failed: len=%d",  _len);

						return -1;

					}

					if(!res->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed!");

						return -1;

					}

					Service::ThreadPool().schedule(boost::bind(&ItemService::Process, res, _handler));
				}

				break;

			case BILL:
				{
					Note("======================BILL====================");

					boost::shared_ptr<C2S_Bill> res(new C2S_Bill());

					if(NULL == res){

						Error("New C2S_AddFriend failed: len=%d",  _len);

						return -1;

					}

					if(!res->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed!");

						return -1;

					}

					Service::ThreadPool().schedule(boost::bind(&BillService::Process, res, _handler));
				}

				break;

			case HARDBEAT:
				{
					Note("======================HARDBEAT====================");

					boost::shared_ptr<C2S_HardBeat> res(new C2S_HardBeat());

					if(NULL == res){

						Error("New C2S_AddFriend failed: len=%d",  _len);

						return -1;

					}

					if(!res->ParseFromArray(_buf, _len)){

						Error("Protocol Buffer parse failed!");

						return -1;

					}

					Service::ThreadPool().schedule(boost::bind(&HardBeatService::Process, res, _handler));
				}

			default:

				return -1;

		}                         

		return 1;

	}//Process          

}//PWRD
