#ifndef __PIPE_HPP
#define __PIPE_HPP

#include <Global.hpp>

#include <Daemon.hpp>

using namespace PWRD;

namespace PWRD{

		class Pipe{

			public:

				Pipe(){ init(); };

				virtual ~Pipe(){ fini(); }

				int infd(){ return fds_[0]; }

				int outfd(){ return fds_[1]; }

			protected:

				int init(){ 

					if( pipe(fds_) < 0){
						
						Error("Create Pipe faield: errmsg=%s", strerror(errno));

						return -1;

					}

					Trace("TRACE Pipe fd: infd=%d, outfd=%d", fds_[0], fds_[1]);

					fcntl(fds_[0], F_SETFL, fcntl(fds_[0], F_GETFL, 0) | O_NONBLOCK); 

					return 1;
				
				};

				int fini(){
					
					return 1;

				}

			private:

				int fds_[2];


		};

}

#endif
