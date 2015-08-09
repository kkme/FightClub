#ifndef __PKLISTSERVICE_HPP
#define __PKLISTSERVICE_HPP

#include <Service.hpp>
using namespace PWRD::FC;

namespace PWRD{

	namespace FC{

		class PKListService: public Service{

			public:

				PKListService(string _name):name_(_name){ init(); }

				virtual ~PKListService(){ fini(); }

				virtual void Process(Packet* _packet UNUSED);

				virtual void Run();

			protected:

				int init();

				int fini();

			private:

				string name_;


		};//PKListService

	}//FC

}//PWRD

#endif
