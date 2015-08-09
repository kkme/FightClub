
#include <Socket.hpp>
#include <SocketDef.hpp>

using namespace PWRD;
using namespace PWRD::Network;

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
