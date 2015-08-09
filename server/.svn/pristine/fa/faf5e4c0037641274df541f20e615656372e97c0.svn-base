#ifndef __ITEMSERVICE_HPP
#define __ITEMSERVICE_HPP

#include <Conf.hpp>

#include <Head.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

#include <Registry.hpp>

#include <Player.hpp>

#include <PlayerCache.hpp>

#include <Server.hpp>

#include <FightClub.pb.h>

#include <boost/shared_ptr.hpp>

using namespace PWRD;

using namespace PWRD::FC;

using namespace PWRD::Event;

using namespace PWRD::Network;

namespace PWRD{

	namespace FC{

		class ItemService{

			public:

				ItemService(){ init(); }

				virtual ~ItemService(){ fini(); }

				static int Process(boost::shared_ptr<C2S_Item> _packet UNUSED, EventHandler* _handler UNUSED);

			protected:

				int init();

				int fini();

			private:

		};//ItemService

	}//FC

}//PWRD

#endif
