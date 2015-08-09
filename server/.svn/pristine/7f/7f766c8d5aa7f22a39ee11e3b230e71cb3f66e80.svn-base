#ifndef __TIMEDELAYSERVICE_HPP
#define __TIMEDELAYSERVICE_HPP

#include <Conf.hpp>

#include <Head.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

#include <Server.hpp>

#include <FightClub.pb.h>

#include <boost/shared_ptr.hpp>

using namespace PWRD;

using namespace PWRD::DB;

using namespace PWRD::Event;

namespace PWRD{

	namespace FC{

		class TimeDelayService{

			public:

				TimeDelayService(){ init(); }

				virtual ~TimeDelayService(){ fini(); }

				static int Process(boost::shared_ptr<C2S_TimeStamp> _packet UNUSED, EventHandler* _handler UNUSED);

			protected:

				int init();

				int fini();

			private:

		};//TimeDelayService

	}//FC

}//PWRD

#endif
