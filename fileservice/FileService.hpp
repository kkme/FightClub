#ifndef __FILESERVICE_H
#define __FILESERVICE_H

#include <FileSink.hpp>
#include <Monitor.pb.h>
#include <ActiveQueue.hpp>

using namespace PWRD;
using namespace PWRD::ActiveObject;

namespace PWRD{

	namespace Logic{

		class FileService{

			public:

				FileService(int _outfd, ActiveQueue<FileBlock*>* _aqueue): outfd_(_outfd), aqueue_(_aqueue){ init(); }

				virtual ~FileService(){ fini(); }

				virtual void Run();

			protected:

				int init();

				int fini();

			private:

				int outfd_;

				FileSink* sink_;

				ActiveQueue<FileBlock*>* aqueue_;

		};

	}

}

#endif
