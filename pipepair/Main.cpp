#include <PipeHandler.hpp>
#include <StatDef.hpp>
#include <ActiveQueue.hpp>
#include <Registry.hpp>
#include <FileSink.hpp>
#include <Monitor.pb.h>
#include <FileService.hpp>
#include <ReactorService.hpp>
#include <EventPipeHandler.hpp>

using namespace PWRD;
using namespace PWRD::Event;
using namespace PWRD::Logic;
using namespace PWRD::ActiveObject;

ActiveQueue<FileBlock*>* activeq;

void* StartReactor(void* arg){

	Reactor* reactor = (Reactor*)arg;

	assert(NULL != reactor);

	reactor->Run();

	return NULL;

}

void* StartFileService(void* arg){

	FileService* fs = (FileService*)arg;

	assert(NULL != fs);

	fs->Run();

	return NULL;
}

/*
void* Write(void* arg){
	
	int* wfd = (int*)arg;

	assert(NULL != wfd);

	int bytes = 0;

	while(true){
		
		sleep(1);

		bytes = write(*wfd, &stat.len, sizeof(int));

		bytes += write(*wfd, str.c_str(), str.size());

		//Note("Write StatInfo: fd=%d, len=%d, bytes=%d", *wfd, stat.len, bytes);
	}

	return NULL;

}
*/

int main(int argc, char*  argv[]){

	//Reactor
	Reactor* reactor = ReactorService::Instance();
	
	if(NULL == reactor){

		Error("New reactor failed!");

		return -1;
	}

	//Pipe
	Pipe *pipe = new Pipe();

	assert(NULL != pipe);

	//PipeHandler
	PipeHandler* handler = new PipeHandler(pipe->infd());

	assert(NULL != handler);

	handler->Open(DEFAULTTIMER);

	//Registry
	Registry::Instance();

	//ActiveQ
	activeq = new ActiveQueue<FileBlock*>();

	assert(NULL != activeq);

	//FileBlock
	FileBlock* block = new FileBlock();

	block->set_taskid("12345");
	block->set_type("conf");
	block->set_path("iplist.xml");
	block->set_content("<root> <prog MType=1 timer=\"15\" cmd=\"/home/litanhua/Test/script/check.pl 1 manager 60 0 80 0\"></prog> <prog MType=3 timer=\"15\" cmd=\"/home/litanhua/Test/script/start.pl ager 60 0 80 0\"></prog> </root> ");

	//FileService
	FileService* fs = new FileService(pipe->outfd(), activeq);

	assert(NULL != fs);

	//Threads
	pthread_t rt, ft;

	pthread_create(&rt, NULL, &StartReactor, (void*)reactor);

	//int fd = pipe->outfd();

	//pthread_create(&wt, NULL, &Write, (void*)&fd);

	pthread_create(&ft, NULL, &StartFileService, (void*)fs);

	sleep(1);

	activeq->Enqueue(block);

	pthread_join(rt, NULL);

	pthread_join(ft, NULL);

	//pthread_join(wt, NULL);

	return 1;

}
