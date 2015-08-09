#include <ClientImpl.hpp>

#include <RecvService.hpp>

#include <SendService.hpp>

#include <boost/thread.hpp>

using namespace PWRD;

using namespace PWRD::Network;

using namespace PWRD::Workflow;

using namespace PWRD::ActiveMQ;

static void* RunReactor(void* arg){

	assert(NULL != arg);

	Reactor* reactor = (Reactor*)arg;

	reactor->Run();

	return NULL;

}


static void* RunClientImpl(void* arg){

	ClientImpl* ci = (ClientImpl*)arg;

	ci->Run();

	return NULL;

}


int main(int argc, char *argv[]){

	if(argc != 2){

		cout<< "Usage: " << argv[0] << "  <conf>" << endl;

		return -1;

	}

	string conf(argv[1]);

	Conf::GetInstance(argv[1]);

	Address address("127.0.0.1", 11101);

	Reactor* reactor = ReactorService::Instance();

	assert(reactor != NULL);

	//AsyncQueue For Request 
	ActiveQueue<Request*>* aqueue = new ActiveQueue<Request*>();

	assert(NULL != aqueue);

	//ActiveQueue For FeedBack 
	ActiveQueue<FeedBack*>* squeue = new ActiveQueue<FeedBack*>();

	assert(NULL != squeue);

	activemq::library::ActiveMQCPP::initializeLibrary();

	//Recv Service
	RecvService* rs = new RecvService(conf, aqueue);

	assert(NULL != rs);

	rs->Run();


	ClientImpl* ci = new ClientImpl(conf, aqueue, squeue);

	assert(NULL != ci);

	pthread_t react, client;

	pthread_create(&react, NULL, &RunReactor, (void*)reactor);

	pthread_create(&client, NULL, &RunClientImpl, (void*)ci);

	//Send Service
	SendService* ss = new SendService(conf, squeue);

	assert(NULL != ss);

	ss->Run();

	pthread_join(react, NULL);

	//pthread_join(client, NULL);

	activemq::library::ActiveMQCPP::shutdownLibrary();

	return 1;

}

/*
static void* RunSendService(void* arg){

	SendService* send = (SendService*)arg;

	send->Run();

	return NULL;

}

static void* RunRecvService(void* arg){

	RecvService* recv = (RecvService*)arg;

	recv->Run();

	return NULL;

}
*/

//	pthread_create(&send, NULL, &RunSendService, (void*)ss);

//	pthread_create(&recv, NULL, &RunRecvService, (void*)rs);

//	pthread_join(send, NULL);

//	pthread_join(recv, NULL);
