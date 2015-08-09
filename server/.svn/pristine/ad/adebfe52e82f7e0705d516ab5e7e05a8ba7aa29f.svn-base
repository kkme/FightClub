#ifndef __FIGHTRESPONSESERVICE_HPP
#define __FIGHTRESPONSESERVICE_HPP

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

		class FightResponseService{

			public:

				FightResponseService(){ init(); }

				virtual ~FightResponseService(){ fini(); }

				static int Process(boost::shared_ptr<C2S_FightResponse> _packet UNUSED, EventHandler* _handler UNUSED);

			protected:

				int init();

				int fini();

			private:

		};//FightResponseService

	}//FC

}//PWRD

#endif
