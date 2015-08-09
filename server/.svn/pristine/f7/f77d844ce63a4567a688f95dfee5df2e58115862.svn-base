#ifndef __LOG_H
#define __LOG_H

#include <Conf.hpp>

#include <Client.hpp>

#include <Address.hpp>

#include <LogRecord.pb.h>

#include <boost/lexical_cast.hpp>

#define TCP_SERVER_PORT 11101

#define UDP_SERVER_PORT 11100

using namespace PWRD;
using namespace PWRD::Network;

namespace PWRD{

	namespace Log{

		class LOG{

			public:

				LOG* Instance();

				int Log(int _type, const string& _msg);

			protected:

				static int init();

				static int fini();

			private:

				static Client* client_;

				static LOG* instance_;


		}; //LOG

	}; //Log

} //PWRD

#endif
