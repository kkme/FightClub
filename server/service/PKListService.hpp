#ifndef __PKLISTLISTSERVICE_HPP
#define __PKLISTLISTSERVICE_HPP

#include <Conf.hpp>

#include <Head.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

#include <String.hpp>

#include <Server.hpp>

#include <Player.hpp>

#include <PlayerCache.hpp>

#include <Registry.hpp>

#include <StringTool.hpp>

#include <FightClub.pb.h>

#include <boost/shared_ptr.hpp>

using namespace PWRD;

using namespace PWRD::FC;

using namespace PWRD::Mem;

using namespace PWRD::Utils;

using namespace PWRD::Event;

using namespace PWRD::Network;

//#define PKNUM 3

namespace PWRD{

	namespace FC{

		class PKListService{

			public:

				PKListService(){ init(); }

				virtual ~PKListService(){ fini(); }

				static int Process(boost::shared_ptr<C2S_PKList> _packet UNUSED, EventHandler* _handler UNUSED);

			protected:

				static int init();

				static int fini();

			private:

		};//PKListService

	}//FC

}//PWRD

#endif
