#ifndef __PLAYERCACHE_HPP
#define __PLAYERCACHE_HPP

#include <Player.hpp>

#include <String.hpp>

using namespace PWRD::FC;

namespace PWRD{

	namespace FC{

		typedef map<string, boost::shared_ptr<Player> > PlayerMap;

		class PlayerCache{

			public:

				static PlayerCache* Instance();

				virtual ~PlayerCache(){ fini(); }

				static long Size();

				static void Remove(const string& _roleid);

				static void Registe(boost::shared_ptr<Player> _player);

				static boost::shared_ptr<Player> Get(const string& _roleid);

				//Getter
				static int GetPKLevel(const string& _roleid){ if(NULL != Get(_roleid)){ return Get(_roleid)->GetPKLevel(); } return 0; }

				static int GetPKExp(const string& _roleid){ if(NULL != Get(_roleid)){ return Get(_roleid)->GetPKExp(); } return 0; }

				static int GetRankLevel(const string& _roleid){ if(NULL != Get(_roleid)){ return Get(_roleid)->GetRankLevel(); } return 0;  }

				static int GetRankExp(const string& _roleid){  if(NULL != Get(_roleid)){ return Get(_roleid)->GetRankExp(); } return 0; }

				static int GetPKWin(const string& _roleid){  if(NULL != Get(_roleid)){ return Get(_roleid)->GetPKWin(); } return 0; }

				static int GetPKTatol(const string& _roleid){ if(NULL != Get(_roleid)){ return Get(_roleid)->GetPKTatol(); } return 0; }

				static int GetRanKWin(const string& _roleid){ if(NULL != Get(_roleid)){ return Get(_roleid)->GetRanKWin(); } return 0; }

				static int GetRanKTatol(const string& _roleid){ if(NULL != Get(_roleid)){ return Get(_roleid)->GetRanKTatol(); } return 0; }

				static int GetMoney(const string& _roleid){ if(NULL != Get(_roleid)){ return Get(_roleid)->GetMoney(); } return 0; }

				static int GetGold(const string& _roleid){ if(NULL != Get(_roleid)){ return Get(_roleid)->GetGold(); } return 0; }

				static String GetItems(const string& _roleid){ if(NULL != Get(_roleid)){ return Get(_roleid)->GetItems(); } return String(Element_ELEMENT_TYPE_NULL_TYPE); }

				static String GetEquips(const string& _roleid){ if(NULL != Get(_roleid)){ return Get(_roleid)->GetEquips(); } return String(Element_ELEMENT_TYPE_NULL_TYPE); }

				static String GetBuffs(const string& _roleid){ if(NULL != Get(_roleid)){ return Get(_roleid)->GetBuffs(); } return String(Element_ELEMENT_TYPE_NULL_TYPE); }

				static String GetFriends(const string& _roleid){ if(NULL != Get(_roleid)){ return Get(_roleid)->GetFriends(); } return String(Element_ELEMENT_TYPE_NULL_TYPE); }

				//Setter
				static void SetPKLevel(const string& _roleid, int _level){ if(NULL != Get(_roleid)) return Get(_roleid)->SetPKLevel(_level); }

				static void SetPKExp(const string& _roleid, int _exp){ if(NULL != Get(_roleid)) return Get(_roleid)->SetPKExp(_exp); }

				static void SetRankLevel(const string& _roleid, int _level){ if(NULL != Get(_roleid)) return Get(_roleid)->SetRankLevel(_level); }

				static void SetRankExp(const string& _roleid, int _exp){  if(NULL != Get(_roleid)) return Get(_roleid)->SetRankExp(_exp); }

				static void SetPKWin(const string& _roleid){ if(NULL != Get(_roleid)) return Get(_roleid)->SetPKWin(); }

				static void SetPKLost(const string& _roleid){ if(NULL != Get(_roleid)) return Get(_roleid)->SetPKLost(); }

				static void SetRankWin(const string& _roleid){ if(NULL != Get(_roleid)) return Get(_roleid)->SetRankWin(); }

				static void SetRankLost(const string& _roleid){ if(NULL != Get(_roleid)) return Get(_roleid)->SetRankLost(); }

				static void SetMoney(const string& _roleid, int _money){ if(NULL != Get(_roleid)) return Get(_roleid)->SetMoney(_money); }

				static void SetGold(const string& _roleid, int _gold){ if(NULL != Get(_roleid)) return Get(_roleid)->SetGold(_gold); }

				static void SetItems(const string& _roleid, const String& _items){ if(NULL != Get(_roleid)) return Get(_roleid)->SetItems(_items); }

				static void SetEquips(const string& _roleid, const String& _equips){ if(NULL != Get(_roleid)) return Get(_roleid)->SetEquips(_equips); }

				static void SetBuffs(const string& _roleid, const String& _buffs){ if(NULL != Get(_roleid)) return Get(_roleid)->SetBuffs(_buffs); }

				static void SetFriends(const string& _roleid, const String& _friends){ if(NULL != Get(_roleid)) return Get(_roleid)->SetFriends(_friends); }

				//Dirty
				static bool Dirty(const string& _roleid){ if(NULL != Get(_roleid)) return Get(_roleid)->Dirty(); }


			protected:

				static int init();

				static int fini();

			private:

				static Mutex mutex_;

				static PlayerMap map_;

				static PlayerCache* instance_;

		}; //PlayerCache

	} //FC

} //PWRD

#endif
