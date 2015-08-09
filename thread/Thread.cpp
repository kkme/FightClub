#define SILENT

#include <sys/time.h>
#include <Thread.hpp>

#define THREAD_NULL 0
#define SUSPENDWAITMS 10
#define ASSIGN_LONG(dest,val) dest=val
#define ASSIGN_BOOL(dest,val) dest=val
#define ASSIGN_PTR(dest,val)  dest=val

namespace PWRD{


	const int Thread::P_ABOVE_NORMAL = 0;
	const int Thread::P_BELOW_NORMAL = 1;
	const int Thread::P_HIGHEST = 2;
	const int Thread::P_IDLE = 3;
	const int Thread::P_LOWEST = 4;
	const int Thread::P_NORMAL = 5;
	const int Thread::P_CRITICAL = 6;

	bool Thread::itsShutdownInProgress=false;

	void Thread::Running(){

		ASSIGN_BOOL(itsRunningFlag,true); 
	};

	bool Thread::IsRunning(){

		return (itsRunningFlag!=0) ? true : false; 
	};

	bool Thread::IsSuspended(){

		return (itsSuspendedFlag!=0) ? true : false; 
	};

	void Thread::ShutdownInProgress(){

		Trace("TRACE -----------------------SHUTDOWN-----------------------");
		itsShutdownInProgress=true; 

	}

	unsigned long Thread::threadID(){

		return pthread_self();

	}


	Thread::Thread(){

		Trace("TRACE Thread constructor - start");

		m_hThread = THREAD_NULL;
		m_strName = "Thread";

		ASSIGN_BOOL(itsRunningFlag,false);
		ASSIGN_BOOL(itsSuspendedFlag,false);
		ASSIGN_LONG(itsWorkingThreadID,0);	

		pthread_mutex_init(&m_hMutex,NULL);


	}

	Thread::Thread(const char* nm){

		Trace("TRACE Thread constructor - start");
		Trace("TRACE Name=%s", nm);

		m_hThread = THREAD_NULL;
		m_strName = nm;

		ASSIGN_BOOL(itsRunningFlag,false);
		ASSIGN_BOOL(itsSuspendedFlag,false);
		ASSIGN_LONG(itsWorkingThreadID,0);	

		pthread_mutex_init(&m_hMutex,NULL);

		Trace("TRACE Thread constructor - end");
	}

	Thread::~Thread(){

		Trace("TRACE Thread destructor - start");
		Trace("TRACE Name=%s", getName());

		if(m_hThread != THREAD_NULL){

			Stop(true);

		}

		pthread_mutex_destroy(&m_hMutex);

		Trace("TRACE Thread destructor - end");
	}


	const char* Thread::getName() const{	

		return m_strName.c_str();
	}

	bool Thread::Is(const char* theName){

		return (m_strName==theName);

	}

	void Thread::Run(){
		// Base run
	}

	void Thread::Sleep(long ms){

		Trace("TRACE Thread::sleep(static) - start");

		struct timespec abs_ts;
		struct timespec rm_ts;
		rm_ts.tv_sec = ms/1000; 
		rm_ts.tv_nsec = ms%1000 *1000000;

		do{
			abs_ts.tv_sec = rm_ts.tv_sec; 
			abs_ts.tv_nsec = rm_ts.tv_nsec;

		} while(nanosleep(&abs_ts,&rm_ts) < 0);

		Trace("TRACE Thread::sleep(static) - stop");
	}


	void Thread::Start(){

		Trace("TRACE Thread::start - start");
		Trace("TRACE Name=%s", getName());

		pthread_mutex_init(&m_hSuspendMutex,NULL);

		pthread_cond_init(&m_SuspendCondition,NULL);

		int iret = pthread_create( &m_hThread, NULL, _ou_thread_proc,this);

		if(iret!=0){

			Trace("TRACE Fail to create thread");
			throw ThreadException(string("Failed to create thread ->")+m_strName);

		}

		Trace("TRACE Thread::start - end");
	}

	void Thread::Stop(bool cancel){

		Trace("TRACE Thread::stop - start");
		Trace("TRACE Name=%s", getName());

		if(itsRunningFlag){

			ASSIGN_BOOL(itsRunningFlag,false);

			Trace("TRACE Joining thread");

			if(cancel==true)
				pthread_cancel(m_hThread);
			else
				pthread_join(m_hThread,NULL);

			Trace("TRACE Thread cleanup")			;

			pthread_mutex_destroy(&m_hSuspendMutex);
			pthread_cond_destroy(&m_SuspendCondition);

			m_hThread = THREAD_NULL;
		}

		Trace("TRACE Thread::stop - end");
	}

	void Thread::SetPriority(int tp){

		if(m_hThread == THREAD_NULL){

			throw ThreadException("Thread object is null");
		}

		pro = tp;

	}

	void Thread::SetAffinity(unsigned cpu){

		cpu_set_t cpuset;

		CPU_ZERO(&cpuset);
		CPU_SET(cpu, &cpuset);

#ifdef HAVE_PTHREAD_SETAFFINITY_NP 
#ifndef P2_PTHREAD_SETAFFINITY
		if(pthread_setaffinity_np(m_hThread, sizeof(cpuset), &cpuset)!=0)
			throw ThreadException("Failed to set affinity");
#else
		if(pthread_setaffinity_np(m_hThread, &cpuset)!=0)
			throw ThreadException("Failed to set affinity");
#endif
#else
		Trace("Thread affinity not supported on this system");
#endif
	}


