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

		typedef tuple<int, string, int, int,string> Result;

		typedef std::vector<Result> ResultList;

		typedef std::vector<string> StringList;

		class MySQL{

			public:

				MySQL(string _url, string _user, string _pass, string _db):url_(_url), user_(_user), pass_(_pass), db_(_db){ init(); };

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

				virtual int Close();

				virtual ResultSet* Qurey(const string& _qurey);

				virtual ResultSet* Qurey(const char *, int);

				virtual ResultSet* Qurey(PreparedStatement* _ps);

				//getter & setter
			public:
				void set_url(string _url){ url_ = _url; };
				void set_user(string _user){ user_ = _user; };
				void set_pass(string _pass){ pass_ = _pass; };
				void set_db(string _db){ db_ = _db; };

				void set_sql(string _sql){sql_ = _sql;};

				string url(){return url_;};
				string user(){return user_;};
				string pass(){return pass_;};
				string db(){return db_;};
				string sql(){return sql_;}

			private:
				string url_;
				string user_;
				string pass_;
				string db_;
				string sql_;
				string qurey_sql_;

			private:
				sql::Driver *driver_;
				sql::Connection *conn_;
				sql::Statement * stmt_;
				sql::PreparedStatement *pstmt_;
				sql::ResultSet *rstset_;

		};
	}

}

#endif
