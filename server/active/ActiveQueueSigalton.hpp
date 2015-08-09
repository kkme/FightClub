#ifndef __ACTIVEQUEUESIGALTON_HPP
#define __ACTIVEQUEUESIGALTON_HPP

#include <FCDef.hpp>

#include <ActiveQueue.hpp>


using namespace PWRD;

using namespace PWRD::ActiveObject;

namespace PWRD{

	namespace ActiveObject{

		template <class T>

		class ActiveQueueSigalton{

			public:
				typedef T value_type;

				static ActiveQueueSigalton* Instance(){ 

					if(NULL == instance_){ 

						init(); 

						instance_ = new ActiveQueueSigalton(); 
					}

					return instance_;

				};

				virtual ~ActiveQueueSigalton(){ fini(); }

				static ActiveQueue<T>* Queue(){ return queue_; }

			protected:

				ActiveQueueSigalton(){ init(); }

				static int init(){ queue_ = new ActiveQueue<T>(); assert(NULL != queue_); return 1; }

				static int fini(){ delete queue_; return 1; }

			private:

				static ActiveQueue<T>* queue_;

				static ActiveQueueSigalton* instance_;

		};

		template <class T>

		ActiveQueue<T>* ActiveQueueSigalton<T>::queue_ = NULL;

		template <class T>

		ActiveQueueSigalton<T>* ActiveQueueSigalton<T>::instance_ = NULL;

	}

}

#endif
