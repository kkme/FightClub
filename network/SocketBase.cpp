#include <cassert>
#include <Exception.hpp>
#include <Socket.hpp>

namespace PWRD{

	namespace Network{

		SocketBase::SocketBase(void) { }

		SocketBase::~SocketBase(void) { }

		void SocketBase::Nonblock(){

			assert(socket_ != INVALID_HANDLE);

			int opt = fcntl(socket_, F_GETFL);

			if (opt == -1)

				throw PWRD::Event::Exception("Nonblock(get) failed");

			if (fcntl(socket_, F_SETFL, opt | O_NONBLOCK) == -1)

				throw PWRD::Event::Exception("Nonblock(set) failed");

		}
	}
}
