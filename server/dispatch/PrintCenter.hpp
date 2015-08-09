#ifndef __PRINTCENTER_HPP
#define __PRINTCENTER_HPP

#include <Conf.hpp>

#include <Global.hpp>

#include <Daemon.hpp> 

#include <StringTool.hpp>

#include <EventHandler.hpp>

#include <ActiveQueueSigalton.hpp>

using namespace PWRD;

using namespace PWRD::Utils;

using namespace PWRD::Event;

using namespace PWRD::ActiveObject;

//serivces

namespace PWRD{

	namespace FC{

		class PrintCenter{

			public:

				static PrintCenter* Instance(){ 

					if(NULL == instance_){

						instance_ = new PrintCenter();

					}

					return instance_;

				}

				virtual ~PrintCenter(){ fini(); }

				static int Process(EventHandler* _handler, TYPE, const char* _buf, int _len );


				static void Run();

			protected:

				static int init(){

					Conf* conf = Conf::GetInstance();

					string hp = conf->find("Fight", "hp");

					hp_ = StringTool::Str2Int(hp);

					string hhp = conf->find("Fight", "hhp");

					hhp_ = StringTool::Str2Int(hhp);

					animation_ = conf->find("Fight", "animation");

					hanimation_ = conf->find("Fight", "hanimation");


					return 1;
				}

				static int fini(){

					return 1;

				}

			private:

				PrintCenter(){ init(); }

				static PrintCenter* instance_;

				static int hp_;

				static int hhp_;

				static string animation_;

				static string hanimation_;

				static void Print(S2C_Registe* _res){

					Note("S2C_Registe: roleid=%s", _res->roleid().c_str());

				}

				static void Print(S2C_PKStat* _res){

					if(FIGHT == _res->stat()){

						Note("S2C_STAT: roleid=%s: FIGHT", _res->roleid().c_str());

					}
					else if(BUSY == _res->stat()){

						Note("S2C_STAT: roleid=%s: BUSY", _res->roleid().c_str());

					}
					else if(IDLE == _res->stat()){

						Note("S2C_STAT: roleid=%s: IDLE", _res->roleid().c_str());

					}
					else if(BREAK == _res->stat()){

						Note("S2C_STAT: roleid=%s: BREAK", _res->roleid().c_str());

					}	


				}

				static void Print(S2C_Friend* _res){

					Note("S2C_Registe: roleid=%s, friendlist=%s", _res->roleid().c_str(), _res->flist().c_str());

				}

				static void Print(S2C_Gold* _res){

					Note("S2C_Registe: roleid=%s, gold=%d", _res->roleid().c_str(), _res->gold());

				}

				static void Print(S2C_Bill* _res){

					if(1 == _res->status()){

						Note("S2C_Bill: roleid=%s, status=OK", 
								_res->roleid().c_str());

					}	
					else{

						Note("S2C_Bill: roleid=%s, status=FAILED", 
								_res->roleid().c_str());
					}

				}

				static void Print(S2C_Property* _res){

					Note("S2C_Property: roleid=%s, rolename=%s, pklevel=%d, pkexp=%d, ranklevel=%d, rankexp=%d,item=%s, equip=%s, buff=%s", _res->roleid().c_str(), _res->rolename().c_str(), 
							_res->pklevel(), _res->pkexp(), _res->ranklevel(), _res->rankexp(), 
							_res->items().c_str(), _res->equips().c_str(), _res->buffs().c_str());

				}

				static void Print(S2C_PKList* _res){

					for(int index = 0; index < _res->pkpro_size(); index++){

						PKProperty pro = _res->pkpro(index);

						Note("S2C_PKProperty: roleid=%s, rolename=%s, pklevel=%d, pkexp=%d, ranklevel=%d, rankexp=%d, item=%s, equip=%s, buff=%s", 
								pro.roleid().c_str(), pro.rolename().c_str(), 
								pro.pklevel(), pro.pkexp(), pro.ranklevel(), pro.rankexp(), 
								pro.items().c_str(), pro.equips().c_str(), pro.buffs().c_str());

					} //For
				}


				static void Print(S2C_FightResponse* _res){

					if(_res->ido()){

						Note("S2C_FightResponse: roleid=%s, froleid=%s, ok=OK", 
								_res->roleid().c_str(), _res->froleid().c_str());

					}	
					else{

						Note("S2C_FightResponse: roleid=%s, froleid=%s, ok=REFUSED", 
								_res->roleid().c_str(), _res->froleid().c_str());

					}


				}

