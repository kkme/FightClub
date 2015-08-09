#include <TestCase.hpp>

#include <ClientImpl.hpp>

#include <PrintCenter.hpp>

#include <ActiveQueueSigalton.hpp>

using namespace PWRD;

using namespace PWRD::Network;

void* StartReactor(void* arg){

	Reactor* reactor = (Reactor*)arg;

	assert(reactor != NULL);

	reactor->Run();

	return NULL;

}

void* Print(void* arg){

	PrintCenter* center = (PrintCenter*)arg;

	assert(center != NULL);

	center->Run();

	return NULL;

}

void* Test(void* arg){

	Client* client = (Client*)arg;

	assert(client != NULL);

	TestCase::T_Version(client);

	sleep(1);

	TestCase::T_Property(client);

	pause();

	sleep(1);

	TestCase::T_PKList(client);

	sleep(1);

	TestCase::T_FightRequest(client);

	sleep(1);

	TestCase::T_FightResponse(client);

	sleep(1);


	TestCase::T_Fight(client);

	sleep(1);

	TestCase::T_FightResult(client);



}


int main(int argc, char *argv[]){

	if(argc != 2){

		cout<< "Usage: " << argv[0] << "  <conf>" << endl;

		return -1;

	}

	string file(argv[1]);

	ActiveQueueSigalton::Instance();

	Reactor* reactor = ReactorService::Instance();

	assert(reactor != NULL);

	ClientImpl* ci = new ClientImpl(file);

	assert(NULL != ci);

	ci->Open();

	Client* client = ci->client();

	assert(NULL != client);

	//Daemon(argv[0]);

	//timer queue
	TimerQueue* timerq = TimerQueue::Instance();

	if(NULL == timerq){

		cout << "New TimerQueue failed" << endl;

		return -1;

	}

	//start reactor 
	pthread_t reactor_thread, center_thread, test_thread;

	pthread_create(&reactor_thread, NULL, &StartReactor, (void*) reactor);

	pthread_create(&center_thread, NULL, &Print, (void*) reactor);

	pthread_create(&center_thread, NULL, &Test, (void*) client);

	pthread_join(reactor_thread, NULL);

	pthread_join(center_thread, NULL);

	pthread_join(test_thread, NULL);

	//start reactor 

	return 1;

}
