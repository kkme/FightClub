#ifndef __PROPERTYSERVICE_HPP
#define __PROPERTYSERVICE_HPP

#include <Conf.hpp>

#include <Head.hpp>

#include <FightClub.pb.h>

#include <Global.hpp>

#include <Player.hpp>

#include <PlayerCache.hpp>

#include <Daemon.hpp>

#include <Server.hpp>

#include <StringTool.hpp>

#include <boost/shared_ptr.hpp>

using namespace PWRD;

using namespace PWRD::FC;

using namespace PWRD::Mem;

using namespace PWRD::Utils;

using namespace PWRD::Event;

namespace PWRD{

	namespace FC{

		class PropertyService{

			public:

				PropertyService(){ init(); }

				virtual ~PropertyService(){ fini(); }

				static int Process(boost::shared_ptr<C2S_Property> _packet UNUSED, EventHandler* _handler UNUSED);

			protected:

				static int init();

				static int fini();

			private:

		};//PropertyService

	}//FC

}//PWRD

#endif
