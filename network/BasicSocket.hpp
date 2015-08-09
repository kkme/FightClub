#ifndef __SOCKET_BASIC_SOCKET_H
#define __SOCKET_BASIC_SOCKET_H

#include <Socket.hpp>

using namespace PWRD::Network;

namespace PWRD{

	namespace Network{

		class Address;

		template <class SocketTypeT>

			class BasicSocket : public SocketBase{

				public:

					typedef SocketTypeT SocketType;

					BasicSocket(void);

					~BasicSocket(void);

					// Declare the copy constructor and assignment operator in private, so
					// ensure the BasicSocket object not to allow copy!
					
				private:

					BasicSocket(const BasicSocket&);

					const BasicSocket& operator=(const BasicSocket&);

				public:

					void Open();

					/**
					 * Destory socket object.
					 */
					void Close();

					void Open(const Address& addr);
			};

	}
}

#include "./BasicSocket.tmpl"

#endif
