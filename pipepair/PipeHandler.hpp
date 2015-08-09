#ifndef __PIPEHANDLER_HPP
#define __PIPEHANDLER_HPP
/*
 * Usage:
 *	   This file is a IPC utility used for transferring data 
 *	   from FileService to XMLHandler, and it can be registered
 *	   to Reactor
 */
#include <XMLBuilder.hpp>

#include <Pipe.hpp>

#include <Daemon.hpp>

#include <Registry.hpp>

#include <XMLBuilder.hpp>
#include <EventHandler.hpp>

#include <Global.hpp>

#include <EventPipeHandler.hpp>

#include <ReactorService.hpp>

using namespace PWRD;

using namespace PWRD::XML;

using namespace PWRD::Event;

namespace PWRD{

	namespace Event{


		class PipeHandler: public EventHandler{

			public:

				PipeHandler(int _infd): infd_(_infd){ init(); }

				virtual ~PipeHandler(){ fini(); }

				virtual int Open(int _intra);

				virtual int Receive();

				virtual int Send();

				virtual int Close();

				virtual int Timeout(bool& _flag);

				virtual Handle GetHandle() const{ return infd_; }

			protected:

				int init();

				int fini();

			private:

				int infd_;

				string path_;

				char buf_[BUFSIZ];

				ConfBuilder* xmlbuilder_;


		};//PipeHandler

	}//Event

}//PWRD

#endif
