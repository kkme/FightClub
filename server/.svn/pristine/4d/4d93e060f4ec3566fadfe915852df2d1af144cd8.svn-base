#ifndef DAEMON_HPP

#define DAEMON_HPP



#include <stdio.h> 

#include <string.h>

#include <string>

#include <iostream>

#include <strings.h>

#include <stdarg.h>

#include <time.h>

#include <stdlib.h>

#include <pthread.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <sys/file.h>

#include <signal.h>



using namespace std;



namespace PWRD

{



#define DATETIME_SIZE 20

	class FormatTime

	{

		public:

			// 获取当前时间 xxxx-xx-xx xx:xx:xx

			char *getdatetime();



			// 获取当前时间 xx:xx:xx

			char* gettime ();



			// 获取当前日期 xxxx-xx-xx

			char* getdate ();



			// 根据时间戳 转换成时间 xxxx-xx-xx xx:xx:xx 

			char* getdatetime (time_t timep);



		private:

			char timer[DATETIME_SIZE];

			struct tm times;

			void format_time(time_t time_stamp);

	};





	void Signal();

	int  Daemon(char *);



	//定义日志打印级别

#define DEBUG  0

#define DETAIL 1

#define NORMAL 2

#define SIMPLE 3



#ifndef LEVEL

#define LEVEL NORMAL

#endif


#define Trace(FORMAT, ...) logs.write_log(DEBUG, FORMAT, ##__VA_ARGS__)

#define Error(FORMAT, ...) logs.write_log(NORMAL, FORMAT, ##__VA_ARGS__)

#define Note(FORMAT, ...) logs.write_log(NORMAL, FORMAT, ##__VA_ARGS__)

#define write_log(flag, fmt, ...) write_(__FILE__, __func__, __LINE__, flag , fmt , ##__VA_ARGS__)

	class WriteLog 

	{

		public:

			WriteLog();

			~WriteLog();

			/* 打印日志函数 */

			void write_(const char *file, const char* func, \

					const int line, int flag , const char* fmt, ... );

			static const char *level[4];

		private:

			int pfd;

			PWRD::FormatTime mytime;

	};



};



extern PWRD::WriteLog logs;



#endif

