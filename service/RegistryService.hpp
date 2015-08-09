#ifndef __REGISTRYSERVICE_HPP
#define __REGISTRYSERVICE_HPP

#include <Service.hpp>
using namespace PWRD::FC;

namespace PWRD{

	namespace FC{

		typedef map<string, Session*> CacheMap;

		class RegistryService: public Service{

			public:

				RegistryService(string _name = ""):name_(_name){ init(); }

				virtual ~RegistryService(){ fini(); }

				virtual void Process(RegistryItem* _registry UNUSED, HANDLER _handler);

				virtual void Run();

			protected:

				int init();

				int fini();

			private:

				string name_;


		};//RegistryService

	}//FC

}//PWRD

#endif
