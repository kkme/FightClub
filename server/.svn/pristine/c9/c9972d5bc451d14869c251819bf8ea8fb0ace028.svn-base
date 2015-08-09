#ifndef __ACTIVEQUEUE_HPP
#define __ACTIVEQUEUE_HPP


#include <queue>
#include <iostream>
#include <semaphore.h>
#include <Daemon.hpp>

using namespace std;

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

						boost::mutex::scoped_lock lock(mutex_);

						T obj = activeq_.front();

						activeq_.pop();

						return obj;

					}

					bool Enqueue(T obj){

						Trace("TRACE ActiveQueue Enqueue");

						boost::mutex::scoped_lock lock(mutex_);

						if(NULL != obj){

							activeq_.push(obj);

							sem_post(&sem_);

							return true;

						}

						return false;

					}

					int AsyncWait(){

						return sem_wait(&sem_);

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

					boost::mutex mutex_;

					ActivationQueue activeq_;

			};

	}

}



#endif
