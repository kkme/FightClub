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

	}
}

#include <SocketBase.inl>

#endif

