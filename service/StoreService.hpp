#ifndef __STORESERVICE_HPP
#define __STORESERVICE_HPP

#include <Service.hpp>
using namespace PWRD::FC;

namespace PWRD{

	namespace FC{

		class StoreService: public Service{

			public:

				StoreService(string _name):name_(_name){ init(); }

				virtual ~StoreService(){ fini(); }

				virtual void Process(Packet* _packet UNUSED);

				virtual void Run();

			protected:

				int init();

				int fini();

			private:

				string name_;


		};//StoreService

	}//FC

}//PWRD

#endif
