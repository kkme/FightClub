#ifndef __TRANSFORM_HPP
#define __TRANSFORM_HPP

#include <Daemon.hpp>
#include <Global.hpp>
#include <Monitor.pb.h>
#include <MonitorBlock.hpp>

using namespace PWRD;

using namespace PWRD::JSON;

namespace PWRD{

	class Transform{

		public:

			static Response* Process(Result* _result){

				Response* response = new Response();

				assert(NULL != response);

				response->set_type(_result->type());

				response->set_taskid(_result->taskid());

				stringstream ss;

				string errnumstr;

				ss << _result->errnum();

				ss >> errnumstr;

				response->set_errnum(errnumstr);

				response->set_errmsg(_result->errmsg());

				FormatTime time;

				string timestamp(time.getdatetime());

				response->set_timestamp(timestamp);

				return response;

			}

	};

}

#endif
