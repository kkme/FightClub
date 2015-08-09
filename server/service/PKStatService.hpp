#ifndef __PKSTATSERVICE_HPP
#define __PKSTATSERVICE_HPP

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

		class PKStatService{

			public:

				PKStatService(){ init(); }

				virtual ~PKStatService(){ fini(); }

				static int Process(boost::shared_ptr<C2S_PKStat> _packet UNUSED, EventHandler* _handler UNUSED);

			protected:

				int init();

				int fini();


		};//PKStatService

	}//FC

}//PWRD

#endif
