#include <TestCase.hpp>

namespace PWRD{

	Head TestCase::head_;

	string TestCase::rolename_ = "";

	string TestCase::roleid_ = "";

	string TestCase::froleid_ = "";

	string TestCase::uuid_ = "";

	char TestCase::buf_[BUFSIZ];

	TestCase* TestCase::instance_ = NULL;

	/*=====================================================================
	 *@public	
	 ====================================================================*/
	int TestCase::init(){

		Conf* conf = Conf::GetInstance();

		rolename_ = conf->find("TestCase", "rolename");

		roleid_ = conf->find("TestCase", "roleid");

		froleid_ = conf->find("TestCase", "froleid");

		uuid_ = conf->find("TestCase", "uuid");

		Note("Load Config: rolename=%s, uuid=%s", rolename_.c_str(), uuid_.c_str());

		return 1;

	}

	int TestCase::fini(){

		return 1;

	}

	void TestCase::T_Registe(Client* _handler){

		head_.type =  REGISTRY;

		head_.version = 0;

		C2S_Registe* item = new C2S_Registe();	

		assert(NULL != item);

		item->set_rolename(rolename_);

		item->set_uuid(uuid_);

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		if(!item->ParseFromArray(buf_, head_.length)){

			Error("Fuck this world!");


		}

		_handler->Send(head_, buf_, head_.length);

	}

	void TestCase::T_Login(Client* _handler){

		head_.type =  LOGIN;

		head_.version = 0;

		C2S_Login* item = new C2S_Login();	

		assert(NULL != item);

		item->set_roleid(roleid_);

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		if(!item->ParseFromArray(buf_, head_.length)){

			Error("Fuck this world!");


		}

		_handler->Send(head_, buf_, head_.length);

	} //T_Login

	void TestCase::T_Request(Client* _handler){

		head_.type =  FIGHTREQUEST;

		head_.version = 0;

		C2S_FightRequest* item = new C2S_FightRequest();	

		assert(NULL != item);

		item->set_roleid(roleid_);

		item->set_froleid(froleid_);

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		if(!item->ParseFromArray(buf_, head_.length)){

			Error("Fuck this world!");


		}

		_handler->Send(head_, buf_, head_.length);

	} //T_Request

	void TestCase::T_Fight(Client* _handler){

		head_.type =  FIGHTING;

		head_.version = 0;

		C2S_Fight* item = new C2S_Fight();	

		assert(NULL != item);

		item->set_roleid(roleid_);

		item->set_froleid(froleid_);

		Beat* beat = item->mutable_beat();

		assert(NULL != beat);

		beat->set_hp(10);

		beat->set_animation("animation_001#");

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		if(!item->ParseFromArray(buf_, head_.length)){

			Error("Fuck this world!");


		}

		_handler->Send(head_, buf_, head_.length);

	} //T_Request

	void TestCase::T_HardBeat(Client* _handler){

		head_.type =  HARDBEAT;

		head_.version = 0;

		C2S_HardBeat* item = new C2S_HardBeat();	

		assert(NULL != item);

		item->set_roleid(roleid_);

		item->set_froleid(froleid_);

		Beat* beat = item->mutable_beat();

		assert(NULL != beat);

		beat->set_hp(10);

		beat->set_animation("animation_001#");

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		if(!item->ParseFromArray(buf_, head_.length)){

			Error("Fuck this world!");


		}

		_handler->Send(head_, buf_, head_.length);

	} //T_Request


	void TestCase::T_Item(Client* _handler){

		head_.type =  ITEM;

		head_.version = 0;

		C2S_Item* item = new C2S_Item();	

		assert(NULL != item);

		item->set_roleid(roleid_);

		item->set_froleid(froleid_);

		item->set_itemid("item_001#");

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		if(!item->ParseFromArray(buf_, head_.length)){

			Error("Fuck this world!");


		}

		_handler->Send(head_, buf_, head_.length);

	} //T_Request

