#include <SocketType.hpp>

namespace PWRD{

	namespace Network{

		int StreamType::Family() {

			return AF_INET;

		}

		int StreamType::SocketType() {

			return SOCK_STREAM;

		}

		int StreamType::Protocol() {

			return IPPROTO_TCP;

		}

		int DatagramType::Family() {

			return AF_INET;

		}

		int DatagramType::SocketType() {

			return SOCK_DGRAM;

		}

		int DatagramType::Protocol() {

			return IPPROTO_UDP;

		}
	}
}

