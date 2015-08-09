#ifndef __ERROR_HPP
#define __ERROR_HPP

#include <Global.hpp>
#include <Daemon.hpp>
#include <Server.hpp>
#include <FightClub.pb.h>

using namespace std;
using namespace PWRD;
using namespace PWRD::Network;

namespace PWRD{

	namespace Error{

		class Error{

			public:
				static Error* Instance();

				static int Send(ERRORTYPE _type, EventHandler* _handler);

			protected:

				static int init();
				static int fini();

				Error(){ init(); }
				virtual ~Error(){ fini(); }

			private:

				static Error* instance_;


		}; //Error


	} //Error

} //Error



#endif