	void TestCase::T_QTE(Client* _handler){

		head_.type =  QTE;

		head_.version = 0;

		C2S_QTE* item = new C2S_QTE();	

		assert(NULL != item);

		item->set_roleid(roleid_);

		item->set_froleid(froleid_);

		int index = 3;

		//for(int index = 0; index < 5; index++){

		QTE_Beat* beat = item->add_qte();

		beat->set_hp(index);

		beat->set_during(index);

		//}

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		if(!item->ParseFromArray(buf_, head_.length)){

			Error("Fuck this world!");


		}

		_handler->Send(head_, buf_, head_.length);

	} //T_Request

	void TestCase::T_PKList(Client* _handler){

		head_.type =  PKLIST;

		head_.version = 0;

		C2S_PKList* item = new C2S_PKList();	

		assert(NULL != item);

		item->set_roleid(roleid_);

		item->set_request("5:6;4:6;");

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		if(!item->ParseFromArray(buf_, head_.length)){

			Error("Fuck this world!");


		}

		_handler->Send(head_, buf_, head_.length);

	} //T_PKList

	void TestCase::T_Property(Client* _handler){

		head_.type =  PROPERTY;

		head_.version = 0;

		C2S_Property* item = new C2S_Property();	

		assert(NULL != item);

		item->set_roleid(roleid_);

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		_handler->Send(head_, buf_, head_.length);

	} //Property

	void TestCase::T_Friend(Client* _handler){

		head_.type =  FRIENDLIST;

		head_.version = 0;

		C2S_Friend* item = new C2S_Friend();	

		assert(NULL != item);

		item->set_roleid(roleid_);

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		_handler->Send(head_, buf_, head_.length);

	} //Friend

	void TestCase::T_FriendNum(Client* _handler){

		head_.type =  FRIENDLIST;

		head_.version = 0;

		C2S_Friend* item = new C2S_Friend();	

		assert(NULL != item);

		item->set_roleid(roleid_);

		item->set_num(2);

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		_handler->Send(head_, buf_, head_.length);

	} //Friend

	void TestCase::T_FriendIndex(Client* _handler){

		head_.type =  FRIENDLIST;

		head_.version = 0;

		C2S_Friend* item = new C2S_Friend();	

		assert(NULL != item);

		item->set_roleid(roleid_);

		item->set_index(2);

		item->set_length(3);

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		_handler->Send(head_, buf_, head_.length);

	} //Friend

	void TestCase::T_Bill(Client* _handler){

		head_.type =  BILL;

		head_.version = 0;

		C2S_Bill* item = new C2S_Bill();	

		assert(NULL != item);

		item->set_roleid(roleid_);

		item->set_itemid("shoes_0000");

		item->set_num(3);

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		_handler->Send(head_, buf_, head_.length);

	} //Bill

	void TestCase::T_Stat(Client* _handler){

		head_.type =  PKSTAT;

		head_.version = 0;

		C2S_Bill* item = new C2S_Bill();	

		assert(NULL != item);

		item->set_roleid(roleid_);

		head_.length = item->ByteSize();

		item->SerializeToArray(buf_, head_.length);

		_handler->Send(head_, buf_, head_.length);

	} //Bill

	/*
	   void TestCase::T_PKList(Client* _handler){

	   head_.type =  PKLIST;

	   head_.version = 0;

	   RegistryItem* item = new RegistryItem();	

	   assert(NULL != item);

	   item->set_uid(fuid_);

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

	   item->set_uid(uid_);

	   item->set_fuid(fuid_);

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

	   item->set_uid(uid_);

	   item->set_fuid(fuid_);

	   item->set_experience(1);

	   item->set_bonus(90);

	   item->set_win(false);

	   head_.length = item->ByteSize();

item->SerializeToArray(buf_, head_.length);

_handler->Send(head_, buf_, head_.length);


}


void TestCase::T_FightResponse(Client* _handler){

	head_.type =  FIGHTRESPONSE;

	head_.version = 0;

	Response* item = new Response();

	assert(NULL != item);

	item->set_uid(uid_);

	item->set_fuid(fuid_);

	item->set_ido(true);

	head_.length = item->ByteSize();

	item->SerializeToArray(buf_, head_.length);

	_handler->Send(head_, buf_, head_.length);

}
*/


}
