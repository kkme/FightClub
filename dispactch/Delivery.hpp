#ifndef __DELIVERY_HPP
#define __DELIVERY_HPP

#include <Session.hpp>

#include <ActiveQueuehpp>

using namespace PWRD::Network;

using namespace PWRD::ActiveObject;

namespace PWRD{

	namespace Network{

		typedef struct{

			Session* ss;

			Packet* pack;

		} Session_t;

		class Delivery{

			public:
				virtual ~Delivery(){ fini(); }

				static Delivery* Instance();

				static Session_t* Dequeue();

				static bool Enqueue(Session_t*);

				static int AsyncWait();

				static int Size();

			protected:

				static int init();

				static int fini();

			private:

				Delivery(){ init(); };
				Delivery* instance_;

				static ActiveQueue<Session_t*>* activeq_;

		};//Delivery

	}//Network

}//PWRD

#endif
