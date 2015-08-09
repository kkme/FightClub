#include "File.hpp"
#include "FileService.hpp"
#include "Time.hpp"

#include <iostream>

using namespace std;

using namespace PWRD;
using namespace PWRD::Timekit;
using namespace PWRD::Persist;

string t;

const char *buf = "hello world!\n";

int len = strlen(buf);

void test(int type){

	int fd = FileService::Find(type);

	int res = File::Write(fd, t.c_str(), t.size());
	res += 	File::Write(fd, buf, len);

	cout << "Write " << res << " bytes" << endl;


}

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

	Now now;


	now(t);

	string day = t.substr(0, 10);

	FileService::Makedir(day);


	//test
	{
		
		test(10);
		test(12);
		test(14);
		test(16);
		
		test(11);

		test(13);
		test(17);
		test(28);
		test(32);

		test(21);

		test(22);
		test(31);

		test(15);


		test(19);
	}

	t.assign("2011-12-02 20:18:41");

	day = t.substr(0, 10);

	FileService::Makedir(day);

	//test new day
	{
		test(10);
		test(12);
		test(14);
		test(16);
		
		test(11);

		test(13);
		test(17);
		test(28);
		test(32);

		test(21);

		test(22);
		test(31);

		test(15);


		test(19);
	}

	cout << "Format: 4" << endl;
	cout << "Journey: 1" << endl;
	cout << "Stat 4" << endl;
	cout << "Money 1" << endl;
	cout << "exp 2" << endl;
	cout << "chat 1" << endl;
	cout << "err 1" << endl;

	return -1;

	

}
