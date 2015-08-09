#include <PlayerCache.hpp>

namespace PWRD{

	namespace FC{

		/*=============================================================
		 * @private:
		 ==============================================================*/
		Mutex PlayerCache::mutex_;

		PlayerMap PlayerCache::map_;

		PlayerCache* PlayerCache::instance_ = NULL;


		/*=============================================================
		 * @protected
		 ==============================================================*/
		int PlayerCache::init(){

			return 1;

		}

		int PlayerCache::fini(){

			return 1;
		}

		/*=============================================================
		 * @public
		 ==============================================================*/
		PlayerCache* PlayerCache::Instance(){

			if(NULL == instance_){

				instance_ = new PlayerCache();

			}

			return instance_;

		} //Instance

		void PlayerCache::Registe(boost::shared_ptr<Player> _player){


			ScopedLock lock(mutex_);

			if(map_.end() == map_.find(_player->GetRoleID())){

				map_[_player->GetRoleID()] = _player;

				Note("Insert a Player: roleid=%s, rolename=%s",
					_player->GetRoleID().c_str(), _player->GetRoleName().c_str());

				return;

			}

			Error("Item Exist: RoleID=%s, RoleName=%s", _player->GetRoleID().c_str(), _player->GetRoleName().c_str());

			return;

		} //Registe

		void PlayerCache::Remove(const string& _roleid){

			Trace("TRACE Delete a Gamer: roleid=%s", _roleid.c_str());

			ScopedLock lock(mutex_);

			PlayerMap::iterator it = map_.find(_roleid);

			if(map_.end() != it){

				map_.erase(it);

				return;

			}

			Error("Can't Find Item: roleid=%s", _roleid.c_str());

			return;

		} //Remove

		long PlayerCache::Size(){

			ScopedLock lock(mutex_);

			return map_.size();


		} //Size

		boost::shared_ptr<Player>  PlayerCache::Get(const string& _roleid){

			Trace("TRACE Check Item: roleid=%s", _roleid.c_str());

			ScopedLock lock(mutex_);

			PlayerMap::iterator it = map_.find(_roleid);

			if(map_.end() != it){

				return it->second;

			}

			return boost::shared_ptr<Player>();

		} //Get


	} //FC

} //PWRD
