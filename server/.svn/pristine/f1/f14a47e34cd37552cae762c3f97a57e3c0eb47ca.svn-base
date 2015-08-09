#ifndef __FILESERVICE_HPP
#define __FILESERVICE_HPP

#include <Conf.hpp>

#include <iostream>

#include <sys/stat.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <Daemon.hpp>

#include <boost/lexical_cast.hpp>

#include <boost/tokenizer.hpp>

#include <boost/thread/thread.hpp>

using namespace std;
using namespace PWRD;

namespace PWRD{

	namespace Persist{

		typedef enum {

			FLAGS = O_WRONLY|O_CREAT|O_APPEND|O_NONBLOCK|O_LARGEFILE,
			MODE  = S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH

		}OPTION;

		typedef map<int, int> FileMap;

		typedef map<int, string> NameMap;

		typedef vector<string> Vector;

		class FileService{

			public:

				static FileService* Instance(string& _file);

				static int Load();

				static int Find(int _type);

				static int Makedir(string& _day);

				static int Write(int _fd, const char* _buf, int len);

				virtual ~FileService(){ fini(); };

			protected:

				virtual int init();

				virtual int fini();


			private:

				FileService(){ init(); };

				static int Cont();


				static bool debug_;

				static string day_;

				static string file_;

				static string root_;

				static int debugfd_;

				static FileMap fmap_; //type <===> num

				static FileMap dmap_; //num  <===> fd

				static NameMap nmap_; //num  <===> file

				static FileService* instance_;



		};

	}

}

#endif
