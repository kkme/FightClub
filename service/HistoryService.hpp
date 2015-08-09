#ifndef __HISTORYSERVICE_HPP
#define __HISTORYSERVICE_HPP

#include <Service.hpp>
using namespace PWRD::FC;

namespace PWRD{

	namespace FC{

		class HistoryService: public Service{

			public:

				HistoryService(string _name):name_(_name){ init(); }

				virtual ~HistoryService(){ fini(); }

				virtual void Process(Packet* _packet UNUSED);

				virtual void Run();

			protected:

				int init();

				int fini();

			private:

				string name_;


		};//HistoryService

	}//FC

}//PWRD

#endif
