#ifndef __MAILSERVICE_HPP
#define __MAILSERVICE_HPP

#include <Service.hpp>

using namespace PWRD::FC;

namespace PWRD{

	namespace FC{

		class MailService: public Service{

			public:

				MailService(string _name):name_(_name){ init(); }

				virtual ~MailService(){ fini(); }

				virtual void Process(Packet* _packet UNUSED);

				virtual void Run();

			protected:

				int init();

				int fini();

			private:

				string name_;


		};//MailService

	}//FC

}//PWRD

#endif
