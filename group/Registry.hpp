#ifndef __REGISTRY_H
#define __REGISTRY_H

#include <Global.hpp>

#include <Daemon.hpp>

#include <Mutex.hpp>

#include <Session.hpp>

#include <Monitor.pb.h>

#include <SyncQueue.hpp>

#include <EventHandler.hpp>

#include <PropertyImpl.hpp>

using namespace PWRD;

using namespace PWRD::DB;

using namespace PWRD::IPC;

using namespace PWRD::Event;

using namespace PWRD::ActiveObject;

namespace PWRD{

	namespace Event{

		typedef EventHandler* HANLDER;

		typedef struct{

			STAT stat;	

			string uid;

			HANDLER buddy;
			
			Property* property;

		}SessionGroup;

		typedef SessionGroup* SG;

		typedef map<HANDLER, SG> SessionMap;

		typedef map<string, HANDLER> CacheMap;

		class Registry{

			public:

				static Registry* Instance();

				static void Initialize(HANDLER _handler, string _uid);

				static void RegisteHandler(HANDLER, HANDLER);

				static void RemoveHandler(HANDLER);

				static void RegistrCache(string, HANDLER);

				static void RemoveCache(string);

				static CacheMap* chmap(){ return chmap_; }

				static SessionMap* sgmap(){ return sgmap_; }

				static SyncQueue<Result*>* syncq(){ return syncq_; }

			protected:

				Registry(){ init(); }

				virtual ~Registry(){ fini(); }

				int init();

				int fini();

			private:

				static Mutex mutex_;

				static CacheMap* chmap_; 

				static SessionMap* sgmap_;

				static SyncQueue<Result*>* syncq_;

		};

	}//Event

}//PWRD

#endif
