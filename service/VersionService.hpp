#ifndef __VERSIONSERVICE_HPP
#define __VERSIONSERVICE_HPP

#include <Service.hpp>
using namespace PWRD::FC;

namespace PWRD{

	namespace FC{

		class VersionService: public Service{

			public:

				VersionService(string _name):name_(_name){ init(); }

				virtual ~VersionService(){ fini(); }

				virtual void Process(Packet* _packet UNUSED);

				virtual void Run();

			protected:

				int init();

				int fini();

			private:

				string name_;


		};//VersionService

	}//FC

}//PWRD

#endif
