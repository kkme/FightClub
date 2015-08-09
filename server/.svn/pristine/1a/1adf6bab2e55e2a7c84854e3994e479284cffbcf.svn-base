#ifndef __DISPATCHCENTER_HPP
#define __DISPATCHCENTER_HPP

#include <Conf.hpp>

#include <Global.hpp>

#include <Daemon.hpp> 

#include <Service.hpp>

#include <BillService.hpp>

#include <RoomService.hpp>

#include <PKStatService.hpp>

#include <PKListService.hpp>

#include <VersionService.hpp>

#include <FriendListService.hpp>

#include <AddFriendService.hpp>

#include <PropertyService.hpp>

#include <FightingService.hpp>

#include <HardBeatService.hpp>

#include <LoginService.hpp>

#include <QTEService.hpp>

#include <ItemService.hpp>

#include <RoomService.hpp>

#include <RegisteService.hpp>

#include <TimeDelayService.hpp>

#include <FightRequestService.hpp>

#include <FightResultService.hpp>

#include <FightResponseService.hpp>

#include <ActiveQueueSigalton.hpp>

#include <boost/shared_ptr.hpp>

using namespace PWRD;

using namespace PWRD::FC;

using namespace PWRD::ActiveObject;

//serivces

namespace PWRD{

	namespace FC{


		class DispatchCenter{

			public:

				DispatchCenter(){}

				virtual ~DispatchCenter(){}

				int Process(EventHandler* _handler, TYPE, const char* _buf, int _len );

				void Run();


		};

		class DispatchService{
		
			public:

				static DispatchCenter* Instance(){
				
					if(NULL == instance_){

						instance_ = new DispatchCenter();

					}

					return instance_;

				}

				virtual ~DispatchService(){}	

			private:

				DispatchService(){}

				static DispatchCenter* instance_;

		};


	} //FC

}//PWRD

#endif
