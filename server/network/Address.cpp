#include <Address.hpp>
#include <SocketType.hpp>

namespace PWRD{

	namespace Network{

		Address::Address(){ 

			memset(&addr_, '\0', sizeof(sockaddr_in));
		}

		Address::Address(const std::string& ip, u_short port){

			Set(ip, port);

		}

		Address::Address(u_long ip, u_short port){

			Set(ip, port);

		}

		Address::Address(u_short port){

			Set(port);

		}

		void Address::Set(const std::string& ip, u_short port){

			memset(&addr_, '\0', sizeof(sockaddr_in));

			// TCP sin_family is same than UDP's.
			addr_.sin_family = StreamType::Family();

			addr_.sin_port = htons(port);

			addr_.sin_addr.s_addr = inet_addr(ip.c_str());

		}

		void Address::Set(u_long ip, u_short port) {

			memset(&addr_, '\0', sizeof(sockaddr_in));

			// TCP sin_family is same than UDP's.
			addr_.sin_family = StreamType::Family();

			addr_.sin_port = port;

			addr_.sin_addr.s_addr = ip;

		}

		void Address::Set(u_short port){

			memset(&addr_, '\0', sizeof(sockaddr_in));

			// TCP sin_family is same than UDP's.
			addr_.sin_family = StreamType::Family();

			addr_.sin_port = htons(port);

			addr_.sin_addr.s_addr = INADDR_ANY;

		}

		Address::~Address(void) { }

		std::string Address::IP() const{

			return inet_ntoa(addr_.sin_addr);

		}

		u_long Address::NetIP() const{

			return addr_.sin_addr.s_addr;

		}

		u_short Address::Port() const{

			return ntohs(addr_.sin_port);

		}

		u_short Address::NetPort() const{

			return addr_.sin_port;

		}

		const sockaddr_in& Address::Sockaddr() const{

			return addr_;

		}

		void Address::Sockaddr(const sockaddr_in& sin){

			addr_ = sin;
		}
	}
}
