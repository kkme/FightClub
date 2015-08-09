#ifndef __PIDSET_HPP

#define __PIDSET_HPP

#include <Global.hpp>

#include <Daemon.hpp>

using namespace PWRD;

namespace PWRD{

	namespace IPC{

		class PidSet{	

			public:

				static bool Exist(pid_t);

				static void Kill(pid_t);

		};

	}

}

#endif

