#ifndef __ACTIVEQUEUE_HPP
#define __ACTIVEQUEUE_HPP

#include <Daemon.hpp>

#include <Global.hpp>

#include <Mutex.hpp>

using namespace std;

using namespace PWRD;

using namespace PWRD::IPC;

namespace PWRD{

	namespace ActiveObject{

		template <class T>

			class ActiveQueue{

				public:

					typedef T value_type;

					typedef queue<value_type> ActivationQueue;

					ActiveQueue(){ init(); };

					~ActiveQueue(){ fini(); };

					T Dequeue(){

						Trace("TRACE ActiveQueue Dequeue");

						mutex_.Lock();

						T obj = activeq_.front();

						activeq_.pop();

						mutex_.UnLock();

						return obj;

					}

					bool Enqueue(T obj){

						Trace("TRACE ActiveQueue Enqueue");


						if(NULL == obj){

							return false;

						}

						mutex_.Lock();

						activeq_.push(obj);

						mutex_.UnLock();

						sem_post(&sem_);


						return true;

					}

					int AsyncWait(){

						return sem_wait(&sem_);

					}

					int Size(){

						int size = 0;

						mutex_.Lock();

						size = activeq_.size();

						mutex_.UnLock();

						return size;
					}

				protected:

					int init(){


						if(sem_init(&sem_, 0, 0) < 0){

							Error("Sem init failed: errno=%d, errmsg=%s", errno, strerror(errno));

							return -1;

						}

						//activeq_.clear();

						return 1;

					}

					int fini(){

						if(sem_destroy(&sem_) < 0){

							Error("Sem destroy failed: errno=%d, errmsg=%s", errno, strerror(errno));

							return -1;
						}

						return 1;

					}



				private:

					sem_t sem_;

					Mutex mutex_;

					ActivationQueue activeq_;

			};

	}

}



#endif
