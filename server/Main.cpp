#include <ThreadWrapper.hpp>

using namespace PWRD;

int main(int argc, char* argv[]){

	if(argc != 2){

		cout<< "Usage: " << argv[0] << "  <conf>" << endl;

		return -1;

	}

	string file(argv[1]);

	//Reactor
	Reactor* reactor = ReactorService::Instance();

	assert(reactor != NULL);

	//Registry
	Registry::Instance();

	//ActiveQueue For Result
	ActiveQueue<FileBlock*>* activeq = new ActiveQueue<FileBlock*>();

	assert(activeq != NULL);

	//Pipe
	Pipe *pipe = new Pipe();

	//FileService
	FileService* fs = new FileService(pipe->outfd(), activeq);

	assert(NULL != fs);

	//SyncQueue
	SyncQueue<Result*>* syncq = new SyncQueue<Result*>();

	assert(NULL != syncq);

	//PipeHandler
	PipeHandler* handler = new PipeHandler(pipe->infd());

	handler->Open(DEFAULTTIMER);

	//ServerImpl
	ServerImpl *si = new ServerImpl(file, syncq, activeq);

	if(NULL == si){

		cout << "New ServerImpl failed" << endl;

		return -1;

	}

	si->Open();

	pthread_t rt, fst;

	pthread_create(&rt, NULL, &StartReactor, (void*)reactor);

	pthread_create(&fst, NULL, &StartFileService, (void*)fs);

	pthread_join(rt, NULL);

	pthread_join(fst, NULL);

	return 1;

}
