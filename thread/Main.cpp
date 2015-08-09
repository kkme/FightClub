#include <Thread.hpp>
using namespace PWRD;

class Print: Thread{

	public:
		Print(const char* _name):Thread(_name), name_(_name){

			cout << name_ << " Start........" << endl;

		}

		virtual ~Print(){

			cout << name_ << " End.........." << endl;
		}

		virtual void Run(){

			while(1){

				sleep(1);

				cout << "Hello world!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

			}

		}

	private:

		string name_;


};

int main(){

	//string tt = "Fuck";

	Print print("Litanhua");

	print.Run();

	pause();

	return 1;

}
