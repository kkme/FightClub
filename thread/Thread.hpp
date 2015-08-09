#ifndef __THREAD_H
#define __THREAD_H

#include <errno.h>
#include <pthread.h>
#include <Daemon.hpp>
#include <Global.hpp>

#include <Exception.hpp>
using namespace PWRD;
using namespace PWRD::Event;

namespace PWRD{


	class ThreadException : public Exception{

		private:
			string msg_;

		public:
			ThreadException(string m):Exception(msg_), msg_(m){};

			virtual ~ThreadException() throw() {};

			virtual string getMessage() const{ return msg_; };
	};	

	class Thread{

		protected:
			string m_strName;

			pthread_t m_hThread;
			pthread_mutex_t m_hMutex;
			pthread_mutex_t m_hSuspendMutex;
			pthread_cond_t m_SuspendCondition;
			unsigned long itsWorkingThreadID;
			bool itsRunningFlag;
			bool itsSuspendedFlag;
			int pro;

			static bool itsShutdownInProgress;

		public:

			Thread();

			Thread(const char* nm);

			virtual ~Thread();

			virtual void Start();

			virtual void Run();

			void Suspend();

			void Resume();

			void Stop(bool cancel=true);

			void SetPriority(int p);

			void SetAffinity(unsigned cpu);

			bool Wait(long ms=5000);

			void Release();

			bool Is(const char* theName);

			const char* getName() const;

			void Running();

			bool IsRunning();

			bool IsSuspended();

			//static membs
			static void Sleep(long ms);
			static void ShutdownInProgress();
			static bool IsShuttingDown() { return itsShutdownInProgress; };
			static unsigned long threadID();		

			static const int P_ABOVE_NORMAL;
			static const int P_BELOW_NORMAL;
			static const int P_HIGHEST;
			static const int P_IDLE;
			static const int P_LOWEST;
			static const int P_NORMAL;
			static const int P_CRITICAL;

	};

	extern "C"{
		void* _ou_thread_proc(void* param);
	};

}

#endif

