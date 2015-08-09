#ifndef __LOGINSERVICE_HPP
#define __LOGINSERVICE_HPP

#include <Conf.hpp>

#include <Head.hpp>

#include <SQLDef.hpp>

#include <SQLImpl.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

#include <Player.hpp>

#include <PlayerCache.hpp>

#include <Server.hpp>

#include <FightClub.pb.h>

#include <StringTool.hpp>

#include <boost/shared_ptr.hpp>

using namespace PWRD;

using namespace PWRD::FC;

using namespace PWRD::DB;

using namespace PWRD::Utils;

using namespace PWRD::Event;

namespace PWRD{

	namespace FC{

		class LoginService{

			public:

				LoginService(){ init(); }

				virtual ~LoginService(){ fini(); }

				static int Process(boost::shared_ptr<C2S_Login> _packet UNUSED, EventHandler* _handler UNUSED);

			protected:

				int init();

				int fini();


		};//LoginService

	}//FC

}//PWRD

#endif