				static void Print(S2C_Login* _res){

					if(_res->ok()){

						Note("-------------Login OK---------------");
					}
					else{

						Note("-------------Login BAD---------------");
					}


				} //Print Item

				static void Print(S2C_Item* _res){

					Note("S2C_Item: roleid=%s, froleid=%s, itemid=%s", 
							_res->roleid().c_str(), _res->froleid().c_str(), _res->itemid().c_str());

				} //Print Item

				static void Print(S2C_Fight* _res){

					Note("S2C_Fight: roleid=%s, froleid=%s", 
							_res->roleid().c_str(), _res->froleid().c_str());

				} //Print Fight 

				static void Print(S2C_HardBeat* _res){

					Note("S2C_Fight: roleid=%s, froleid=%s", 
							_res->roleid().c_str(), _res->froleid().c_str());

				} //Print Fight 

				static void Print(S2C_QTE* _res){

					stringstream ss;

					for(int index = 0; index < _res->qte_size(); index++){

						ss << " ( ";
						ss << _res->qte(index).hp();
						ss << ":";
						ss << _res->qte(index).during();
						ss << ") ";

					}

					Note("S2C_QTE: roleid=%s, froleid=%s, qte=%s", 
							_res->roleid().c_str(), _res->froleid().c_str(), ss.str().c_str());

				} //Print QTE

				static int WriteRequest(C2S_FightRequest* _req, EventHandler* _handler){



					assert(NULL != _req);

					assert(NULL != _handler);

					S2C_FightResponse* res = new S2C_FightResponse();

					assert(NULL != res);

					res->set_roleid(_req->roleid());

					res->set_froleid(_req->froleid());

					res->set_ido(true);

					//Send
					Head head;

					head.type = FIGHTRESPONSE;

					head.version = 1;

					char* buf = new char[res->ByteSize()];

					*buf = 0;

					head.length = res->ByteSize();

					res->SerializeToArray(buf, head.length);

					_handler->Send(head, buf, head.length);

					delete res;

					return 1;


				}

				static int WriteResponse(C2S_FightRequest* _req, EventHandler* _handler){

					assert(NULL != _req);

					assert(NULL != _handler);

					S2C_FightResponse* res = new S2C_FightResponse();

					assert(NULL != res);

					res->set_roleid(_req->roleid());

					res->set_froleid(_req->froleid());

					res->set_ido(true);

					//Send
					Head head;

					head.type = FIGHTRESPONSE;

					head.version = 1;

					char* buf = new char[res->ByteSize()];

					*buf = 0;

					head.length = res->ByteSize();

					res->SerializeToArray(buf, head.length);

					sleep(8);

					_handler->Send(head, buf, head.length);

					delete res;

					return 1;


				}

				static int WriteFight(S2C_Fight* _req, EventHandler* _handler){

					assert(NULL != _req);

					assert(NULL != _handler);

					C2S_Fight* res = new C2S_Fight();

					assert(NULL != res);

					res->set_roleid(_req->froleid());

					res->set_froleid(_req->roleid());

					//Beat
					Beat* beat = res->mutable_beat();

					assert(NULL != beat);

					beat->set_hp(hp_);

					beat->set_animation(animation_);

					//Send
					Head head;

					head.type = FIGHTING;

					Note(">>>>>>>>>>>>>>>>>>FINGHTING=%d<<<<<<<<<<<<<<<", FIGHTING);

					head.version = 1;

					char* buf = new char[res->ByteSize()];

					*buf = 0;

					head.length = res->ByteSize();

					res->SerializeToArray(buf, head.length);

					//sleep(8);

					_handler->Send(head, buf, head.length);

					delete res;

					return 1;


				} //WriteFight

