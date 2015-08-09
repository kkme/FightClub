#ifndef __SERVICE_H
#define __SERVICE_H

#include <Head.hpp>
#include <Packet.hpp>
#include <Global.hpp>

using namespace PWRD;


namespace PWRD{

	namespace FC{

		class Service{

			public:
				Service(string _name):name_(_name){ init(); }

				virtual ~Service(){ fini(); };

				virtual void Process(Packet* _packet UNUSED){};

				virtual void Run(){};

			protected:

				virtual int init(){ return 1; }

				virtual int fini(){ return 1; }

				string name_;

			private:



		};

	}//FC
}

#endif
