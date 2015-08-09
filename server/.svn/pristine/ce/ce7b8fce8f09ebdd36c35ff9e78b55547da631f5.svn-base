#include <ServerImpl.hpp>

#include <DispatchCenter.hpp>

#include <ActiveQueueSigalton.hpp>

using namespace PWRD;

using namespace PWRD::Network;

void* StartReactor(void* arg){
	
	Reactor* reactor = (Reactor*)arg;

	assert(reactor != NULL);

	reactor->Run();

	return NULL;

}

void* Dispatch(void* arg){

	DispatchCenter* center = (DispatchCenter*)arg;

	assert(center != NULL);

	center->Run();

	return NULL;

}


int main(int argc, char *argv[]){

	if(argc != 2){

		cout<< "Usage: " << argv[0] << "  <conf>" << endl;

		return -1;

	}

	Daemon(argv[0]);

	Reactor* reactor = ReactorService::Instance();

	if(NULL == reactor){

		Trace("TRACE New ServerImpl failed");

		return -1;

	}

	DispatchCenter* dispatch = DispatchService::Instance();

	if(NULL == dispatch){
	
		cout << "New DispatchCenter failed" << endl;

		return -1;

	}

	string file(argv[1]);

	Conf::GetInstance(argv[1]);

	MyPool::Instance();

	Service::Instance();

	SQLDef::Instance();

	SQLImpl::Instance();

	PlayerCache::Instance();

	ActiveQueueSigalton<Packet*>::Instance();

	//ServerImpl
	ServerImpl *si = new ServerImpl(file);

	if(NULL == si){
		
		cout << "New ServerImpl failed" << endl;

		return -1;

	}

	si->Open();


	//timer queue
	TimerQueue* timerq = TimerQueue::Instance();

	if(NULL == timerq){
		
		cout << "New TimerQueue failed" << endl;

		return -1;

	}

	//Signal();


	//start reactor 
	//pthread_t reactor_thread, center_thread;

	//pthread_create(&reactor_thread, NULL, &StartReactor, (void*) reactor);
	Service::ThreadPool().schedule(boost::bind(&Reactor::Run, reactor));

	Service::ThreadPool().schedule(boost::bind(&DispatchCenter::Run, dispatch));

	Service::Wait();
	//pthread_create(&center_thread, NULL, &Dispatch, (void*) reactor);

	//pthread_join(reactor_thread, NULL);

	//pthread_join(center_thread, NULL);

	//start reactor 
	//Threadpool::Instance().schedule(boost::bind(&Reactor::Run, reactor));

	return 1;

}
