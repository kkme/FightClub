#ifndef __FIGHTRESULTSERVICE_HPP
#define __FIGHTRESULTSERVICE_HPP

#include <Conf.hpp>

#include <Head.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

#include <Server.hpp>

#include <Registry.hpp>

#include <FightClub.pb.h>

#include <boost/shared_ptr.hpp>

using namespace PWRD;

using namespace PWRD::Event;

using namespace PWRD::Network;

namespace PWRD{

	namespace FC{

		class FightResultService{

			public:

				FightResultService(){ init(); }

				virtual ~FightResultService(){ fini(); }

				static int Process(boost::shared_ptr<C2S_FightResult> _packet UNUSED, EventHandler* _handler UNUSED);

			protected:

				int init();

				int fini();

			private:

		};//FightResultService

	}//FC

}//PWRD

#endif