				static int WriteHardBeat(S2C_HardBeat* _req, EventHandler* _handler){

					assert(NULL != _req);

					assert(NULL != _handler);

					C2S_HardBeat* res = new C2S_HardBeat();

					assert(NULL != res);

					res->set_roleid(_req->froleid());

					res->set_froleid(_req->roleid());

					//Beat
					Beat* beat = res->mutable_beat();

					assert(NULL != beat);

					beat->set_hp(hhp_);

					Note(">>>>>>>>>>>>>>>>>>>>>>>>>hhp=%d<<<<<<<<<<<<<<<<<<<", hhp_);

					beat->set_animation(hanimation_);

					//Send
					Head head;

					head.type = HARDBEAT;

					head.version = 1;

					char* buf = new char[res->ByteSize()];

					*buf = 0;

					head.length = res->ByteSize();

					res->SerializeToArray(buf, head.length);

					_handler->Send(head, buf, head.length);

					delete res;

					return 1;


				} //WriteHardBeat

				static int WriteItem(S2C_Item* _req, EventHandler* _handler){

					assert(NULL != _req);

					assert(NULL != _handler);

					C2S_Item* res = new C2S_Item();

					assert(NULL != res);

					res->set_roleid(_req->froleid());

					res->set_froleid(_req->roleid());

					res->set_itemid("item_01#");

					//Send
					Head head;

					head.type = ITEM;

					head.version = 1;

					char* buf = new char[res->ByteSize()];

					*buf = 0;

					head.length = res->ByteSize();

					res->SerializeToArray(buf, head.length);

					_handler->Send(head, buf, head.length);

					delete res;

					return 1;


				} //WriteItem

				static int WriteQTE(S2C_QTE* _req, EventHandler* _handler){

					assert(NULL != _req);

					assert(NULL != _handler);

					C2S_QTE* res = new C2S_QTE();

					assert(NULL != res);

					res->set_roleid(_req->froleid());

					res->set_froleid(_req->roleid());

					int index = 3;

					QTE_Beat* beat = res->add_qte();

					beat->set_hp(index);

					beat->set_during(index);

					//Send
					Head head;

					head.type = QTE;

					head.version = 1;

					char* buf = new char[res->ByteSize()];

					*buf = 0;

					head.length = res->ByteSize();

					res->SerializeToArray(buf, head.length);

					_handler->Send(head, buf, head.length);

					delete res;

					return 1;


				} //WriteQTE

				static void Print(S2C_FightResult* _res){

					Note("FightResult: roleid=%s, froleid=%s, win=%d, type=%d, equipment=%s", _res->roleid().c_str(), _res->froleid().c_str(), _res->win(), _res->type(), _res->equipment().c_str());

				}
				/*
				   static void Print(Request* _res){

				   Note("Request: uid=%s, fuid=%s", _res->uid().c_str(), _res->fuid().c_str());

				   }

				   static void Print(Response* _res){

				   Note("Response: uid=%s, fuid=%s, ido=%d", _res->uid().c_str(), _res->fuid().c_str(), _res->ido());

				   }

				   static void Print(Fight* _res){

				   Note("Fighting: uid=%s, fuid=%s, boxing=%d, hp=%d", _res->uid().c_str(), _res->fuid().c_str(), _res->boxing(), _res->hp());

				   }


				   static void Print(TimeStamp* _res){

				   Note("TimeStamp: uid=%s, timestamp=%s", _res->uid().c_str(), _res->timestamp().c_str());

				   }

				   static void Print(File* _res){

				   Note("File: uid=%s, match=%d", _res->uid().c_str(), _res->match());

				   }

				   static void Print(Property* _res){

				   Note("Property: uid=%s, name=%s, hp=%d, rank=%d", _res->uid().c_str(), _res->name().c_str(), _res->hp(), _res->rank());

				   }

				   static void Print(PKListBlock* _res){

				   Note("PKListBlock: uid=%s, name=%s, hp=%d, rank=%d", _res->property(0).uid().c_str(), _res->property(0).name().c_str(), _res->property(0).hp(), _res->property(0).rank());

				   }

				   static int WriteResponse(Request* _req, EventHandler* _handler){

				   assert(NULL != _req);

				   assert(NULL != _handler);

				   Response* res = new Response();

				   assert(NULL != res);

				   res->set_uid(_req->uid());

				   res->set_fuid(_req->fuid());

				   res->set_ido(true);

				//Send
				Head head;

				head.type = FIGHTRESPONSE;

				head.version = 1;

				char* buf = new char[res->ByteSize()];

				 *buf = 0;

				head.length = res->ByteSize();

				res->SerializeToArray(buf, head.length);

				_handler->Send(head, buf, head.length);

				delete res;

				return 1;


	}
	*/


		};//PrintCenter

	} //FC

}//PWRD

#endif
