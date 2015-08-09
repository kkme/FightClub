#ifndef __SQLIMPL_HPP
#define __SQLIMPL_HPP

#include <Conf.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

#include <MySQL.hpp>

#include <Player.hpp>

#include <MyPool.hpp>

#include <SQLDef.hpp>

#include <PlayerCache.hpp>

using namespace PWRD;

using namespace PWRD::DB;

using namespace PWRD::FC;

namespace PWRD{

	namespace DB{

		class SQLImpl{

			public:

				static SQLImpl* Instance(); 

				~SQLImpl(){ fini(); };

				static int Init(const string& _uuid, const string _rolename, const string& _create);

				static int InitOther(int _roleid);

				static boost::shared_ptr<Player> Get(int _roleid);

				static int UpdatePKExp(int _roleid, int _pkexp);

				static int UpdatePKLevel(int _roleid, int _pklevel);

				static int UpdateRankExp(int _roleid, int _rankexp);

				static int UpdateRankLevel(int _roleid, int _ranklevel);

				static int UpdateMoney(int _roleid, int _money);

				static int UpdateGold(int _roleid, int _gold);

				static int UpdateCashstat(int _roleid, int _cashstat);

				static int UpdateLastLogout(int _roleid, const string& _time);

				static int UpdatePKWin(int _roleid);

				static int UpdatePKLost(int _roleid);

				static int UpdateRankWin(int _roleid);

				static int UpdateRankLost(int _roleid);

				static int UpdateItem(int _roleid, const string& _item);

				static int UpdateEquipment(int _roleid, const string& _equipment);

				static int UpdateBuff(int _roleid, const string& _buff);

				static int UpdateFriend(int _roleid, const string& _friend);

				static int InsertBill(int _roleid, const string& _time, const string& _id, int _num, int _buytype, int _point);

			protected:

				SQLImpl(){ init(); };

				static int init();

				static int fini();

			private:
				static string item_;

				static string equip_;

				static string buff_;

				static SQLImpl* instance_;


		}; //SQLImpl


	} //DB

} //PWRD

#endif
