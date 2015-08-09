#include <DispatchCenter.hpp>

namespace PWRD{

	/*=========================================================
	 * @protected
	 =========================================================*/
	void DispatchCenter::Load(){

		Conf* conf = Conf::GetInstance();

		conf->getkeys("Service", serkeys_);

		Vector::const_iterator it;
		
		for(it = serkeys_.begin(); it != serkeys_.end(); it++){
			
			string sername = conf->find("Service", *it);

			aqmap_[sername] = new ActiveQueueMap();

			assert(aqmap_[sername]);

			smap_[sername] = Switch(sername);
		}

	}

	Service* DispatchCenter::Switch(const string& _name){

		Service* service = NULL;

		if(!_name.compare("FightService")){

			service = new FightService();


		}
		else if(!_name.compare("DBService")){

			service = new DBService();

		}
		else if(!_name.compare("CacheService")){

			service = new CacheService();

		}
		else if(!_name.compare("FileService")){

			service = new FileService();

		}
		else if(!_name.compare("PKListService")){

			service = new PKListService();

		}
		else if(!_name.compare("SNSFriendService")){

			service = new SNSFriendService();
		}
		else if(!_name.compare("RANKINGService")){

			service = new RANKINGService();

		}
		else if(!_name.compare("HistoryService")){

			service = new HistoryService();

		}
		else if(!_name.compare("VersionService")){

			service = new VersionService();

		}
		else if(!_name.compare("ShitListService")){

			service = new ShitListService();
		}
		else if(!_name.compare("RegistryService")){

			service = new RegistryService();
		}
		else if(!_name.compare("MailService")){

			service = new MailService();
		}
		else if(!_name.compare("StoreService")){

			service = new StoreService();
		}
		else{

			Error("Can't find this Service! name=%s", _name.c_str());

		}

		assert(NULL != service);

		return service;

	}

	int DispatchCenter::init(){

		smap_ = new ServiceMap();

		assert(smap_ != NULL);

		Load();

		return 1;

	}

	int DispatchCenter::fini(){

		if(NULL != smap_){

			delete smap_;

		}
		
		return 1;

	}

	/*=========================================================
	 * @public
	 =========================================================*/

	void DispatchCenter::Run(){

		
		Trace("TRACE DispatchCenter Run");

		while(true){

			//do something
			if(Delivery::Instance()->AsyncWait() < 0){

				continue;

			}

		}

	}

	void DispatchCenter::Register(string _name, Service* _service){
		
		Trace("TRACE DispatchCenter Register: name=%s <===> service=%p", _name.c_str(), _service);

		(*smap_)[_name] = _service;

	}

	void DispatchCenter::Remove(string _name){
		
		Trace("TRACE DispatchCenter Remove: name=%s", _name.c_str());

		smap_->erase(_name);

	}

}//PWRD
