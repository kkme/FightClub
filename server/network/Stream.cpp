#include <Stream.hpp>
#include <Address.hpp>
#include <Exception.hpp>
#include <SocketDef.hpp>

using namespace PWRD::Event;

namespace PWRD{

	namespace Network{

		Stream::Stream(void) {

		}

		Stream::~Stream(void) {

		}

		int Stream::SendN(const char* buffer, int length) {

			int total = 0;

			for (int bytes = 0; total < length; total += bytes) {

				bytes = ::send(GetHandle(), buffer + total, length - total, MSG_NOSIGNAL);

				if (bytes == FAILED)

					throw Exception("Send stream error!");

			}

			return total;
		}

		int Stream::ReceiveN(char* buffer, int length) {

			int bytes = ::recv(GetHandle(), buffer, length, 0);

			if (bytes == FAILED)

				throw Exception("Receive stream error!");

			return bytes;
		}

		int Stream::Send(const char* buffer, int length) {

			int bytes = ::send(GetHandle(), buffer, length, MSG_NOSIGNAL);

			if (bytes == FAILED && GetLastError() != RWOULDBLOCK)

				throw Exception("Send stream error!");

			return bytes;
		}

//#include <stdio.h>
		int Stream::Receive(char* buffer, int length) {
			/*

			typedef struct{

				int type;

				long length;

				float version;

			}HH;
		

			char buf[44];
			HH head;

			for(;;){
				
				int bytes = ::read(GetHandle(), buf, 44);

				memcpy(&head, buf, 12);

				printf("--------------types=%d, type=%d, len=%d-------------\n", bytes, head.type, head.length);

			}

			return 0;
			*/

			int bytes = ::recv(GetHandle(), buffer, length, 0);

			if (bytes == FAILED && GetLastError() != RWOULDBLOCK)

				throw Exception("Receive stream error!");

			return bytes;
		}

	}

}
