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

				ServerImpl(string& _file, SyncQueue<Result*>* _syncq, ActiveQueue<FileBlock*> *_activeq):file_(_file), syncq_(_syncq), activeq_(_activeq){ init(); };

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

				Address udpaddr_;

				string tcphost_;

				string udphost_;

				Server *server_;

				SyncQueue<Result*>* syncq_;

				ActiveQueue<FileBlock*>* activeq_;
		};

	}

}

#endif
