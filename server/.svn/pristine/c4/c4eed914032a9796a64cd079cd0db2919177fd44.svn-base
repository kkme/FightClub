#include <Global.hpp>
#include <SyncQueue.hpp>

using namespace PWRD;
using namespace PWRD::ActiveObject;

int main(void){

	SyncQueue<string*>* q = new SyncQueue<string*>();

	string* p = new string("hello world");

	q->Enqueue(p);

	if(q->Size() > 0){

		string* s = q->Dequeue();

		cout << *s << endl;
	}

	cout << "Size: " << q->Size() << endl;

	return 1;

}
