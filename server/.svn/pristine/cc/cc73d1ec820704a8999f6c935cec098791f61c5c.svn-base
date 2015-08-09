#ifndef __ASYNC_TIMER_HPP
#define __ASYNC_TIMER_HPP

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <Conf.hpp>
#include <Global.hpp>
#include <Daemon.hpp>
#include <XMLBuilder.hpp>

using namespace PWRD;
using namespace PWRD::XML;

namespace PWRD{

	namespace Utils{

		class AsyncTimer{

			public:

				AsyncTimer(string& _file, XMLBuilder& _builder, boost::asio::io_service& _io_service):file_(_file), builder_(_builder), timer_(_io_service), io_service_(_io_service){ init(); }

				virtual ~AsyncTimer(){ fini(); }

				void Run();

				void Action(const boost::system::error_code& _ec, boost::asio::deadline_timer& _t);

				boost::asio::deadline_timer& timer(){ return  timer_; };

				boost::asio::io_service& io_service(){ return io_service_; };

			protected:

				int init();

				int fini();


			private:

				int seconds_;

				string file_;

				XMLBuilder& builder_;

				boost::asio::deadline_timer timer_;

				boost::asio::io_service& io_service_;

		};

	}

}


#endif
