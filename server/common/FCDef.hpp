#ifndef __FCDEF_HPP
#define __FCDEF_HPP

#include <Head.hpp>

namespace PWRD{

	class Packet{

		public:

			int len;

			TYPE type;

			char buf[BUFSIZ];

			void* handler;

			Packet(int _len, TYPE _type, const char* _buf, void* _handler):len(_len), type(_type), handler(_handler){

				strncpy(buf, _buf, _len);
			
			}

			virtual ~Packet(){}


	};


}

#endif
