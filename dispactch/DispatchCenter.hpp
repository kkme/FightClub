#ifndef __DISPATCHCENTER_H
#define __DISPATCHCENTER_H

#include <Conf.hpp>
#include <Mutex.hpp>
#include <Service.hpp>
#include <Delivery.hpp>

using namespace PWRD;
using namespace PWRD::Service;


namespace PWRD{

	typedef map<string, Service*> ServiceMap;

	typedef map<string, ActiveQueue<Session_t*>*> ActiveQueueMap;

	typedef vector<string> Keys;

	class DispatchCenter: public Thread{

		public:
			DispatchCenter(){ init(); }

			virtual void Run();

			void Register(string, Service*);

			void Remove(string);

			virtual ~DispatchCenter(){ fini(); }

		protected: 

			void Load();

			Service* Switch(const string& _name);

			int init();

			int fini();


		private:

			Keys serkeys_;

			ServiceMap* smap_;

			DispatchCenter* dc_;

			ActiveQueueMap aqmap_;



	};

	typedef DispatchCenter DC;

}//PWRD

#endif
