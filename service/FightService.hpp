#ifndef __FIGHTSERVICE_HPP
#define __FIGHTSERVICE_HPP

#include <Service.hpp>
using namespace PWRD::FC;

namespace PWRD{

	namespace FC{

		class FightService: public Service{

			public:

				FightService(string _name):name_(_name){ init(); }

				virtual ~FightService(){ fini(); }

				virtual void Process(Packet* _packet UNUSED);

				virtual void Run();

			protected:

				int init();

				int fini();

			private:

				string name_;


		};//FightService

	}//FC

}//PWRD

#endif
