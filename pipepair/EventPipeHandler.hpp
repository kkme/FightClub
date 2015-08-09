#ifndef __EVENTPIPEHANDLER_HPP
#define __EVENTPIPEHANDLER_HPP

#include <Pipe.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

#include <PidSet.hpp>

#include <Registry.hpp>

#include <Monitor.pb.h>

#include <ActiveQueue.hpp>

#include <EventHandler.hpp>

#include <ReactorService.hpp>

#include <TimerQueue.hpp>

#include <boost/tokenizer.hpp>

#include <boost/tuple/tuple.hpp>

#define ARGC 100

#define ARGV 1024

using namespace boost;

using namespace PWRD;

using namespace PWRD::IPC;

using namespace PWRD::ActiveObject;


namespace PWRD{

	namespace Event{

		class EventPipeHandler: public EventHandler{

			public:

				EventPipeHandler(int _type, const string _path, const string& _shell, int _timeout, const string& _server):type_(_type), pid_(-1), timeout_(_timeout), path_(_path), shell_(_shell), server_(_server){ init(); };

				virtual ~EventPipeHandler(){ fini(); };

				virtual int Open();

				virtual int Receive();

				virtual int Send();

				virtual int Close();

				virtual int Execute();

				virtual int Timeout(bool& _flag);

				virtual void Start();

				virtual Handle GetHandle() const{ return pipe_->infd(); }


			protected:

				int init();

				int fini();


			private:

				int type_;

				pid_t pid_;

				Pipe* pipe_;

				int timeout_;

				string path_;

				string shell_;

				string strbuf_;

				string server_;

				char buf_[BUFSIZ];

				//function members
				int Return();

				void getCMD(char **);
				//boost::asio::deadline_timer *deadline_;

		};

	}//Event

}//PWRD

#endif
