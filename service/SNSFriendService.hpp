#ifndef __SNSSERVICE_HPP
#define __SNSSERVICE_HPP

#include <Service.hpp>
using namespace PWRD::FC;

namespace PWRD{

	namespace FC{

		class SNSFriendService: public Service{

			public:

				SNSFriendService(string _name):name_(_name){ init(); }

				virtual ~SNSFriendService(){ fini(); }

				virtual void Process(Packet* _packet UNUSED);

				virtual void Run();

			protected:

				int init();

				int fini();

			private:

				string name_;


		};//SNSFriendService

	}//FC

}//PWRD

#endif
