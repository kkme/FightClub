#include <Registry.hpp>

namespace PWRD{

	namespace Mem{

		/*=============================================================
		 * @private:
		 ==============================================================*/
		Mutex Registry::mutex_;

		GamerSet Registry::map_;

		Registry* Registry::instance_ = NULL;


		/*=============================================================
		 * @protected
		 ==============================================================*/
		int Registry::init(){

			return 1;

		}

		int Registry::fini(){

			return 1;
		}

		/*=============================================================
		 * @public
		 ==============================================================*/
		Registry* Registry::Instance(){

			if(NULL == instance_){

				instance_ = new Registry();

			}

			return instance_;

		} //Instance

		void Registry::Registe(const Gamer_t& _gamer){

			Trace("TRACE Insert a Gamer: roleid=%s, handler=%p, pklevel=%ld, ranklevel=%ld", 
					_gamer.roleid.c_str(), _gamer.handler, _gamer.pklevel, _gamer.ranklevel);

			ScopedLock lock(mutex_);

			if(!map_.insert(_gamer).second){

				Error("Item Exist: roleid=%s", _gamer.roleid.c_str());

			}

		} //Registe

		void Registry::Remove(HANDLER _handler){

			Trace("TRACE Delete a Gamer: handler=%p", _handler);

			ScopedLock lock(mutex_);

			GamerSet::index<HANDLERTAG>::type& rl = map_.get<HANDLERTAG>();

			GamerSet::index<HANDLERTAG>::type::iterator it = rl.find(_handler);

			if(rl.end() != it){

				rl.erase(it);

				return;

			}

			Error("Can't Find The Item: handler=%p", _handler);

			return;

		} //Remove

		long Registry::Size(){

			ScopedLock lock(mutex_);

			return map_.size();


		}

		bool Registry::Check(const string& _roleid){

			Trace("TRACE Check Item: roleid=%s", _roleid.c_str());

			ScopedLock lock(mutex_);

			GamerSet::index<ROLEIDTAG>::type& rl = map_.get<ROLEIDTAG>();

			GamerSet::index<ROLEIDTAG>::type::iterator it = rl.find(_roleid);

			if(map_.end() != it){

				return true;

			}

			return false;

		} //Check

		boost::shared_ptr<Gamer_t> Registry::Get(const string& _roleid){

			Trace("TRACE Find tuple: roleid=%s", _roleid.c_str());

			ScopedLock lock(mutex_);

			GamerSet::index<ROLEIDTAG>::type& rl = map_.get<ROLEIDTAG>();

			GamerSet::index<ROLEIDTAG>::type::iterator it = rl.find(_roleid);

			if(map_.end() != it){

				Trace("TRACE Find the Item: roleid=%s", _roleid.c_str());

				boost::shared_ptr<Gamer_t> gamer(new Gamer_t(it->roleid, it->handler, it->pklevel, it->ranklevel));

				return gamer;
			}

			Error("Can't Find Item: roleid=%s", _roleid.c_str());

			return boost::shared_ptr<Gamer_t>();

		} //Get

		GamerList Registry::Get(int _level, int _num, bool _type){

			ScopedLock lock(mutex_);

			GamerList list;

			int step = 0;

			//Rank
			if(_type){

				GamerSet::index<RANKLEVELTAG>::type& rl = map_.get<RANKLEVELTAG>();

				GamerSet::index<RANKLEVELTAG>::type::iterator it = rl.lower_bound(_level);

				GamerSet::index<RANKLEVELTAG>::type::iterator end = rl.upper_bound(_level);

				while(end != it && step < _num){

					if(IDLE == it->stat){

						boost::shared_ptr<Gamer_t> gamer(new Gamer_t(it->roleid, it->handler, it->ranklevel, it->stat, true));

						list.push_back(gamer);

					} //if stat IDLE

					it++;

					step++;

				}

				return list;

			}
			//PK
			else{

				GamerSet::index<PKLEVELTAG>::type& rl = map_.get<PKLEVELTAG>();

				GamerSet::index<PKLEVELTAG>::type::iterator it = rl.lower_bound(_level);

				GamerSet::index<PKLEVELTAG>::type::iterator end = rl.upper_bound(_level);

				while(end != it && step < _num){

					if(IDLE == it->stat){

						boost::shared_ptr<Gamer_t> gamer(new Gamer_t(it->roleid, it->handler, it->pklevel, it->stat));

						list.push_back(gamer);

					} //if stat IDLE

					it++;

					step++;
				}

				return list;

			} //else PK

		} //Get

