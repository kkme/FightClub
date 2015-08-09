#ifndef __ADDFRIENDSERVICE_HPP
#define __ADDFRIENDSERVICE_HPP

#include <Conf.hpp>

#include <Head.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

#include <Server.hpp>

#include <Registry.hpp>

#include <StringTool.hpp>

#include <FightClub.pb.h>

#include <boost/shared_ptr.hpp>

using namespace PWRD;

using namespace PWRD::Utils;

using namespace PWRD::Event;

using namespace PWRD::Network;

//#define FriendNUM 3

namespace PWRD{

	namespace FC{

		class AddFriendService{

			public:

				AddFriendService(){ init(); }

				virtual ~AddFriendService(){ fini(); }

				static int Process(boost::shared_ptr<C2S_AddFriend> _packet UNUSED, EventHandler* _handler UNUSED);

			protected:

				int init();

				int fini();

			private:

				

		};//FriendListService

	}//FC

}//PWRD

#endif
