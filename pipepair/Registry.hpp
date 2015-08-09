#ifndef __REGISTRY_H
#define __REGISTRY_H

#include <Global.hpp>

#include <Daemon.hpp>

#include <Mutex.hpp>

#include <Monitor.pb.h>

#include <SyncQueue.hpp>

#include <EventHandler.hpp>

using namespace PWRD;

using namespace PWRD::IPC;

using namespace PWRD::Event;

using namespace PWRD::ActiveObject;

namespace PWRD{

	namespace Event{

		typedef int FD;

		typedef int STATUS;

		typedef pid_t PID;

		typedef string SHELL;

		typedef map<SHELL, EventHandler*> RuntimeMap;

		typedef map<EventHandler*, SHELL> HandlerMap;

		class Registry{

			public:

				static Registry* Instance();

				static void RegisteHandler(EventHandler*, SHELL& _shell);

				static void RemoveHandler(EventHandler*);

				static void RegisteRuntime(SHELL& _shell, EventHandler*);

				static void RemoveRuntime(SHELL& _shell);

				static bool Erase(SHELL _shell);

				static HandlerMap* hmap(){ return hmap_; }

				static RuntimeMap* rmap(){ return rmap_; }

				static SyncQueue<Result*>* syncq(){ return syncq_; }

			protected:

				Registry(){ init(); }

				virtual ~Registry(){ fini(); }

				int init();

				int fini();

			private:

				static HandlerMap* hmap_;

				static RuntimeMap* rmap_;
				
				static Registry* instance_;

				static Mutex mutex_;

				static SyncQueue<Result*>* syncq_;

		};

	}//Event

}//PWRD

#endif
