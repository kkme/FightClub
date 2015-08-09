#ifndef __TASKDEF_HPP

#define __TASKDEF_HPP

#include <map>

#include <unistd.h>

#include <Global.hpp>

#include <Daemon.hpp>

#include <boost/tuple/tuple.hpp>



#include <boost/bind.hpp>

#include <boost/asio.hpp>

#include <boost/asio/io_service.hpp>

#include <boost/asio/deadline_timer.hpp>



using namespace PWRD;

using namespace boost;


namespace PWRD{

	namespace Schedule{



		typedef enum{READ = 0, WRITE = 1} IODIRECT;



		typedef tuple<int, int> Pair;



		typedef map<int, Pair>  PairPool;



		class PipeFactory{



			public:

				static Pair getInstance(){

					int fd[2];

					if(pipe(fd) < 0){

						logs.write_log(NORMAL, "create pipe error: errno=%d, errmsg=%s",

								errno, strerror(errno));

						return make_tuple(-1, -1);

					}

					else{

						Pair pair = make_tuple(fd[0], fd[1]); 

						pairpool_[fd[0]] =  pair;

						return pair;

					}

				}

				static PairPool& pairpool(){return pairpool_;}



			private:

				static PairPool pairpool_;

		};

	}

}

#endif
