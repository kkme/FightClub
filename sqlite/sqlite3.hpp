#ifndef PWRD_DB_SQLIT_HPP
#include <sqlite3.h>
#include <iostream>
#include <stdio.h>

namespace PWRD { namespace DB {

	using namespace std;
	/**
	 * @Synopsis  以READ WRITE方式打开; 每次只支持执行1条sql; 线程不安全;
	 */
	class Sqlite3DB {
		public:

			/**
			 * @Synopsis  Sqlite3DB 
			 *
			 * @Param filename
			 * @The filename of database need to open.
			 * @ isok() == true 成功, 否则可以print errmsg()
			 */
			Sqlite3DB (string&);

			/**
			 * @Synopsis  ~Sqlite3DB 
			 * @If the db was opened then close it.
			 */
			virtual ~Sqlite3DB ();

			/**
			 * @Synopsis  prepare 
			 * @Compiling An SQL Statement
			 *
			 * @Param string SQL statement, UTF-8 encoded
			 *
			 * @Returns  void 
			 */
			void prepare (string&);


			/**
			 * @Synopsis  result 
			 * @virtual 的函数 自定义处理查询结果
			 */
			virtual void result ();

			/**
			 * @Synopsis  column_count 
			 *
			 * @Returns isrow() == true 返回当前的列数 
			 */
			int column_count ();
			/**
			 * @Synopsis  finalize 
			 * @This routine destroys a prepared statement created by a prior call to sqlite3_prepare(). 
			 * @Every prepared statement must be destroyed using a call to this routine in order to avoid memory leaks. 
			 */
			void finalize ();

			/**
			 * @Synopsis  step 
			 * @Evaluate An SQL Statement
			 *
			 * @Returns  void 
			 */
			void step();

			/**
			 * @Synopsis  reset 
			 * @If the most recent call to sqlite3_step(S) for the prepared statement S returned SQLITE_ROW or SQLITE_DONE, 
			 * or if sqlite3_step(S) has never before been called on S, then sqlite3_reset(S) returns SQLITE_OK.
			 *
			 * If the most recent call to sqlite3_step(S) for the prepared statement S indicated an error, 
			 * then sqlite3_reset(S) returns an appropriate error code.
			 */
			void reset ();

			/**
			 * @Synopsis  bind
			 */
			virtual void bind (void*) {};

			/**
			 * @Synopsis  errmsg 
			 *
			 * @Returns  返回错误信息 
			 */
			const char* errmsg ();

			/**
			 * @Synopsis  isok
			 * @判断返回状态是否是 SQLITE_OK 
			 *
			 * @Returns  bool 
			 */
			bool isok (); 

			/**
			 * @Synopsis  isdone 
			 * @判断返回状态是否是 SQLITE_DONE
			 * @判断返回的数据是否取完 通过step()
			 *
			 * @Returns  bool 
			 */
			bool isdone ();

			/**
			 * @Synopsis  isrow 
			 * @判断返回状态是否是 SQLITE_ROW
			 * @step() 后时候有数据返回
			 *
			 * @Returns   
			 */
			bool isrow ();

			/**
			 * @Synopsis  isreset 判断reset是否成功, 没太多必要去判断这个值是否正确
			 * @If the most recent call to sqlite3_step(S) for the prepared statement S returned SQLITE_ROW or SQLITE_DONE, 
			 * @or if sqlite3_step(S) has never before been called on S, then sqlite3_reset(S) returns SQLITE_OK.
			 * @If the most recent call to sqlite3_step(S) for the prepared statement S indicated an error, 
			 * then sqlite3_reset(S) returns an appropriate error code.
			 *
			 * @Returns  bool 
			 */
			bool isreset();
			/**
			 * @Synopsis  stmt 
			 * @返回prepair()后的stmt 用于获取返回数据
			 *
			 * @Returns   
			 */
			sqlite3_stmt* stmt() {
				return stmt_;
			};

			int g_errno (){
				return g_errno_;
			};

			void set_g_errno (int err) {
				g_errno_ = err;
			};
		public:
			/**
			 * @Synopsis  exec 
			 * @参见exec(string&)
			 *
			 * @Param string sql
			 * @Param errmsg 正常返回NULL  
			 * @Param args 回调函数的第一个参数 回调参见virutal exec_callback
			 */
			void exec(string& sql, char* errmsg, void* args);

			/**
			 * @Synopsis  exec 
			 * @调用sqlite3_exec(), 包裹了sqlite3_prepare_v2(), sqlite3_step(), and sqlite3_finalize()
			 *
			 * @Param string sql语句 
			 * @Param errmsg 正常返回NULL   如果返回非空必须调用free避免内存泄漏
			 */
			void exec(string& sql, char* errmsg);

			/**
			 * @Synopsis  exec_callback 
			 *
			 * @Param args exec(string& sql, void* args) 的args参数
			 * @Param nums 返回的列数
			 * @Param columns 列的char**
			 * @Param columns_name 列名的char**
			 *
			 * @Returns  如果返回0表示正常
			 * @如果出错返回非0, 这样调用isabort()返回true
			 */
			virtual int exec_callback(void* args, int nums, char** columns, char** columns_name);

			/**
			 * @Synopsis  isabort 判断exec的回调函数是否出错
			 * @判断返回状态是否是 SQLITE_ABORT 
			 *
			 * @Returns  bool 
			 */
			bool isabort();

			/**
			 * @Synopsis  free 
			 *
			 * @Param arg 调用sqlite3_free释放内存
			 */
			void free (void* arg);
		private:
			static int exec_callback_(void* args, int nums, char** columns, char** columns_name);

		private:
			string filename_;
			sqlite3* db_;
			sqlite3_stmt* stmt_;
			int g_errno_;

	};
}}
#endif
