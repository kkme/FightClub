#ifndef __ASYNCMYSQL_HPP
#define __ASYNCMYSQL_HPP

#include <MySQL.hpp>
#include <ActiveQueue.hpp>

using namespace PWRD;
using namespace PWRD::DB;
using namespace PWRD::ActiveObject;

namespace PWRD{

	namespace DB{

		typedef ActiveQueue<string*> MySQL_Request;

		typedef ActiveQueue<ResultSet*> MySQL_Response;

		class AsyncQureyMySQL: public MySQL{

			public:

				AsyncQureyMySQL(string _url, string _user, string _pass, string _db):MySQL(_url, _user, _pass, _db){};

				virtual ~AsyncQureyMySQL(){}

				void Run();

				MySQL_Request& Request(){ return request_; }

				MySQL_Response& Response(){ return response_; }


			protected:

				int init();

				int fini();

			private:

				MySQL_Request request_;

				MySQL_Response response_;	

		};

		class AsyncUpdateMySQL: public MySQL{

			public:

				AsyncUpdateMySQL(string _url, string _user, string _pass, string _db):MySQL(_url, _user, _pass, _db){};

				virtual ~AsyncUpdateMySQL(){}

				void Run();

				MySQL_Request& Request(){ return request_; }


			protected:

				int init();

				int fini();

			private:

				MySQL_Request request_;

		};

	}

}

#endif
