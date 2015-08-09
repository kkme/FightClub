#include <Task.hpp>
#include <Registry.hpp>
#include <TaskImpl.hpp>
#include <ServerImpl.hpp>
#include <XMLBuilder.hpp>
#include <ReceiverImpl.hpp>
#include <EventPipeHandler.hpp>
#include <AsyncTimer.hpp>

using namespace PWRD;
using namespace PWRD::XML;
using namespace PWRD::Event;
using namespace PWRD::Utils;

int main(int argc, char *argv[]){

	if(3 != argc){

		cout << "Usage: " << argv[0] << " <xml> <conf>" << endl;

		return -1;

	}

	//XML Builder
	string xml(argv[1]);

	string file(argv[2]);

	XMLBuilder *builder = new XMLBuilder(xml);

	boost::asio::io_service io_service;

	AsyncTimer* timer = new AsyncTimer(file, *builder, io_service);

	//Server

	boost::thread* timert = new boost::thread(boost::bind(&AsyncTimer::Run, timer));

	timert->join();

	return 1;

}
