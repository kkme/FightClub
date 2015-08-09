#ifndef __PLAYER_HPP
#define __PLAYER_HPP

#include <Mutex.hpp>

#include <Daemon.hpp>

#include <Global.hpp>

#include <String.hpp>

#include "boost/tuple/tuple.hpp"

using namespace PWRD;

using namespace PWRD::FC;

using namespace PWRD::IPC;

using namespace boost;

namespace PWRD{

	namespace FC{

		typedef enum{

			ROLEID_INDEX = 0,

			ROLENAME_INDEX,
			
			PKLEVEL_INDEX,

			PKEXP_INDEX,

			RANKLEVEL_INDEX,

			RANKEXP_INDEX,
			
			PKWIN_INDEX,

			PKTATOL_INDEX,

			RANKWIN_INDEX,

			RANKTATOL_INDEX
		
		}PLAYER_F_INDEX;

		typedef enum{

			MONEY_INDEX,

			GOLD_INDEX,

			ITEM_INDEX,

			EQUIP_INDEX,

			BUFF_INDEX,

			FRIENDS_INDEX,

			DIRTY_INDEX


		}PLAYER_E_INDEX;
	
		//roleid, rolename, pklevel, pkexp, ranklevel, rankexp, pkwin, pktotal, rankwin, ranktotal,
		typedef boost::tuple<string, string, int, int, int, int, int, int, int, int> Player_F_t; //Fundamental Attribute

		//money, gold, items, equips, buffs, frends, dirty
		typedef boost::tuple<int, int, String, String, String, String, bool> Player_E_t; //Extra Attribute

		class Player{

			public:

				Player(const Player_F_t& _f, const Player_E_t& _e);

				Player(string _roleid, string _rolename, int _pklevel, int _pkexp, int _ranklevel, int _rankexp, int _pkwin, int _pktotal, int _rankwin, int _ranktotal, int _money, int _gold, String* _item, String* _equip, String* _buff, String* _friend);

				virtual ~Player(){ fini(); }

				Player_F_t GetF(){ return player_f_t_;}

				Player_E_t GetE(){ return player_e_t_;}

				string GetRoleID(){ ScopedLock lock(mutex_); return player_f_t_.get<ROLEID_INDEX>(); }

				string GetRoleName(){ ScopedLock lock(mutex_); return player_f_t_.get<ROLENAME_INDEX>(); }

				//Getter
				int GetPKLevel(){ ScopedLock lock(mutex_); return player_f_t_.get<PKLEVEL_INDEX>(); }

				int GetPKExp(){ ScopedLock lock(mutex_); return player_f_t_.get<PKEXP_INDEX>(); }

				int GetRankLevel(){ ScopedLock lock(mutex_); return player_f_t_.get<RANKLEVEL_INDEX>(); }

				int GetRankExp(){ ScopedLock lock(mutex_); return player_f_t_.get<RANKEXP_INDEX>(); }

				int GetPKWin(){ ScopedLock lock(mutex_); return player_f_t_.get<PKWIN_INDEX>(); }

				int GetPKTatol(){ ScopedLock lock(mutex_); return player_f_t_.get<PKTATOL_INDEX>(); }

				int GetRanKWin(){ ScopedLock lock(mutex_); return player_f_t_.get<RANKWIN_INDEX>(); }

				int GetRanKTatol(){ ScopedLock lock(mutex_); return player_f_t_.get<RANKTATOL_INDEX>(); }

				int GetMoney(){ ScopedLock lock(mutex_); return player_e_t_.get<MONEY_INDEX>(); }

				int GetGold(){ ScopedLock lock(mutex_); return player_e_t_.get<GOLD_INDEX>(); }

				String GetItems(){ ScopedLock lock(mutex_); return player_e_t_.get<ITEM_INDEX>(); }

				String GetEquips(){ ScopedLock lock(mutex_); return player_e_t_.get<EQUIP_INDEX>(); }

				String GetBuffs(){ ScopedLock lock(mutex_); return player_e_t_.get<BUFF_INDEX>(); }

				String GetFriends(){ ScopedLock lock(mutex_); return player_e_t_.get<FRIENDS_INDEX>(); }

				//Setter
				void SetPKLevel(int _level){ ScopedLock lock(mutex_); get<PKLEVEL_INDEX>(player_f_t_) = _level;  get<DIRTY_INDEX>(player_f_t_) = true; }

				void SetPKExp(int _exp){ ScopedLock lock(mutex_); get<PKEXP_INDEX>(player_f_t_) = _exp;  get<DIRTY_INDEX>(player_f_t_) = true; }

				void SetRankLevel(int _level){ ScopedLock lock(mutex_); get<RANKLEVEL_INDEX>(player_f_t_) = _level;  get<DIRTY_INDEX>(player_f_t_) = true; }

				void SetRankExp(int _exp){ ScopedLock lock(mutex_); get<RANKEXP_INDEX>(player_f_t_) = _exp;  get<DIRTY_INDEX>(player_f_t_) = true; }

				void SetPKWin(){ ScopedLock lock(mutex_); ++get<PKWIN_INDEX>(player_f_t_); ++get<PKTATOL_INDEX>(player_f_t_); get<DIRTY_INDEX>(player_f_t_) = true; }
				void SetPKLost(){ ScopedLock lock(mutex_); ++get<PKTATOL_INDEX>(player_f_t_); get<DIRTY_INDEX>(player_f_t_) = true; }

				void SetRankWin(){ ScopedLock lock(mutex_); ++get<RANKWIN_INDEX>(player_f_t_); ++get<RANKTATOL_INDEX>(player_f_t_); get<DIRTY_INDEX>(player_f_t_) = true; }
				void SetRankLost(){ ScopedLock lock(mutex_); ++get<RANKTATOL_INDEX>(player_f_t_); get<DIRTY_INDEX>(player_f_t_) = true; }

				void SetMoney(int _money){ ScopedLock lock(mutex_);  get<MONEY_INDEX>(player_e_t_) = _money; get<DIRTY_INDEX>(player_e_t_) = true; }

				void SetGold(int _gold){ ScopedLock lock(mutex_);  get<GOLD_INDEX>(player_e_t_) = _gold; get<DIRTY_INDEX>(player_e_t_) = true; }

				void SetCashStat(int _cashstat){ ScopedLock lock(mutex_);  get<GOLD_INDEX>(player_e_t_) = _cashstat; get<DIRTY_INDEX>(player_e_t_) = true; }

				void SetItems(const String& _items){ ScopedLock lock(mutex_); get<ITEM_INDEX>(player_e_t_) = _items;  get<DIRTY_INDEX>(player_e_t_) = true; }

				void SetEquips(const String& _equips){ ScopedLock lock(mutex_); get<EQUIP_INDEX>(player_e_t_) = _equips; get<DIRTY_INDEX>(player_e_t_) = true; }

				void SetBuffs(const String& _buffs){ ScopedLock lock(mutex_); get<BUFF_INDEX>(player_e_t_) = _buffs; get<DIRTY_INDEX>(player_e_t_) = true; }

				void SetFriends(const String& _friends){ ScopedLock lock(mutex_); get<BUFF_INDEX>(player_e_t_) = _friends; get<DIRTY_INDEX>(player_e_t_) = true; }

				//Dirty
				bool Dirty(){ ScopedLock lock(mutex_); return get<DIRTY_INDEX>(player_e_t_); }

			protected:

				int init();

				int fini();

			private:

				Mutex mutex_;

				Player_F_t player_f_t_;

				Player_E_t player_e_t_;


		}; //Player

	} //FC

} //PWRD


#endif
