#include <TestCase.hpp>

namespace PWRD{


	Head TestCase::head_;

	char TestCase::buf_[BUFSIZ];

	void TestCase::T_Version(Client* _handler){
	
		head_.type =  REGISTRY;

		head_.version = 0;

		RegistryItem* item = new RegistryItem();	

		assert(NULL != item);

		item->set_uid("Litanhua");

		item->set_version("0.1.0");

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		if(!item->ParseFromArray(buf_, head_.length)){
			
			Error("Fuck this world!");
		

		}

		_handler->Send(head_, buf_, head_.length);

	}

	void TestCase::T_Property(Client* _handler){
	
		head_.type =  PROPERTY;

		head_.version = 0;

		RegistryItem* item = new RegistryItem();	

		assert(NULL != item);

		item->set_uid("Litanhua");

		item->set_version("0.1.0");

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		_handler->Send(head_, buf_, head_.length);

	}

	void TestCase::T_PKList(Client* _handler){
	
		head_.type =  PKLIST;

		head_.version = 0;

		RegistryItem* item = new RegistryItem();	

		assert(NULL != item);

		item->set_uid("ZhaoZhiyang");

		item->set_version("0.1.0");

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		_handler->Send(head_, buf_, head_.length);

	}

	void TestCase::T_Fight(Client* _handler){
	
		head_.type =  FIGHTING;

		head_.version = 0;

		Fight* item = new Fight();	

		assert(NULL != item);

		item->set_fuid("ZhaoZhiyang");

		item->set_uid("Litanhua");

		item->set_boxing(1);

		item->set_hp(90);

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		_handler->Send(head_, buf_, head_.length);

	}

	void TestCase::T_FightResult(Client* _handler){
	
		head_.type =  FIGHTRESULT;

		head_.version = 0;

		FightResult* item = new FightResult();	

		assert(NULL != item);

		item->set_fuid("ZhaoZhiyang");

		item->set_uid("Litanhua");

		item->set_experience(1);

		item->set_bonus(90);

		item->set_win(false);

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		_handler->Send(head_, buf_, head_.length);


	}

	void TestCase::T_FightRequest(Client* _handler){
	
		head_.type =  FIGHTREQUEST;

		head_.version = 0;

		Request* item = new Request();	

		assert(NULL != item);

		item->set_fuid("ZhaoZhiyang");

		item->set_uid("Litanhua");

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		_handler->Send(head_, buf_, head_.length);

	}

	void TestCase::T_FightResponse(Client* _handler){

		head_.type =  FIGHTRESPONSE;

		head_.version = 0;
	
		Response* item = new Response();

		assert(NULL != item);

		item->set_fuid("ZhaoZhiyang");

		item->set_uid("Litanhua");

		item->set_ido(true);

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		_handler->Send(head_, buf_, head_.length);

	}


}
