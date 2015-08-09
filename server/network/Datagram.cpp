#include <Address.hpp>
#include <Datagram.hpp>
#include <Exception.hpp>

using namespace PWRD::Event;

namespace PWRD{

	namespace Network{

		Datagram::Datagram() {

			Open();
		}

		Datagram::Datagram(const Address& addr) {

			Open(addr);
		}

		Datagram::~Datagram(void) { }

		int Datagram::ReceiveN(char* buffer, int length) {	
			
			int ret = recvfrom(GetHandle(), buffer, length, 0, NULL, NULL);

			if (ret == FAILED)

				throw Exception("Receive data failed.");

			return ret;
		}

		int Datagram::ReceiveN(char* buffer, int length, Address& addr){	

			SockLen len = sizeof(sockaddr);

			int ret = recvfrom(GetHandle(), buffer, length, 0, (sockaddr*)&addr.Sockaddr(), &len);

			if (ret == FAILED)

				throw Exception("Receive data failed.");

			return ret;
		}

		int Datagram::SendN(const char* buffer, int length, const Address& addr){

			int ret = sendto(GetHandle(), buffer, length, 0, (const sockaddr*)&addr.Sockaddr(),

					sizeof(sockaddr));

			if (ret == FAILED)	

				throw Exception("Send data failed.");

			return ret;
		}

		int Datagram::Receive(char* buffer, int length) {	

			int ret = recvfrom(GetHandle(), buffer, length, 0, NULL, NULL);

			if (ret == FAILED && GetLastError() != RWOULDBLOCK)

				throw Exception("Receive data failed.");


			return ret;
		}

		int Datagram::Receive(char* buffer, int length, Address& addr) {	

			SockLen len = sizeof(sockaddr);

			int ret = recvfrom(GetHandle(), buffer, length, 0, (sockaddr*)&addr.Sockaddr(), &len);

			if (ret == FAILED && GetLastError() != RWOULDBLOCK)

				throw Exception("Receive data failed.");

			return ret;
		}

		int Datagram::Send(const char* buffer, int length, const Address& addr){

			int ret = sendto(GetHandle(), buffer, length, 0, (const sockaddr*)&addr.Sockaddr(),

					sizeof(sockaddr));

			if (ret == FAILED && GetLastError() != RWOULDBLOCK)

				throw Exception("Send data failed.");

			return ret;
		}
	}
}

