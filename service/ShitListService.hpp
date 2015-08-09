#ifndef __SHITSERVICE_HPP
#define __SHITSERVICE_HPP

#include <Service.hpp>
using namespace PWRD::FC;

namespace PWRD{

	namespace FC{

		class ShitListService: public Service{

			public:

				ShitListService(string _name):name_(_name){ init(); }

				virtual ~ShitListService(){ fini(); }

				virtual void Process(Packet* _packet UNUSED);

				virtual void Run();

			protected:

				int init();

				int fini();

			private:

				string name_;


		};//ShitListService

	}//FC

}//PWRD

#endif
