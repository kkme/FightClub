#ifndef __FILESINK_HPP
#define __FILESINK_HPP

#include <Global.hpp>

#include <Daemon.hpp>

#include <StatDef.hpp>

#include <Registry.hpp>

#include <Monitor.pb.h>

#include <ActiveQueue.hpp>

using namespace PWRD;

using namespace PWRD::Event;

using namespace PWRD::ActiveObject;

namespace PWRD{

	namespace Logic{

		typedef enum {

			FLAGS = O_WRONLY|O_CREAT|O_TRUNC|O_APPEND|O_LARGEFILE,

			MODE  = S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IROTH,

			MODEX = S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH

		}OPTION;



		class FileSink{

			public:

				FileSink(){ init(); }

				FileSink(int _outfd):outfd_(_outfd){ init(); }

				virtual ~FileSink(){ fini(); }

				bool Process(FileBlock*);

				virtual bool Sync(const string& _type, const string& _path, const string& _content);

			protected:


				/*
				   virtual bool Prepare(const string&);

				   virtual bool Create(const string&, const string&);

				   virtual bool Append(const string&);

				   virtual bool Checksum(const string&);

				   virtual bool Checkoff(const string&);
				   */

				virtual int init();

				virtual int fini();


			private:

				int outfd_;


		};

	}//Logic

}//PWRD

#endif
