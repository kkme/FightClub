#include "Daemon.hpp"



namespace PWRD

{



	/* class FormatTime */



	void FormatTime::format_time(time_t time_stamp)

	{

		time_t timep;

		bzero(timer, DATETIME_SIZE);

		timep = time(&time_stamp);

		localtime_r(&timep, &times);

	}



	char* FormatTime::getdatetime ()

	{

		format_time(0);

		sprintf(timer, "%d-%02d-%02d %02d:%02d:%02d", \

				(times.tm_year+1900), (times.tm_mon+1), times.tm_mday, \

				times.tm_hour, times.tm_min, times.tm_sec);

		return timer;

	}



	char* FormatTime::gettime ()

	{

		format_time(0);

		sprintf(timer, "%02d:%02d:%02d", times.tm_hour, times.tm_min, times.tm_sec);

		return timer;

	}



	char* FormatTime::getdate ()

	{

		format_time(0);

		sprintf(timer, "%d-%02d-%02d", (times.tm_year+1900), (times.tm_mon+1), times.tm_mday);

		return timer;

	}



	char* FormatTime::getdatetime (time_t timep)

	{

		format_time(timep);

		sprintf(timer, "%d-%02d-%02d %02d:%02d:%02d",

				(times.tm_year+1900), (times.tm_mon+1), times.tm_mday,

				times.tm_hour, times.tm_min, times.tm_sec);

		return timer;

	}



	// 静态函数 和 全局变量

	static string logFile;

	static string pidFile;

	static FILE *log_file = NULL;

	

	void Exit(int sig)

	{

		fprintf(stderr, "recv_signal=%d", sig);

		if (!pidFile.empty())

			unlink(pidFile.c_str());

		exit(0);

	}

	void Signal()

	{

		/*初始化信号*/

		sigset_t set;

		sigfillset(&set);

		sigdelset(&set, SIGTERM);

		sigdelset(&set, SIGINT);

		sigprocmask(SIG_BLOCK, &set, NULL);



		signal(SIGTERM, Exit);

		signal(SIGINT, Exit);

	}



	int Daemon(char *argv0)

	{

		int pid_fd;

		size_t found;

		string path, filepath(argv0);



		pidFile = filepath; pidFile.append(".pid");

		logFile = filepath; logFile.append(".log");



		found = filepath.find_last_of("/");

		path  = filepath.substr(0,found);

		if (chdir(path.c_str()) < 0)

		{

			fprintf(stderr, "chdir(%s)=%m", argv0);

			return -1;

		}



		if (NULL == (log_file=fopen(logFile.c_str(), "a+")))

		{

			printf("open=%s:msg=%m", logFile.c_str());

			return -1;

		}

		else

		{

			setlinebuf(log_file);



			/* 查看文件是否被锁 */

			if((pid_fd=open(pidFile.c_str(), O_WRONLY|O_CREAT|O_TRUNC, 00644)) < 0)

			{

				fprintf(stderr, "file=%s:open=%m", pidFile.c_str());

				return -1;

			}



			if(flock(pid_fd, LOCK_EX|LOCK_NB) < 0)

			{

				fprintf(stderr, "file=%s:flock=%m", pidFile.c_str());

				return -1;

			}



			/* 启动精灵进程 */

			if(daemon(1, 0) < 0)

			{

				fprintf(stderr, "daemon=%m");

				return -1;

			}



			umask(0);



			//写进程文件

			char mypid[50] = {0};

			sprintf(mypid, "%u", getpid());

			write(pid_fd, mypid, strlen(mypid));

		}



		return 0;

	}



	/* class WriteLog */

	const char *WriteLog::level[] = {"DEBUG", "DETAIL", "NORMAL", "SIMPLE"};

	/* 初始化日志文件 */

	WriteLog::WriteLog()

	{

	}

	WriteLog::~WriteLog()

	{

	}

	void WriteLog::write_(const char *file, const char* func, \

			const int line, int flag , const char* fmt, ... )

	{

		char buf[BUFSIZ];

		va_list ap;



		if (LEVEL < 0 || LEVEL > 4 || flag < LEVEL || !fmt)

			return;	



		bzero(buf, BUFSIZ);

		va_start(ap , fmt);

		vsnprintf(buf, BUFSIZ, fmt, ap);



		if (logFile.empty())

		{

			fprintf(stderr, 

				"%s:pthread=%lu:%s [%s:%s:%s:%d]\n",

				mytime.getdatetime(), gettid(), buf, level[flag], file, func, line);

		}

		else 

		{

			if (NULL == log_file || 

				access(logFile.c_str(), F_OK) < 0 || 

				fprintf(log_file, 

					"%s:pthread=%lu:%s [%s:%s:%s:%d]", 

					mytime.getdatetime(), gettid(), buf, level[flag], file, func, line) < 0)

			{

				fclose(log_file);



				if (NULL == (log_file = fopen(logFile.c_str(), "a+")))

				{

					fprintf(stderr, 

						"%s:pthread=%lu:%s [%s:%s:%s:%d]",

						mytime.getdatetime(), gettid(), buf, level[flag], file, func, line);

					fprintf(stderr, "open=%s:msg=%m", logFile.c_str());

				}

				else

				{

					setlinebuf(log_file);

					fprintf(log_file, 

						"%s:pthread=%lu:%s [%s:%s:%s:%d]", 

						mytime.getdatetime(), gettid(), buf, level[flag], file, func, line);

				}

			}

		}



		va_end(ap);

	}

};



PWRD::WriteLog logs;

