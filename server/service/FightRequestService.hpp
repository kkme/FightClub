#ifndef __FIGHTREQUESTSERVICE_HPP
#define __FIGHTREQUESTSERVICE_HPP

#include <Conf.hpp>

#include <Head.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

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

		class FightRequestService{

			public:

				FightRequestService(){ init(); }

				virtual ~FightRequestService(){ fini(); }

				static int Process(boost::shared_ptr<C2S_FightRequest> _packet UNUSED, EventHandler* _handler UNUSED);

			protected:

				int init();

				int fini();

			private:

		};//FightRequestService

	}//FC

}//PWRD

#endif
