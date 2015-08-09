
#include <ExchangeCenter.hpp>

using namespace PWRD::FC;

int main(int argc, char* argv[])
{
	//Daemon(argv[0]);

	try
	{
		ExchangeCenter::Instance();

		//for(int i=1; i < argc; i++){

			string file(argv[1]);

			ExchangeCenter::Load(file);

		//}

		ExchangeCenter::Print();

		cout << "Size: " << ExchangeCenter::Size() << endl;

	}
	catch(std::exception& ex)
	{
		std::cout << "ERR:" << ex.what() << endl;
	}

	return 0;
}
