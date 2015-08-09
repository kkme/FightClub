#include <Request.hpp>
#include <Scheduler.hpp>
#include <Memorypool.hpp>
#include <ActiveQueue.hpp>
#include <ActiveLogRecord.hpp>

using namespace PWRD;
using namespace PWRD::Persist;
using namespace PWRD::ActiveObject;

int main(int argc, char* argv[]){

	if(argc != 2){

		cout<< "Usage: " << argv[0] << "  <conf>" << endl;

		return -1;

	}

	string conf(argv[1]);

	if(NULL == FileService::Instance(conf)){

		cout << "FileService::Instance faild" << endl;

		return -1;
	}

	FileService::Load();

	//MemoryPool
	Memorypool::Instance();

	//Threadpool
	Threadpool::Instance();

	//ActiveQueue
	ActiveQueue<Request> *activeq = new ActiveQueue<Request>();

	if(NULL == activeq){

		cout << "New ActiveQueue failed" << endl;

		return -1;

	}


	//Logrecord
	LogRecord log;

	log.set_type(17);

	log.set_server("manager");

	log.set_process("linkd");

	log.set_message("Hello world\n");

	int len = log.ByteSize();

	char *buf = new char[len];

	*buf = 0;

	log.SerializeToArray(buf, len);

	Trace("TRACE SerializeToArray: buf=%p, len=%d", buf, len);

	// Scheduler
	
	Scheduler *sch = new Scheduler(activeq);


	if(NULL == sch){
		
		cout << "New Scheduler failed" << endl;

		return -1;

	}

	//start
	Threadpool::Instance().schedule(boost::bind(&Scheduler::Dispatch, sch));
	

	int i = 0;

	while( i < 10){
		
		Request *req = Memorypool::Instance().construct(buf, len);

		activeq->Enqueue(req);

		sleep(1);

		i++;
	}

	Threadpool::Instance().wait();
	return -1;
}