	void Thread::Suspend(){

		Trace("Thread::suspend - start");
		Trace("Name=%s", getName());

		if(m_hThread == THREAD_NULL){

			throw ThreadException(string("Thread object is null ->")+m_strName);
		}
		else{
			Trace("TRACE Tread suspended");

			pthread_mutex_lock(&m_hSuspendMutex);
			//Trace("TRACE Cond mutex count=%lu", m_hSuspendMutex.__m_count);
			//Trace("TRACE Cond lock status=%lu", m_hSuspendMutex.__m_lock.__status);
			itsSuspendedFlag=true;

			while(itsSuspendedFlag==true){

				int ms=SUSPENDWAITMS;
				struct timespec abs_ts;
				struct timeval cur_tv;
				gettimeofday(&cur_tv, NULL);
				abs_ts.tv_sec = cur_tv.tv_sec + ms/1000; 
				abs_ts.tv_nsec = (cur_tv.tv_usec + ms%1000*1000)*1000;

				// FIX by Steve Rodgers
				if(abs_ts.tv_nsec > 999999999){

					abs_ts.tv_sec++;
					abs_ts.tv_nsec -= 1000000000;

				}
				// End fix

				pthread_cond_timedwait(&m_SuspendCondition,&m_hSuspendMutex,&abs_ts);

				//Trace("Cond condition lock status=%lu", m_SuspendCondition.__c_lock.__status);

				if(itsRunningFlag==false){

					Trace("Resume thread for shutdown cleanup");
					break;
				}
			}

			pthread_mutex_unlock(&m_hSuspendMutex);

			//Trace("TRACE Cond mutex count=%lu", m_hSuspendMutex.__m_count);
			//Trace("TRACE Cond lock status=%lu", m_hSuspendMutex.__m_lock.__status);

			Trace("TRACE Thread resumed");
		}

		Trace("TRACE Thread::suspend - end")	;
	}

	void Thread::Resume(){

		Trace("TRACE Thread::resume - start");
		Trace("TRACE Name=%s", getName());

		if(m_hThread == THREAD_NULL){

			throw ThreadException(string("Thread object is null ->")+m_strName);
		}
		else{
			pthread_mutex_lock(&m_hSuspendMutex);

			//Trace("TRACE Cond mutex count=%lu", m_hSuspendMutex.__m_count);
			//Trace("TRACE Cond lock status=%lu", m_hSuspendMutex.__m_lock.__status);

			itsSuspendedFlag=false;
			pthread_cond_signal(&m_SuspendCondition);

			//Trace("TRACE Cond condition lock status=%lu", m_SuspendCondition.__c_lock.__status);

			pthread_mutex_unlock(&m_hSuspendMutex);

			//Trace("TRACE Cond mutex count=%lu", m_hSuspendMutex.__m_count);
			//Trace("TRACE Cond lock status=%lu", m_hSuspendMutex.__m_lock.__status);
		}

		Trace("TRACE Thread::resume - end");
	}

	bool Thread::Wait(long ms){

		Trace("TRACE Thread::wait - start");
		Trace("TRACE Name=%s", getName());

		if(itsWorkingThreadID!=0){

			Trace("TRACE Thread:%s id:%lu is waiting for thread:%lu", getName(), threadID(), itsWorkingThreadID);
		}

		struct timespec abs_ts;
		struct timeval cur_tv;

		gettimeofday(&cur_tv, NULL);

		abs_ts.tv_sec = cur_tv.tv_sec + ms/1000; 
		abs_ts.tv_nsec = (cur_tv.tv_usec + ms%1000*1000)*1000;

		int res=pthread_mutex_timedlock(&m_hMutex,&abs_ts);	

		//Trace("TRACE Mutex count=%lu",  m_hMutex.__m_count);
		//Trace("TRACE Lock status=%lu", m_hMutex.__m_lock.__status);

		switch(res){

			case 0:
				itsWorkingThreadID=threadID(); //++ v1.5

				Trace("TRACE Thread::wait - end")	;

				return true;

			case EINVAL:

				throw ThreadException(string("pthread_mutex_timedlock: Invalid value ->")+m_strName);

				break;

			case ETIMEDOUT:

				throw ThreadException(string("pthread_mutex_timedlock: Wait timed out ->")+m_strName);

				break;

			default:

				throw ThreadException(string("pthread_mutex_timedlock: Unexpected value ->")+m_strName);		
		}

		return false;
	}

	void Thread::Release(){

		Trace("TRACE Thread::release - start");

		Trace("TRACE Name=%s", getName());

		pthread_mutex_unlock(&m_hMutex);	

		//Trace("TRACE Mutex count=%lu", m_hMutex.__m_count);

		//Trace("TRACE Lock status=%lu", m_hMutex.__m_lock.__status);

		Trace("TRACE Thread::release - end")	;
	}


	void* _ou_thread_proc(void* param){

		Trace("TRACE Start _ou_thread_proc");

		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);

		pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);

		try{

			Thread* tp = (Thread*)param;

			tp->Running();

			Trace("TRACE Thread %s  started", tp->getName());

			tp->Run();

		}
		catch(...){

			Trace("Unhandled exception in thread callback");
		}

		Trace("End _ou_thread_proc");

		pthread_exit(NULL);

		return NULL;
	}

}
