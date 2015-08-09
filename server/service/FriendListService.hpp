#ifndef __FRIENDLISTSERVICE_HPP
#define __FRIENDLISTSERVICE_HPP

#include <Conf.hpp>

#include <Head.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

#include <Server.hpp>

#include <Registry.hpp>

#include <StringTool.hpp>

#include <FightClub.pb.h>

#include <Player.hpp>

#include <PlayerCache.hpp>

#include <boost/shared_ptr.hpp>

using namespace PWRD;

using namespace PWRD::FC;

using namespace PWRD::Utils;

using namespace PWRD::Event;

using namespace PWRD::Network;

namespace PWRD{

	namespace FC{

		class FriendListService{

			public:

				FriendListService(){ init(); }

				virtual ~FriendListService(){ fini(); }

				static int Process(boost::shared_ptr<C2S_Friend> _packet UNUSED, EventHandler* _handler UNUSED);

			protected:

				int init();

				int fini();

			private:

				

		};//FriendListService

	}//FC

}//PWRD

#endif
