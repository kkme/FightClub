#ifndef __DBSERVICE_HPP
#define __DBSERVICE_HPP

#include <Service.hpp>
using namespace PWRD::FC;

namespace PWRD{

	namespace FC{

		class DBService: public Service{

			public:

				DBService(string _name):name_(_name){ init(); }

				virtual ~DBService(){ fini(); }

				virtual void Process(Packet* _packet UNUSED);

				virtual void Run();

			protected:

				int init();

				int fini();

			private:

				string name_;


		};//DBService

	}//FC

}//PWRD

#endif
