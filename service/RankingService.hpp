#ifndef __FIGHTSERVICE_HPP
#define __FIGHTSERVICE_HPP

#include <Service.hpp>
using namespace PWRD::FC;

namespace PWRD{

	namespace FC{

		class RankingService: public Service{

			public:

				RankingService(string _name):name_(_name){ init(); }

				virtual ~RankingService(){ fini(); }

				virtual void Process(Packet* _packet UNUSED);

				virtual void Run();

			protected:

				int init();

				int fini();

			private:

				string name_;


		};//RankingService

	}//FC

}//PWRD

#endif
