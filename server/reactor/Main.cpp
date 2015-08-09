#include "Reactor.hpp"
#include "PipeHandler.hpp"
#include <boost/thread/thread.hpp>
#include <Global.hpp>
#include <InnerChange.hpp>
using namespace boost;
using namespace PWRD::InnerProcess;
using namespace PWRD::IO;
using namespace PWRD::Event;

#define REACTORSIZE 1024

int pipe_[2];

void printout(){
	while(1){
		const char *content = "hello world!";
		logs.write_log(NORMAL, "%s", content);
		write(pipe_[1], content, strlen(content));
		sleep(1);
	}
}

int main(void){
	pipe(pipe_);

	Pipe pipeio(pipe_[0]);

	InnerChange inner;

	EventHandler* eventHandler = new PipeHandler(pipeio, inner);

	Reactor * reactor = new Reactor(REACTORSIZE);

	//ReactorMask mask = EventHandler::READ_MASK | EventHandler::WRITE_MASK ;
	ReactorMask mask = EventHandler::READ_MASK;
	reactor->Register(eventHandler, mask);

	boost::thread *readt = new boost::thread(boost::bind(&printout));
	boost::thread *writet = new boost::thread(boost::bind(&Reactor::Run, reactor));

	readt->join();
	writet->join();

	return 1;
}
