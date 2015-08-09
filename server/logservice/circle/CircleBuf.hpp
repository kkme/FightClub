#ifndef __CIRCLE_BUFFER_HPP
#define __CIRCLE_BUFFER_HPP

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

#define CIRCLE_BUFFSIZE (8192*2) 

namespace PWRD {

	namespace Utils{


		class CircleBuffer {

			public:
				CircleBuffer () {
					buffer_ = new char[CIRCLE_BUFFSIZE];
					sp_ = csp_ = cep_ = buffer_;
					ep_ = buffer_ + CIRCLE_BUFFSIZE;
					full_ = false;
				};

				virtual ~CircleBuffer () {
					if (buffer_)
						delete buffer_;
				};

				ssize_t add (ssize_t);
				ssize_t add (size_t, size_t);

				ssize_t add (char*);
				ssize_t add (char*, size_t);

				ssize_t get (char*, size_t);

				size_t used ();
				size_t free ();

			private:
				char* sp_;  /* start pointer */
				char* ep_;  /* end pointer */
				char* csp_; /* current start pointer */
				char* cep_; /* current end pointer */
				char* buffer_;
				bool  full_;


			public:

				char* csp() { return csp_; };

				char* cep() { return cep_; };

				char* ep () { return ep_; }

				char* sp () { return sp_; };

		};
	}
}

#endif
