#include <Stream.hpp>
#include <Address.hpp>
#include <Exception.hpp>
#include <Connector.hpp>

namespace PWRD{

	namespace Network{

		Connector::Connector(void){ }

		Connector::~Connector(void){ }

		void Connector::Connect(const Address& remoteAddr, Stream& s){

			s.Open();

			if (::connect(s.GetHandle(), (sockaddr*)&remoteAddr.Sockaddr(),
						sizeof(sockaddr)) == FAILED){

				throw PWRD::Event::Exception("Connect to destination machine error!");

			}

		}
	}
}

