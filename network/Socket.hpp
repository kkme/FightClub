#ifndef __SOCKET_SOCKET_BASE_H
#define __SOCKET_SOCKET_BASE_H

#include <string>
#include <SocketDef.hpp>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

using namespace PWRD;

namespace PWRD{

	namespace Network{

		class  SocketBase {

			public:
				/**
				 * Retrieves socket handle.
				 * @return: socket handle.
				 */

				inline Handle GetHandle() const;

				inline void Attach(Handle s);

				inline Handle Detach();

				void Nonblock();

			private:

				Handle socket_;

			protected:

				SocketBase(void);

				~SocketBase(void);
		};


		inline Handle SocketBase::GetHandle() const {

			return socket_;
		}

		inline void SocketBase::Attach(Handle s) {

			socket_ = s;

		}

		inline Handle SocketBase::Detach() {

			Handle h = socket_;

			socket_ = INVALID_HANDLE;

			return h;
		}

	}//Network

}//PWRD

#endif

