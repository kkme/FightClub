#ifndef __MUTEX_HPP 
#define __MUTEX_HPP

#include <pthread.h>  

#include <Global.hpp>

#include <Daemon.hpp>

using namespace PWRD;

namespace PWRD{

	namespace IPC{  

		class Mutex{

			public:

				Mutex(){

					pthread_mutex_init(&mutex_, NULL);

				}

				virtual ~Mutex(){

					pthread_mutex_destroy(&mutex_);

				}

				void Lock(){

					pthread_mutex_lock(&mutex_);

				}

				void UnLock(){

					pthread_mutex_unlock(&mutex_);

				}

			private:
				pthread_mutex_t mutex_;
		};

		class ScopedLock{   

			public:  

				ScopedLock(Mutex _mutex):mutex_(_mutex){ 

					mutex_.Lock();

				};

				virtual ~ScopedLock(){

					mutex_.UnLock();

				};

			private:

				Mutex mutex_;
		};

	}//IPC

}//PWRD

#endif
