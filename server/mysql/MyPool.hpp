#ifndef __MYPOOL_HPP
#define __MYPOOL_HPP

#include <Conf.hpp>

#include <MySQL.hpp>

#include <Mutex.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

#include <StringTool.hpp>

using namespace PWRD;

using namespace PWRD::DB;

using namespace PWRD::IPC;

using namespace PWRD::Utils;

#define TRYTIME  10

namespace PWRD{

	namespace DB{

		typedef queue<MySQL*> ConnectionPool;
	
		class MyPool{
		
			public:

				virtual ~MyPool(){ fini(); }
			
				static MyPool* Instance();

				static MySQL* Get();

				static void Release(MySQL* _mysql);

			protected:

				MyPool(){ init(); }

				static int init();

				static int fini();

			private:

				static Mutex lock_;

				static int maxsize_;

				static int currsize_;

				static MySQL* mysql_; //for full-busy time

				static MyPool* instance_;

				static ConnectionPool* pool_;

		};

	}//DB

}//PWRD

#endif
