#ifndef __SYNCQUEUE_HPP
#define __SYNCQUEUE_HPP


#include <queue>
#include <iostream>
#include <semaphore.h>
#include <Daemon.hpp>

#include <Mutex.hpp>

using namespace std;

using namespace PWRD::IPC;

namespace PWRD{

	namespace ActiveObject{

		template <class T>

			class SyncQueue{

				public:

					typedef T value_type;

					typedef queue<value_type> ActivationQueue;

					SyncQueue(){ init(); };

					virtual ~SyncQueue(){ fini(); };

					T Dequeue(){

						Trace("TRACE SyncQueue Dequeue");

						mutex_.Lock();

						T obj;

						if(activeq_.size() > 0){

							obj = activeq_.front();

							activeq_.pop();


						}

						mutex_.UnLock();

						return obj;

					}

					bool Enqueue(T obj){

						Trace("TRACE SyncQueue Enqueue");

						if(NULL == obj){

							return false;

						}

						mutex_.Lock();

						activeq_.push(obj);

						mutex_.UnLock();

						return true;

					}

					size_t Size(){
						
						mutex_.Lock();

						int size = activeq_.size();

						mutex_.UnLock();

						return size;

					}


				protected:

					int init(){

						//activeq_.clear();

						return 1;

					}

					int fini(){

						return 1;

					}



				private:

					Mutex mutex_;

					ActivationQueue activeq_;

			};

	}

}



#endif
