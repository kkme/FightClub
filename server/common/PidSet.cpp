#include <PidSet.hpp>

#include <Mutex.hpp>

using namespace PWRD::IPC;

namespace PWRD{

	namespace IPC{

		bool PidSet::Exist(pid_t _pid){

			int ret = 0;

			if((ret = kill(_pid, 0)) < 0){

				return false;

			}

		}

		void PidSet::Kill(pid_t _pid){

			Note("Kill the process: pid=%d", _pid);

			kill(_pid, SIGKILL);
		}

	}

}

