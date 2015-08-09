#ifndef __SERVERIMPL_HPP
#define __SERVERIMPL_HPP

#include <Conf.hpp>

#include <Server.hpp>
#include <Address.hpp>

#define TCP_SERVER_PORT 11101

#define UDP_SERVER_PORT 11100

using namespace PWRD;
using namespace PWRD::Network;

namespace PWRD{

	namespace Network{

		class ServerImpl{

			public:

				ServerImpl(string& _file):file_(_file){ init(); };

				virtual ~ServerImpl(){ fini(); };

				void Open();

			protected:

				int init();

				int fini();

				int Str2Int(string str);

			private:

				int Load();

				int timeout_;

				string file_;

				Address tcpaddr_;

				string tcphost_;

				Server *server_;

		};

	}

}

#endif
