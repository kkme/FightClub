#ifndef __QTESERVICE_HPP
#define __QTESERVICE_HPP

#include <Conf.hpp>

#include <Head.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

#include <Registry.hpp>

#include <Server.hpp>

#include <FightClub.pb.h>

#include <boost/shared_ptr.hpp>

using namespace PWRD;

using namespace PWRD::Event;

using namespace PWRD::Network;

namespace PWRD{

	namespace FC{

		class QTEService{

			public:

				QTEService(){ init(); }

				virtual ~QTEService(){ fini(); }

				static int Process(boost::shared_ptr<C2S_QTE> _packet UNUSED, EventHandler* _handler UNUSED);

			protected:

				int init();

				int fini();

			private:

		};//QTEService

	}//FC

}//PWRD

#endif
