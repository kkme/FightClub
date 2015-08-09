#ifndef __TASK_HPP

#define __TASK_HPP

#include <boost/asio.hpp>

#include <boost/asio/io_service.hpp>

#include <boost/asio/deadline_timer.hpp>

#include <Global.hpp>

#include <JsonArgus.hpp>

#include <Reactor.hpp>

using namespace PWRD;

using namespace PWRD::JSON;

namespace PWRD{

	namespace Schedule{

		class Task{

			public:

				Task(string &_json):json_(_json){ init(); };

				virtual ~Task(){ fini(); }

				string& json(){ return json_; }

				Request& request(){ return request_; }


			protected:

				int init();

				int fini();

			private:

				string json_;

				Request request_;

		};

	}

}

#endif

