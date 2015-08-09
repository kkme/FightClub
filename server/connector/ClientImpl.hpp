#ifndef __CLIENTIMPL_HPP
#define __CLIENTIMPL_HPP

#include <Conf.hpp>

#include <Client.hpp>
#include <Address.hpp>

#include <boost/lexical_cast.hpp>

#define TCP_SERVER_PORT 11101

#define UDP_SERVER_PORT 11100

using namespace PWRD;
using namespace PWRD::Network;

namespace PWRD{

	namespace Network{

		class ClientImpl{

			public:

				ClientImpl(string& _file):file_(_file){ init(); };

				virtual ~ClientImpl(){ fini(); };

				void Open();

				Client* client(){ return server_; }

			protected:

				int init();

				int fini();

			private:

				int Load();

				int timeout_;

				string file_;

				Address tcpaddr_;

				string tcphost_;

				Client *server_;

		};

	}

}

#endif
