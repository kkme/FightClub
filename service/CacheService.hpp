#ifndef __CACHESERVICE_HPP
#define __CACHESERVICE_HPP

#include <Service.hpp>
using namespace PWRD::FC;

namespace PWRD{

	namespace FC{

		class CacheService: public Service{

			public:

				CacheService(string _name):name_(_name){ init(); }

				virtual ~CacheService(){ fini(); }

				virtual void Process(Packet* _packet UNUSED);

				virtual void Run();

			protected:

				int init();

				int fini();

			private:

				string name_;


		};//CacheService

	}//FC

}//PWRD

#endif
