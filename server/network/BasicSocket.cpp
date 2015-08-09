#include <sstream>
#include <Address.hpp>
#include <Exception.hpp>
#include <SocketType.hpp>
#include <BasicSocket.hpp>

using namespace PWRD::Event;

namespace PWRD{

	namespace Network{

		template <class SocketType>

			BasicSocket<SocketType>::BasicSocket(void){

				Attach(INVALID_HANDLE);
			}

		template <class SocketType>
			BasicSocket<SocketType>::~BasicSocket(void){

				Close();

			}

		template <class SocketType>
			void BasicSocket<SocketType>::Open(){

				Handle sock = ::socket(SocketType::Family(), SocketType::SocketType(), SocketType::Protocol());

				if (sock == INVALID_HANDLE)

					throw Exception("Create a socket failed!");

				int optval = 1;
				
				if(::setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) < 0){

					throw Exception("Setsockopt failed!");

				}

				Error("----------------------------------------------");

				Attach(sock);

			}

		template <class SocketType>
			void BasicSocket<SocketType>::Open(const Address& addr){

				Open();

				if (::bind(GetHandle(), (sockaddr*)(&addr.Sockaddr()), sizeof(sockaddr_in)) == FAILED)

					throw Exception("Bind a socket failed!");
			}

		/**
		 * Destory socket object.
		 */
		template <class SocketType>
			void BasicSocket<SocketType>::Close(){

				if (GetHandle() != INVALID_HANDLE){

					CloseSocket(GetHandle());

					Attach(INVALID_HANDLE);

				}
			}
	}
}

