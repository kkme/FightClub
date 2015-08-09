#ifndef __MYSQL_H 
#define __MYSQL_H

#include <Conf.hpp>
#include <Global.hpp>
#include <Daemon.hpp>

#include <boost/tokenizer.hpp>
#include <boost/tuple/tuple.hpp>

#include <mysql_driver.h>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>

using namespace sql;
using namespace boost;

namespace PWRD{

	namespace DB{

		typedef std::vector<string> StringList;

		typedef std::vector< boost::shared_ptr<PreparedStatement> > PSList;

		typedef std::pair<PreparedStatement, PreparedStatement > StringPair;

		class MySQL{

			public:

				MySQL(string& _url, string& _user, string& _pass, string& _db):url_(_url), user_(_user), pass_(_pass), db_(_db){ init(); };

				virtual ~MySQL(){ fini(); };

			protected:

				int init();

				int fini();


				//interface
			public:

				virtual int Connect();

				virtual int Execute(const string& _sql);

				virtual int Execute(const char*, int);

				virtual int Update(const string& _sql);

				virtual int Update(const char*, int);

				virtual int Update(PreparedStatement* _ps);

				virtual int Update(StringList* _list);

				virtual int Update(PSList* _list);

				virtual ResultSet* Update(PreparedStatement* _p1, PreparedStatement* _p2);

				virtual int Close();

				virtual ResultSet* Query(const string& _qurey);

				virtual ResultSet* Query(const char *, int);

				virtual ResultSet* Query(PreparedStatement* _ps);

				virtual PreparedStatement* Get(const string& _qurey);

				//getter & setter

			private:

				string url_;

				string user_;

				string pass_;

				string db_;

			private:

				sql::Driver *driver_;

				sql::Connection *conn_;

				sql::Statement * stmt_;

				sql::ResultSet *rstset_;

				sql::PreparedStatement *pstmt_;

		};
	}

}

#endif
