#ifndef __THREADWRAPPER_HPP
#define __THREADWRAPPER_HPP

#include <PipeHandler.hpp>

#include <Pipe.hpp>

#include <SyncQueue.hpp>

#include <ServerImpl.hpp>

#include <FileService.hpp>

using namespace PWRD;

using namespace PWRD::Event;

using namespace PWRD::Logic;

using namespace PWRD::Network;

using namespace PWRD::ActiveObject;

namespace PWRD{
	
	static void* StartReactor(void* _args){

		Reactor* _reactor = (Reactor*)_args;

		_reactor->Run();

		return NULL;

	}

	static void* StartFileService(void* _args){
		
		FileService* _fs = (FileService*)_args;

		_fs->Run();

		return NULL;

	}

}//PWRD

#endif
