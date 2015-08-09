#ifndef __SERVICE_HPP
#define __SERVICE_HPP

#include <Conf.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

#include <StringTool.hpp>

#include <boost/bind.hpp>

#include <boost/threadpool.hpp>

#include <boost/thread/mutex.hpp>

using namespace PWRD;

using namespace PWRD::Utils;

using namespace boost;

using namespace boost::threadpool;

#define THREADPOOLSIZE 10

#define TIME_UTC boost::TIME_UTC_

namespace PWRD{

	namespace FC{

		class Service{
		
			public:
				static Service* Instance();

				virtual ~Service(){ fini(); }

				static pool& ThreadPool();

				static void Wait(){ pool_.wait(); }

			protected:

				static int init();

				static int fini();

			private:

				Service(){ init(); }

				static int size_;

				static pool pool_;

				static Service* instance_;

		};//Service
	

	}//FC


}//PWRD


#endif
