#include <sstream>
#include "Exception.hpp"
#include  "SocketOS.hpp"
#include "SocketDef.hpp"

namespace PWRD{

	namespace Event{

		Exception::Exception(const std::string& msg) : msg_(msg) {

			msg_ += " Code:";

			std::ostringstream oss;

			oss << GetLastError();

			msg_ += oss.str();

		}


		Exception::~Exception() throw() { }

		const char* Exception::what() const throw() {

			return msg_.c_str();

		}

	}

}
