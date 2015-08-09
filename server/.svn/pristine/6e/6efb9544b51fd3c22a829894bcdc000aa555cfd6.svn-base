#include <AsyncTimer.hpp>

namespace PWRD{

	namespace Utils{

		/*
		 *protected
		 */

		int AsyncTimer::init(){

			Conf *conf = Conf::GetInstance(file_.c_str());

			if(NULL == conf){

				Error("Conf GetInstance failed");

				return -1;

			}

			string secstr = conf->find("AsyncTimer", "seconds");

			stringstream ss;

			ss << secstr;

			ss >> seconds_;

			Trace("TRACE AsyncTimer timeout: seconds=%d", seconds_);
			
			timer_.expires_from_now(boost::posix_time::seconds(seconds_));

			timer_.async_wait(boost::bind(&AsyncTimer::Action, this, boost::asio::placeholders::error, boost::ref(timer_)));

			return 1;

		}

		int AsyncTimer::fini(){

			return 1;
		}

		/*
		 *public
		 */
		void AsyncTimer::Run(){

			Trace("TRACE AsyncTimer Run");

			io_service_.run();

		}

		void AsyncTimer::Action(const boost::system::error_code& _ec, boost::asio::deadline_timer& _t){

			Trace("TRACE AsyncTimer Action");

			if(!_ec){

				builder_.Load();

				_t.expires_from_now(boost::posix_time::seconds(seconds_));

				_t.async_wait(boost::bind(&AsyncTimer::Action, this, boost::asio::placeholders::error, boost::ref(_t)));

			}
			else{
			
				Error("AsyncTimer failed!");
			
			}

		}


	}

}
