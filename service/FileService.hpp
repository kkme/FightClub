#ifndef __FILESERVICE_HPP
#define __FILESERVICE_HPP

#include <Service.hpp>
using namespace PWRD::FC;

namespace PWRD{

	namespace FC{

		class FileService: public Service{

			public:

				FileService(string _name):name_(_name){ init(); }

				virtual ~FileService(){ fini(); }

				virtual void Process(Packet* _packet UNUSED);

				virtual void Run();

			protected:

				int init();

				int fini();

			private:

				string name_;


		};//FileService

	}//FC

}//PWRD

#endif
