#ifndef __BILLSERVICE_HPP
#define __BILLSERVICE_HPP

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

		class BillService{

			public:

				BillService(){ init(); }

				virtual ~BillService(){ fini(); }

				static int Process(boost::shared_ptr<C2S_Bill> _packet UNUSED, EventHandler* _handler UNUSED);

			protected:

				int init();

				int fini();


		};//BillService

	}//FC

}//PWRD

#endif
