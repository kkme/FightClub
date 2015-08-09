#ifndef __FIGHTINGSERVICE_HPP
#define __FIGHTINGSERVICE_HPP

#include <Conf.hpp>

#include <Head.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

#include <Registry.hpp>

#include <Server.hpp>

#include <Registry.hpp>

#include <FightClub.pb.h>

#include <boost/shared_ptr.hpp>

using namespace PWRD;

using namespace PWRD::Mem;

using namespace PWRD::Event;

using namespace PWRD::Network;

namespace PWRD{

	namespace FC{

		class FightingService{

			public:

				FightingService(){ init(); }

				virtual ~FightingService(){ fini(); }

				static int Process(boost::shared_ptr<C2S_Fight> _packet UNUSED, EventHandler* _handler UNUSED);

			protected:

				int init();

				int fini();

			private:

		};//FightingService

	}//FC

}//PWRD

#endif
