#include <Registry.hpp>

using namespace PWRD::Mem;

string roleid = "Litanhua";

string GetRoleID(int _index){

	stringstream ss;

	ss << roleid;
	ss << _index;

	return ss.str();


}


int GetRand(int _index){

	return _index + rand()%4;

}

HANDLER h = NULL;

class MyHandler: public EventHandler{

	public:

		virtual Handle GetHandle() const{ return 1; }

};

HANDLER GetHandler(){

	HANDLER handler = new MyHandler();

	return handler;

}

int main(int argc, char *argv[]){

	//Daemon(argv[0]);

	Registry::Instance();

	srand(time(NULL));

	for(int i = 0; i < 15; i++){

		h = GetHandler();

		Gamer_t gamer(GetRoleID(i), h, GetRand(i), GetRand(i));

		Registry::Registe(gamer);

		//Note("=================================================================");

	} //for

	for(int i = 0; i < 15; i++){

		boost::shared_ptr<Gamer_t> gamer = Registry::Get(GetRoleID(i));

		/*
		cout << "RoleID: " << gamer->roleid
			<< ", Handler: " << gamer->handler
			<< ", PKLevel: " << gamer->pklevel
			<< ", RankLevel: " << gamer->ranklevel
			<< endl;
			*/
	}

	for(int i = 15; i < 20; i++){

		h = GetHandler();

		Gamer_t gamer(GetRoleID(i), h, 10, 10);

		Registry::Registe(gamer);

	}

	Note("====================%d===================", Registry::Size());

	//Registry::Remove(h);

	//Registry::Remove(h);

	Note("====================%d===================", Registry::Size());

	string roleid("Litanhua0");

	boost::shared_ptr<Gamer_t> gamer = Registry::Get(roleid);

	Note("Note Gamer: roleid=%s, handler=%p, pklevel=%ld, ranklevel=%ld", 
			gamer->roleid.c_str(), gamer->handler, gamer->pklevel, gamer->ranklevel);

	boost::shared_ptr<Gamer_t> tt = Registry::Get(10, false);

	if(NULL != tt.get()){

		//Note("Note Gamer: roleid=%s, handler=%p, pklevel=%ld", tt->roleid.c_str(), tt->handler, tt->pklevel);

	}

	boost::shared_ptr<Gamer_t> rr = Registry::Get(10, true);

	if(NULL != rr.get()){

		//Note("Note Gamer: roleid=%s, handler=%p, ranklevel=%ld", rr->roleid.c_str(), rr->handler, rr->ranklevel);
	}

	Note("-----------------BEGIN------------------");

	int step = 0;

	while(step < 6){

		boost::shared_ptr<Gamer_t> aa  = Registry::Get(10, false);

		if(NULL != aa.get()){

			Note("Note Gamer: roleid=%s, handler=%p, pklevel=%ld", 
					aa->roleid.c_str(), aa->handler, aa->pklevel);

			if(!Registry::UpdateStat(aa->roleid, BUSY)){
				
				Note("|||||||||||||||||||||||||||||||||||||||||||||||");

			}
		}
		else{

			Note("---------------Not Enough-----------------");

			break;

		}

		step++;

	}

	roleid = Registry::Get(h);

	Note("RoleID:  %s", roleid.c_str());

	return 1;

}
