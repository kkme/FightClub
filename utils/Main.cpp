#include <AsyncTimer.hpp>
using namespace PWRD::Utils;

int main(int argc, char* argv[]){


	if(3 != argc){

		cout << "Usage: " << argv[0] << " <conf> <xml>" << endl;

		return -1;

	}

	string file(argv[1]);

	string xml(argv[2]);

	XMLBuilder *builder  = new XMLBuilder(xml);

	boost::asio::io_service io_service;

	AsyncTimer* timer = new AsyncTimer(file, *builder, io_service);


	//

	boost::thread* thread = new boost::thread(boost::bind(&AsyncTimer::Run, timer));

	thread->join();

	delete builder;

	return 1;


}


