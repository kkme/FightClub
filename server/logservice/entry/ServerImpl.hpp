#ifndef __SERVERIMPL_HPP
#define __SERVERIMPL_HPP

#include <Conf.hpp>

#include <Server.hpp>
#include <Address.hpp>

#include <boost/lexical_cast.hpp>

#define TCP_SERVER_PORT 11101

#define UDP_SERVER_PORT 11100

using namespace PWRD;
using namespace PWRD::Network;

namespace PWRD{

	namespace Network{

		class ServerImpl{

			public:

				ServerImpl(string& _file, ActiveQueue<Request*> *_activeq):file_(_file), activeq_(_activeq){ init(); };


				virtual ~ServerImpl(){ fini(); };

				void Open();

			protected:

				int init();

				int fini();

			private:

				int Load();

				int timeout_;

				string file_;

				Address tcpaddr_;

				Address udpaddr_;

				string tcphost_;

				string udphost_;

				Server *server_;

				DatagramService * udpsvc_;

				ActiveQueue<Request*> *activeq_;
		};

	}

}

#endif
