#ifndef __REGISTRESERVICE_HPP
#define __REGISTRESERVICE_HPP

#include <Conf.hpp>

#include <Time.hpp>

#include <Head.hpp>

#include <SQLDef.hpp>

#include <SQLImpl.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

#include <Server.hpp>

#include <FightClub.pb.h>

#include <StringTool.hpp>

#include <Player.hpp>

#include <PlayerCache.hpp>

#include <boost/shared_ptr.hpp>


using namespace PWRD;

using namespace PWRD::FC;

using namespace PWRD::DB;

using namespace PWRD::Mem;

using namespace PWRD::Utils;

using namespace PWRD::Event;

namespace PWRD{

	namespace FC{

		class RegisteService{

			public:

				RegisteService(){ init(); }

				virtual ~RegisteService(){ fini(); }

				static int Process(boost::shared_ptr<C2S_Registe> _packet UNUSED, EventHandler* _handler UNUSED);

			protected:

				int init();

				int fini();


		};//RegisteService

	}//FC

}//PWRD

#endif