		string Registry::Get(HANDLER _handler){

			Trace("TRACE Delete a Gamer: handler=%p", _handler);

			ScopedLock lock(mutex_);

			GamerSet::index<HANDLERTAG>::type& rl = map_.get<HANDLERTAG>();

			GamerSet::index<HANDLERTAG>::type::iterator it = rl.find(_handler);

			if(rl.end() != it){

				return it->roleid;

			}

			Error("Can't Find The Item: handler=%p", _handler);

			return string("");
		
		} //Get

		bool Registry::UpdateLevel(const string& _roleid, int _level, bool _type){

			Trace("TRACE Find tuple: roleid=%s", _roleid.c_str());

			ScopedLock lock(mutex_);

			GamerSet::index<ROLEIDTAG>::type& rl = map_.get<ROLEIDTAG>();

			GamerSet::index<ROLEIDTAG>::type::iterator it = rl.find(_roleid);

			if(rl.end() != it){

				Gamer_t gamer = *it;

				if(_type){

					gamer.ranklevel = _level;
				}
				else{
					gamer.pklevel = _level;

				}

				if(!rl.replace(it, gamer)){

					Error("Replace the Item's Cash Failed: roleid=%s, level=%ld", _roleid.c_str(), _level);

					return false;

				} //if replace

				return true;


			} //if !=

			Error("Can't Find the Item: roleid=%s", _roleid.c_str());

			return false;

		} //UpdateLevel

		bool Registry::UpdateStat(const string& _roleid, STAT _stat){

			Trace("TRACE Find tuple: roleid=%s", _roleid.c_str());

			ScopedLock lock(mutex_);

			GamerSet::index<ROLEIDTAG>::type& rl = map_.get<ROLEIDTAG>();

			GamerSet::index<ROLEIDTAG>::type::iterator it = rl.find(_roleid);

			if(rl.end() != it){

				Gamer_t gamer = *it;

				gamer.stat = _stat;

				if(!rl.replace(it, gamer)){

					Error("Replace the Item's Cash Failed: roleid=%s", _roleid.c_str());

					return false;

				} //if replace

				return true;


			} //if !=

			Error("Can't Find the Item: roleid=%s", _roleid.c_str());

			return false;

		} //UpdateStat
			
		STAT Registry::QueryStat(const string& _roleid){
			
			Trace("TRACE Search Gamer: roleid=%s", _roleid.c_str());

			ScopedLock lock(mutex_);

			GamerSet::index<ROLEIDTAG>::type& rl = map_.get<ROLEIDTAG>();

			GamerSet::index<ROLEIDTAG>::type::iterator it = rl.find(_roleid);

			if(rl.end() != it){

				return it->stat;

			} //if !=

			Error("Can't Find the Item: roleid=%s", _roleid.c_str());

			return BREAK;

		} //QueryStat

		HANDLER Registry::QueryHandler(const string& _roleid){
			
			Trace("TRACE Search Gamer: roleid=%s", _roleid.c_str());

			ScopedLock lock(mutex_);

			GamerSet::index<ROLEIDTAG>::type& rl = map_.get<ROLEIDTAG>();

			GamerSet::index<ROLEIDTAG>::type::iterator it = rl.find(_roleid);

			if(rl.end() != it){

				return it->handler;

			} //if !=

			Error("Can't Find the Item: roleid=%s", _roleid.c_str());

			return NULL;

		} //QureyHandler


	} //Mem

} //PWRD
