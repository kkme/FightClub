#include <iostream>
#include <CircleBuf.hpp>

#include <string.h>
using namespace PWRD::Utils;
using namespace std;

CircleBuffer buff;

void display () {
	cout << "\nfree " << buff.free() << endl;
	cout << "used " << buff.used() << "\n" << endl;
};

int main () {

	int fd  = open ("/home/huying/auth.log", O_RDONLY);

	cout << "fd " << fd << endl;


	display();

	cout << "add " << buff.add(fd) << endl;


	display();
	lseek(fd, 0, SEEK_SET);

	cout << "add " << buff.add(fd) << endl;

	display();


	char str[409];
	cout << "get " << buff.get(str, 50) << endl;

	display();
	lseek(fd, 70, SEEK_SET);

	cout << "add " << buff.add(fd) << endl;

	display();

	cout << "get " << buff.get(str, 200) << endl;

	display();


	char src[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
	cout << "add " << buff.add (src) << endl;

	display();

	cout << "add " << buff.add (src) << endl;

	display();

	cout << "get " << buff.get(str, 50) << endl;

	display();

	cout << "get " << buff.get(str, 200) << endl;

	display();

	cout << "add " << buff.add (src) << endl;

	display();

	cout << "add " << buff.add (src) << endl;

	display();

	cout << "add " << buff.add (src) << endl;

	display();

	cout << "add " << buff.add (src) << endl;

	display();

	cout << "add " << buff.add (src) << endl;

	display();

	cout << "get " << buff.get(str, 100) << endl;

	display();

	cout << "-- get " << buff.get(str, 400) << endl;

	display();
};
