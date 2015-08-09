#ifndef __MUTEX_HPP 
#define __MUTEX_HPP

#include <pthread.h>  

#include <Global.hpp>

#include <Daemon.hpp>

using namespace PWRD;

namespace PWRD{

	namespace IPC{  

                class ScopedLock{   

                        public:  

                                ScopedLock(){ 

                                        pthread_mutex_init(&mutex_, NULL); 

                                        pthread_mutex_lock(&mutex_);

                                };

                                virtual ~ScopedLock(){

                                        pthread_mutex_unlock(&mutex_);

					pthread_mutex_destroy(&mutex_);

                                };

                        private:

                                pthread_mutex_t mutex_;
                };

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
        }
}
#endif
