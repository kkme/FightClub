#ifndef __MEMORYPOOL_HPP
#define __MEMORYPOOL_HPP

#include <Daemon.hpp>
#include <Request.hpp>

using namespace PWRD;
using namespace PWRD::ActiveObject;

#include <boost/pool/object_pool.hpp>

namespace PWRD{

	namespace ActiveObject{

		typedef boost::object_pool<Request> MemPool;

		class Memorypool{

			public:
				
				static MemPool* Instance();

			private:

				static MemPool* pool_;

		};


	}


}

#endif
