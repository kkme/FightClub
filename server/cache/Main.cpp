#include <MyPool.hpp>

#include <SQLDef.hpp>

#include <SQLImpl.hpp>

#include <String.hpp>

#include <Player.hpp>

#include <PlayerCache.hpp>

using namespace PWRD::FC;

using namespace PWRD::DB;

int main(int argc, char *argv[]) {

	if(argc != 2){

		Error("Usage: %s <conf>", argv[0]);

		return -1;

	}

	Conf::GetInstance(argv[1]);

	MyPool::Instance();

	SQLDef::Instance();

	SQLImpl::Instance();

	PlayerCache::Instance();

	string uuid = "ASDFGHJKL";

	string rolename = "LiDaWei";

	string create = "2013-01-08 23:45:32";

	int roleid = SQLImpl::Init(uuid, rolename, create);

	SQLImpl::InitOther(roleid);

	boost::shared_ptr<Player> player = SQLImpl::Get(roleid);

	PlayerCache::Registe(player);

	//Following to be Tested

	int pkexp = 242, pklevel = 5, rankexp = 432, ranklevel = 10, gold = 104, money = 3242, cashstat = 4421;

	string last = "2013-01-24 23:32:12";

	int buytype = 1, point = 100;

	SQLImpl::UpdatePKExp(roleid, pkexp);

	SQLImpl::UpdatePKLevel(roleid, pklevel);

	SQLImpl::UpdateRankExp(roleid, rankexp);

	SQLImpl::UpdateRankLevel(roleid, ranklevel);

	SQLImpl::UpdateMoney(roleid, money);

	SQLImpl::UpdateGold(roleid, gold);

	SQLImpl::UpdateCashstat(roleid, cashstat);

	SQLImpl::UpdateLastLogout(roleid, last);

	SQLImpl::UpdatePKWin(roleid);

	SQLImpl::UpdatePKLost(roleid);

	SQLImpl::UpdateRankWin(roleid);

	SQLImpl::UpdateRankLost(roleid);

	string item = "item0:1:0;item2:3:0;item4:5:1";

	SQLImpl::UpdateItem(roleid, item);

	string equip = "equip0:1:0;equip3:2:1;equip23:1:0;";

	SQLImpl::UpdateEquipment(roleid, equip);

	string buff = "buff0:1:0;buff3:2:1;buff2:3:0";

	SQLImpl::UpdateBuff(roleid, buff);

	string friends = "132;3402;2342;234;45;";

	SQLImpl::UpdateFriend(roleid, friends);

	string id = "item0";

	SQLImpl::InsertBill(roleid, last, id, 10, buytype, point);

	return 1;

}
