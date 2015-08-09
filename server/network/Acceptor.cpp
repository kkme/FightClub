#include <Stream.hpp>
#include <Address.hpp>
#include <Acceptor.hpp>
#include <Exception.hpp>
#include <SocketDef.hpp>

using namespace PWRD::Network;
using namespace PWRD::Event;

#define BACKLOG 10

namespace PWRD{

	namespace Network{

		Acceptor::Acceptor(const Address& addr) {

			Open(addr);

			if (listen(GetHandle(), BACKLOG) == FAILED)

				throw Exception("Listen failed!");
		}

		Acceptor::~Acceptor(void) { }

		void Acceptor::Accept(Stream& s){

			Handle sock = ::accept(GetHandle(), NULL, NULL);

			if (sock == INVALID_HANDLE)

				throw Exception("Accept socket error!");

			s.Attach(sock);

		}

		void Acceptor::Accept(Stream& s, Address& addr){

			sockaddr_in sin;

			memset(&sin, '\0', sizeof(sockaddr_in));

			SockLen len = sizeof(sockaddr_in);

			Handle sock = ::accept(GetHandle(), (sockaddr*)&sin, &len);

			if (sock == INVALID_HANDLE)

				throw Exception("Accept socket error!");

			s.Attach(sock);

			addr.Sockaddr(sin);

		}
	}
}

