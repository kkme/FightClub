#ifndef __REQUEST_HPP
#define __REQUEST_HPP

#include <Global.hpp>
#include <Stringpool.hpp>
#include <ActiveLogRecord.hpp>

using namespace PWRD;
using namespace PWRD::ActiveObject;

namespace PWRD{

	namespace ActiveObject{


		class Request{

			public:

				Request(const char *_buf, int _len):buffer_(_buf), len_(_len){ init(); };

				virtual ~Request(){ fini(); };
				
				bool Call();

			protected:

				int init();

				int fini();

			private:

				const char *buffer_;

				int len_;

				string *buf_;

				LogRecord record_;

		};

	}


}

#endif
