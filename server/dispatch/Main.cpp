#include <DispatchCenter.hpp>

using namespace PWRD;

using namespace PWRD::FC;


int main(void){

	DispatchCenter::Instance();

	ActiveQueueSigalton::Instance();

	DispatchCenter::Run();


	return 1;

}

