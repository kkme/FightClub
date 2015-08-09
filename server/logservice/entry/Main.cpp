#include <ServerImpl.hpp>

using namespace PWRD;

using namespace PWRD::Network;

int main(int argc, char *argv[]){

	if(argc != 2){

		cout<< "Usage: " << argv[0] << "  <conf>" << endl;

		return -1;

	}

	Reactor* reactor = ReactorService::Instance();

	if(NULL == reactor){

		cout << "New ServerImpl failed" << endl;

		return -1;

	}

	string file(argv[1]);

	Conf::GetInstance(argv[1]);

	//FileService
	if(NULL == FileService::Instance(file)){

		cout << "FileService::Instance faild" << endl;

		return -1;
	}

	FileService::Load();

	//ActiveQueue
	ActiveQueue<Request*> *activeq = new ActiveQueue<Request*>();

	if(NULL == activeq){

		cout << "New ActiveQueue failed" << endl;

		return -1;

	}


	// Scheduler
	Scheduler *sch = new Scheduler(activeq);

	if(NULL == sch){
		
		cout << "New Scheduler failed" << endl;

		return -1;

	}

	//ServerImpl
	ServerImpl *si = new ServerImpl(file, activeq);

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

	Signal();
	Daemon(argv[0]);

	//Memorypool
	Memorypool::Instance();

	//Stringpool
	Stringpool::Instance();

	//Threadpool
	//Threadpool::Instance();

	//start scheduler
	//Threadpool::Instance().schedule(boost::bind(&Scheduler::Dispatch, sch));
	boost::thread *scheduler_thread = new boost::thread(boost::bind(&Scheduler::Dispatch, sch));

	//start reactor 
	//Threadpool::Instance().schedule(boost::bind(&Reactor::Run, reactor));
	boost::thread *reactor_thread = new boost::thread(boost::bind(&Reactor::Run, reactor));

	//Threadpool::Instance().wait();

	scheduler_thread->join();

	reactor_thread->join();

	delete si;

	delete activeq;

	delete sch;
}
