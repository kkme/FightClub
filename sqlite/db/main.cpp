#include <sqlite3.hpp>
#include <stdio.h>
#include <sstream>

using namespace std;
using namespace PWRD::DB;

typedef struct {
	const char* argv1;
	const char* argv2;
}bind_args_t;

class Sqlite3 : public Sqlite3DB {
	public:
		Sqlite3 (string& filename) : Sqlite3DB(filename) {};

		void result () {
			while (true) {
				step();

				if (isdone()) 
					break;

				if (!isrow()) {
					printf("error : %s\n", errmsg());
					break;
				}

				//sqlite3_column_count(stmt());

				const unsigned char* id      = sqlite3_column_text(stmt(), 0);
				const unsigned char* content = sqlite3_column_text(stmt(), 1);
				const unsigned char* remark  = sqlite3_column_text(stmt(), 2);
				printf("id=%s content=%s remark=%s\n", id, content, remark);
			}
		}

		int exec_callback(void* args __attribute__((unused)), int nums, char** columns, char** columns_name) {
			string row;
			for (int i=0; i<nums; ++i) {
				row.append (columns_name[i]);
				row.append ("=");
				row.append (NULL == columns[i] ? "NULL" : columns[i]);
				row.append (",");
			}
			printf("%s\n", row.c_str());
			row.clear();
			return 0;
		};

		void bind (void* args) {
			/*
			int sqlite3_bind_blob(sqlite3_stmt*, int, const void*, int n, void(*)(void*));
			int sqlite3_bind_double(sqlite3_stmt*, int, double);
			int sqlite3_bind_int(sqlite3_stmt*, int, int);
			int sqlite3_bind_int64(sqlite3_stmt*, int, sqlite3_int64);
			int sqlite3_bind_null(sqlite3_stmt*, int);
			int sqlite3_bind_text(sqlite3_stmt*, int, const char*, int n, void(*)(void*));
			int sqlite3_bind_text16(sqlite3_stmt*, int, const void*, int, void(*)(void*));
			int sqlite3_bind_value(sqlite3_stmt*, int, const sqlite3_value*);
			int sqlite3_bind_zeroblob(sqlite3_stmt*, int, int n);
			*/

			bind_args_t* bind_args = (bind_args_t*)args;

			sqlite3_bind_text(stmt(), 1, bind_args->argv1, -1, NULL);
			sqlite3_bind_text(stmt(), 2, bind_args->argv2, -1, NULL);

			printf("%s, %s\n", bind_args->argv1, bind_args->argv2);
		};


};

int main () {
	/**********open**********/
	char* errmsg;
	string sql;
	string file("realtimelogs.db");

	Sqlite3 sqlite(file);
	if (!sqlite.isok())
		printf("%d %s \n", __LINE__, sqlite.errmsg());

	/**********insert**********/
	for (int i=0; i<10; ++i) {
		sql.clear();sql.append("insert into regex(content) values('yyyyy');");
		printf("%s\n", sql.c_str());

		sqlite.prepare(sql);
		if (!sqlite.isok())
			printf("%d %s \n", __LINE__, sqlite.errmsg());

		sqlite.step();
		if (!sqlite.isdone())
			printf("%d %s \n", __LINE__, sqlite.errmsg());

		sqlite.finalize();
	}

	/***********select*********/
	sql.clear();sql.append("select id,content,remark from regex;");
	printf("%s\n", sql.c_str());

	sqlite.prepare(sql);
	if (!sqlite.isok())
		printf("%d %s \n", __LINE__, sqlite.errmsg());

	sqlite.result();
	
	sqlite.finalize();

	/********rest bind************/
	sql.clear();sql.append("insert into regex(content,remark) values(?1, ?2);");
	printf("%s\n", sql.c_str());

	sqlite.prepare(sql);
	if (!sqlite.isok())
		printf("%d %s \n", __LINE__, sqlite.errmsg());

	bind_args_t bind_args;
	for (int i=0; i<10; ++i) {
		char argv1[10];
		char argv2[10];
		snprintf(argv1, 10, "%s %d", "bind", i);
		snprintf(argv2, 10, "%s %d", "reset", i);

		bind_args.argv1 = argv1;
		bind_args.argv2 = argv2;


		sqlite.reset();
		sqlite.bind(&bind_args);

		sqlite.step();
		if (!sqlite.isdone())
			printf("%d %s \n", __LINE__, sqlite.errmsg());
	}

	/*********exec insert**********/
	sql.clear();sql.append("insert into regex(content) values('execute tttt...');");
	printf("%s\n", sql.c_str());
	errmsg = NULL;
	sqlite.exec(sql, errmsg);

	if (sqlite.isabort())
		printf("%d %d %s", __LINE__, sqlite.g_errno(), errmsg);
	sqlite.finalize();

	/**********exec select*********/
	sql.clear();sql.append("select * from regex");
	printf("%s\n", sql.c_str());
	errmsg = NULL;
	sqlite.exec(sql, errmsg, NULL);

	if (sqlite.isabort())
		printf("%d %d %s", __LINE__, sqlite.g_errno(), errmsg);
	sqlite.finalize();
}
