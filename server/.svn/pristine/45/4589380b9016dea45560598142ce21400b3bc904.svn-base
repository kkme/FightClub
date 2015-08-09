#ifndef __STRINGPOOL_HPP
#define __STRINGPOOL_HPP

#include <Daemon.hpp>

using namespace PWRD;

#include <boost/pool/object_pool.hpp>

namespace PWRD{

	namespace ActiveObject{

		typedef boost::object_pool<string> StrPool;

		class Stringpool{

			public:
				virtual ~Stringpool(){};

				static StrPool* Instance();

			private:

				Stringpool(){ };

				static StrPool *strpool_;

		};

	}


}

#endif
