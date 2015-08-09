#include "sqlite3.hpp"

using namespace std;
using namespace PWRD::DB;

Sqlite3DB::Sqlite3DB (string& _filename):
	filename_(_filename),
	stmt_(NULL) {
		g_errno_ = sqlite3_open_v2 (filename_.c_str(), &db_, SQLITE_OPEN_READWRITE, NULL);
	};

Sqlite3DB::~Sqlite3DB () {
	if (NULL != db_)
		sqlite3_close(db_);
};

void Sqlite3DB::prepare (string& sql) {
	g_errno_ = sqlite3_prepare_v2(db_, sql.c_str(), sql.length(), &stmt_, NULL);
};

void Sqlite3DB::step() {
	g_errno_ = sqlite3_step(stmt_);
};

void Sqlite3DB::result () {
	printf("%s\n", "Result Values From A Query: (Get sqlite3_stmt* by stmt().)\n\
        const void*  sqlite3_column_blob(sqlite3_stmt*, int iCol);\n\
               int   sqlite3_column_bytes(sqlite3_stmt*, int iCol);\n\
               int   sqlite3_column_bytes16(sqlite3_stmt*, int iCol);\n\
            double   sqlite3_column_double(sqlite3_stmt*, int iCol);\n\
               int   sqlite3_column_int(sqlite3_stmt*, int iCol);\n\
      sqlite3_int64  sqlite3_column_int64(sqlite3_stmt*, int iCol);\n\
const unsigned char* sqlite3_column_text(sqlite3_stmt*, int iCol);\n\
     const void*     sqlite3_column_text16(sqlite3_stmt*, int iCol);\n\
             int     sqlite3_column_type(sqlite3_stmt*, int iCol);\n\
     sqlite3_value*  sqlite3_column_value(sqlite3_stmt*, int iCol);\n\n\n\
These routines attempt to convert the value where appropriate. \n\
For example, if the internal representation is FLOAT and a text \n\
result is requested, sqlite3_snprintf() is used internally to perform \n\
the conversion automatically. \n\n\
The following table details the conversions that are applied:\n \
+----------+---------+-------------------------------+\n \
|Internal|Requested  |Conversion                     |\n \
|Type    |Type       |                               |\n \
+--------+-----------+-------------------------------+\n \
|NULL    |INTEGER    |Result is 0                    |\n \
+--------+-----------+-------------------------------+\n \
|NULL    |FLOAT      |Result is 0.0                  |\n \
+--------+-----------+-------------------------------+\n \
|NULL    |TEXT       |Result is NULL pointer         |\n \
+--------+-----------+-------------------------------+\n \
|NULL    |BLOB       |Result is NULL pointer         |\n \
+--------+-----------+-------------------------------+\n \
|INTEGER |FLOAT      |Convert from integer to float  |\n \
+--------+-----------+-------------------------------+\n \
|INTEGER |TEXT       |ASCII rendering of the integer |\n \
+--------+-----------+-------------------------------+\n \
|INTEGER |BLOB       |Same as INTEGER->TEXT          |\n \
+--------+-----------+-------------------------------+\n \
|FLOAT   |INTEGER    |Convert from float to integer  |\n \
+--------+-----------+-------------------------------+\n \
|FLOAT   |TEXT       |ASCII rendering of the float   |\n \
+--------+-----------+-------------------------------+\n \
|FLOAT   |BLOB       |Same as FLOAT->TEXT            |\n \
+--------+-----------+-------------------------------+\n \
|TEXT    |INTEGER    |Use atoi()                     |\n \
+--------+-----------+-------------------------------+\n \
|TEXT    |FLOAT      |Use atof()                     |\n \
+--------+-----------+-------------------------------+\n \
|TEXT    |BLOB       |No change                      |\n \
+--------+-----------+-------------------------------+\n \
|BLOB    |INTEGER    |Convert to TEXT then use atoi()|\n \
+--------+-----------+-------------------------------+\n \
|BLOB    |FLOAT      |Convert to TEXT then use atof()|\n \
+--------+-----------+-------------------------------+\n \
|BLOB    |TEXT       |Add a zero terminator if needed|\n \
+--------+-----------+-------------------------------+"); 
}

int Sqlite3DB::column_count () {
	return sqlite3_column_count(stmt_);
};

void Sqlite3DB::finalize () {
	g_errno_ = sqlite3_finalize (stmt_);
};

bool Sqlite3DB::isdone () {
	return g_errno_ == SQLITE_DONE ? true : false;
};

bool Sqlite3DB::isrow () {
	return g_errno_ == SQLITE_ROW ? true : false;
};

bool Sqlite3DB::isok () {
	return g_errno_ == SQLITE_OK ? true : false;
};

void Sqlite3DB::reset () {
	g_errno_ = sqlite3_reset(stmt_);
};

bool Sqlite3DB::isreset () {
	return (g_errno_ == SQLITE_OK || 
			g_errno_ == SQLITE_DONE ||
			g_errno_ == SQLITE_ROW) ? true : false;
};

const char* Sqlite3DB::errmsg () {
	return sqlite3_errmsg(db_);
};

/* exec */
typedef struct {
	void* object;
	void* args;
} sqlite_exec_cb_t;

void Sqlite3DB::exec(string& sql, char* errmsg, void* args) {
	sqlite_exec_cb_t object_args;
	object_args.object = this;
	object_args.args   = args;
	g_errno_ = sqlite3_exec(db_, sql.c_str(), exec_callback_, (void*)&object_args, &errmsg);
};

void Sqlite3DB::exec(string& sql, char* errmsg) {
	g_errno_ = sqlite3_exec(db_, sql.c_str(), NULL, NULL, &errmsg);
};

int Sqlite3DB::exec_callback(void* args, int nums, char** columns, char** columns_name) {
	printf("args =%p, column_nums=%d, columns=%p, columns_name=%p\n", args, nums, columns, columns_name);
	return 0;
};

int Sqlite3DB::exec_callback_(void* args, int nums, char** columns, char** columns_name) {
	sqlite_exec_cb_t* object_args = (sqlite_exec_cb_t*)args;
	return ((Sqlite3DB*)object_args->object)->exec_callback(object_args->args, nums, columns, columns_name);
};

bool Sqlite3DB::isabort() {
	return g_errno_ == SQLITE_ABORT ? true : false;
};
void Sqlite3DB::free (void* arg) {
	sqlite3_free(arg);
};
