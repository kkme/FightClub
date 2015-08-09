#include <DBService.hpp>
#include <Service.hpp>

using namespace PWRD::MoM;

int main(int argc, char* argv[]){


	if(argc != 2){

		Error("Usage: %s <conf>", argv[0]);

		return -1;

	}


	DBService* db = new DBService("DBService");

	db->Start();

	pause();


	return -1;


}
