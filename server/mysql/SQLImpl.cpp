#include <SQLImpl.hpp>

namespace PWRD{

	namespace DB{

		/*=============================================================
		 * @private
		 ==============================================================*/
		string SQLImpl::item_ = "";

		string SQLImpl::equip_ = "";

		string SQLImpl::buff_ = "";

		SQLImpl* SQLImpl::instance_ = NULL;

		/*=============================================================
		 * @protected
		 ==============================================================*/
		int SQLImpl::init(){

			Conf* conf = Conf::GetInstance();

			item_ = conf->find("Default", "item");

			equip_ = conf->find("Default", "equip");

			buff_ = conf->find("Default", "buff");

			return 1;

		} //init

		int SQLImpl::fini(){

			return 1;

		} //fini


		/*=============================================================
		 * @public
		 ==============================================================*/
		SQLImpl* SQLImpl::Instance(){

			if(NULL == instance_){

				instance_ = new SQLImpl();

			}

			return instance_;

		} //Instance

		int SQLImpl::Init(const string& _uuid, const string _rolename, const string& _create){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(INIT_MAX).c_str());

			PreparedStatement* max = mysql->Get(SQLDef::Get(INIT_MAX));

			Note("TRACE %s", SQLDef::Get(INIT_USER).c_str());

			PreparedStatement* user = mysql->Get(SQLDef::Get(INIT_USER));

			user->setString(1, _uuid);
			user->setString(2, _rolename);
			user->setString(3, _create);
			user->setString(4, _create);

			ResultSet* result = mysql->Update(user, max);

			assert(NULL != result);

			Note("Result RowsCount: size=%d", result->rowsCount());

			result->next();

			int roleid = result->getInt(1);

			Note("New RoleID: id=%d", roleid);

			MyPool::Release(mysql);

			delete max;

			delete user;

			return roleid;

		} //Init

		int SQLImpl::InitOther(int _roleid){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			PSList* list = new PSList();

			assert(NULL != list);

			Note("TRACE %s", SQLDef::Get(INIT_PK).c_str());

			//pkresult
			boost::shared_ptr<PreparedStatement> pkresult(mysql->Get(SQLDef::Get(INIT_PK)));

			assert(NULL != pkresult);

			list->push_back(pkresult);

			pkresult->setInt(1, _roleid);

			//rankresult
			Note("TRACE %s", SQLDef::Get(INIT_RANK).c_str());

			boost::shared_ptr<PreparedStatement> rankresult(mysql->Get(SQLDef::Get(INIT_RANK)));

			assert(NULL != rankresult);

			rankresult->setInt(1, _roleid);

			list->push_back(rankresult);

			//item
			Note("TRACE %s", SQLDef::Get(INIT_ITEM).c_str());

			boost::shared_ptr<PreparedStatement> item(mysql->Get(SQLDef::Get(INIT_ITEM)));

			assert(NULL != item);

			item->setInt(1, _roleid);
			item->setString(2, item_);

			list->push_back(item);

			//equip
			Note("TRACE %s", SQLDef::Get(INIT_EQUIP).c_str());

			boost::shared_ptr<PreparedStatement> equip(mysql->Get(SQLDef::Get(INIT_EQUIP)));

			assert(NULL != equip);

			equip->setInt(1, _roleid);
			equip->setString(2, equip_);

			list->push_back(equip);

			//buff
			Note("TRACE %s", SQLDef::Get(INIT_BUFF).c_str());

			boost::shared_ptr<PreparedStatement> buff(mysql->Get(SQLDef::Get(INIT_BUFF)));

			assert(NULL != buff);

			buff->setInt(1, _roleid);
			buff->setString(2, buff_);

			list->push_back(buff);

			//friend
			Note("TRACE %s", SQLDef::Get(INIT_FRIEND).c_str());

			boost::shared_ptr<PreparedStatement> friends(mysql->Get(SQLDef::Get(INIT_FRIEND)));

			assert(NULL != friends);

			friends->setInt(1, _roleid);

			list->push_back(friends);

			mysql->Update(list);

			MyPool::Release(mysql);

			delete list;

			return _roleid;

		} //UpdateCash

		boost::shared_ptr<Player> SQLImpl::Get(int _roleid){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			PreparedStatement* ps = mysql->Get(SQLDef::Get(SELECT_USER));

			assert(NULL != ps);

			ps->setInt(1, _roleid);

			ResultSet* result = mysql->Query(ps);

			if(result->next()){

				string roleid = StringTool::Int2Str(_roleid);

				string rolename(result->getString(1));

				int pklevel = result->getInt(2);
				int pkexp = result->getInt(3);
				int ranklevel = result->getInt(4);
				int rankexp = result->getInt(5);

				int pkwin = result->getInt(6);
				int pktotal = result->getInt(7);
				int rankwin = result->getInt(8);
				int ranktotal = result->getInt(9);

				int money = result->getInt(10);
				int gold = result->getInt(11);

				string itemstr = result->getString(13);
				string equipstr = result->getString(14);
				string buffstr = result->getString(15);
				string friendstr = result->getString(16);

				Note("RoleName: %s | %s | %s | %s | %s", rolename.c_str(),
						itemstr.c_str(), equipstr.c_str(), buffstr.c_str(), friendstr.c_str());

				String item(Element_ELEMENT_TYPE_ITEM_TYPE, itemstr);
				String equip(Element_ELEMENT_TYPE_EQUIP_TYPE, equipstr);
				String buff(Element_ELEMENT_TYPE_BUFF_TYPE, buffstr);
				String friends(Element_ELEMENT_TYPE_BUFF_TYPE, friendstr);

				MyPool::Release(mysql);

				boost::shared_ptr<Player> player(new Player(roleid, rolename, pklevel, pkexp, ranklevel, rankexp, pkwin, pktotal, rankwin, ranktotal, money, gold, &item, &equip, &buff, &friends));

				return player;

			} //if NULL != result

			Error("Can't Find the Player: roleid=%d", _roleid);

			MyPool::Release(mysql);

			return boost::shared_ptr<Player>();

		} //Get

		int SQLImpl::UpdatePKExp(int _roleid, int _pkexp){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(UPDATE_PKEXP).c_str());

			PreparedStatement* ps = mysql->Get(SQLDef::Get(UPDATE_PKEXP));

			assert(NULL != ps);

			ps->setInt(2, _roleid);

			ps->setInt(1, _pkexp);

			mysql->Update(ps);

			delete ps;

			MyPool::Release(mysql);

			return 1;

		} //UpdatePKExp

		int SQLImpl::UpdatePKLevel(int _roleid, int _pklevel){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(UPDATE_PKLEVEL).c_str());

			PreparedStatement* ps = mysql->Get(SQLDef::Get(UPDATE_PKLEVEL));

			assert(NULL != ps);

			ps->setInt(2, _roleid);

			ps->setInt(1, _pklevel);

			mysql->Update(ps);

			delete ps;

			MyPool::Release(mysql);

			return 1;

		} //UpdatePKLevel

		int SQLImpl::UpdateRankExp(int _roleid, int _rankexp){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(UPDATE_RANKEXP).c_str());

			PreparedStatement* ps = mysql->Get(SQLDef::Get(UPDATE_RANKEXP));

			assert(NULL != ps);

			ps->setInt(2, _roleid);

			ps->setInt(1, _rankexp);

			mysql->Update(ps);

			delete ps;

			MyPool::Release(mysql);

			return 1;

		} //UpdateRankExp

		int SQLImpl::UpdateRankLevel(int _roleid, int _ranklevel){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(UPDATE_RANKLEVEL).c_str());

			PreparedStatement* ps = mysql->Get(SQLDef::Get(UPDATE_RANKLEVEL));

			assert(NULL != ps);

			ps->setInt(2, _roleid);

			ps->setInt(1, _ranklevel);

			mysql->Update(ps);

			delete ps;

			MyPool::Release(mysql);

			return 1;

		} //UpdateRankLevel

		int SQLImpl::UpdateMoney(int _roleid, int _money){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(UPDATE_MONEY).c_str());

			PreparedStatement* ps = mysql->Get(SQLDef::Get(UPDATE_MONEY));

			assert(NULL != ps);

			ps->setInt(2, _roleid);

			ps->setInt(1, _money);

			mysql->Update(ps);

			delete ps;

			MyPool::Release(mysql);

			return 1;

		} //UpdateMoney

		int SQLImpl::UpdateGold(int _roleid, int _gold){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(UPDATE_GOLD).c_str());

			PreparedStatement* ps = mysql->Get(SQLDef::Get(UPDATE_GOLD));

			assert(NULL != ps);

			ps->setInt(2, _roleid);

			ps->setInt(1, _gold);

			mysql->Update(ps);

			delete ps;

			MyPool::Release(mysql);

			return 1;

		} //UpdateGold

		int SQLImpl::UpdateCashstat(int _roleid, int _cashstat){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(UPDATE_CASHSTAT).c_str());

			PreparedStatement* ps = mysql->Get(SQLDef::Get(UPDATE_CASHSTAT));

			assert(NULL != ps);

			ps->setInt(2, _roleid);

			ps->setInt(1, _cashstat);

			mysql->Update(ps);

			delete ps;

			MyPool::Release(mysql);

			return 1;

		} //Cashstat

		int SQLImpl::UpdateLastLogout(int _roleid, const string& _time){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(UPDATE_LASTLOGOUT).c_str());

			PreparedStatement* ps = mysql->Get(SQLDef::Get(UPDATE_LASTLOGOUT));

			assert(NULL != ps);

			ps->setInt(2, _roleid);

			ps->setString(1, _time);

			mysql->Update(ps);

			delete ps;

			MyPool::Release(mysql);

			return 1;

		} //LastLogout

		int SQLImpl::UpdatePKWin(int _roleid){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(UPDATE_PKWIN).c_str());

			PreparedStatement* ps = mysql->Get(SQLDef::Get(UPDATE_PKWIN));

			assert(NULL != ps);

			ps->setInt(1, _roleid);

			mysql->Update(ps);

			delete ps;

			MyPool::Release(mysql);

			return 1;

		} //UpdatePKWin

		int SQLImpl::UpdatePKLost(int _roleid){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(UPDATE_PKLOST).c_str());

			PreparedStatement* ps = mysql->Get(SQLDef::Get(UPDATE_PKLOST));

			assert(NULL != ps);

			ps->setInt(1, _roleid);

			mysql->Update(ps);

			delete ps;

			MyPool::Release(mysql);

			return 1;

		} //UpdatePKLost

		int SQLImpl::UpdateRankWin(int _roleid){
			
			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(UPDATE_RANKWIN).c_str());

			PreparedStatement* ps = mysql->Get(SQLDef::Get(UPDATE_RANKWIN));

			assert(NULL != ps);

			ps->setInt(1, _roleid);

			mysql->Update(ps);

			delete ps;

			MyPool::Release(mysql);

			return 1;

		} //UpdateRankWin

		int SQLImpl::UpdateRankLost(int _roleid){
			
			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(UPDATE_RANKLOST).c_str());

			PreparedStatement* ps = mysql->Get(SQLDef::Get(UPDATE_RANKLOST));

			assert(NULL != ps);

			ps->setInt(1, _roleid);

			mysql->Update(ps);

			delete ps;

			MyPool::Release(mysql);

			return 1;

		} //UpdateRankLost

		int SQLImpl::UpdateItem(int _roleid, const string& _item){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(UPDATE_ITEM).c_str());

			PreparedStatement* ps = mysql->Get(SQLDef::Get(UPDATE_ITEM));

			assert(NULL != ps);

			ps->setInt(2, _roleid);

			ps->setString(1, _item);

			mysql->Update(ps);

			delete ps;

			MyPool::Release(mysql);

			return 1;

		} //UpdateItem

		int SQLImpl::UpdateEquipment(int _roleid, const string& _equipment){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(UPDATE_EQUIP).c_str());

			PreparedStatement* ps = mysql->Get(SQLDef::Get(UPDATE_EQUIP));

			assert(NULL != ps);

			ps->setInt(2, _roleid);

			ps->setString(1, _equipment);

			mysql->Update(ps);

			delete ps;

			MyPool::Release(mysql);

			return 1;

		} //UpdateEquipment

		int SQLImpl::UpdateBuff(int _roleid, const string& _buff){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(UPDATE_BUFF).c_str());

			PreparedStatement* ps = mysql->Get(SQLDef::Get(UPDATE_BUFF));

			assert(NULL != ps);

			ps->setInt(2, _roleid);

			ps->setString(1, _buff);

			mysql->Update(ps);

			delete ps;

			MyPool::Release(mysql);

			return 1;

		} //UpdateBuff

		int SQLImpl::UpdateFriend(int _roleid, const string& _friend){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(UPDATE_FRIEND).c_str());

			PreparedStatement* ps = mysql->Get(SQLDef::Get(UPDATE_FRIEND));

			assert(NULL != ps);

			ps->setInt(2, _roleid);

			ps->setString(1, _friend);

			mysql->Update(ps);

			delete ps;

			MyPool::Release(mysql);

			return 1;

		} //UpdateFiend

		int SQLImpl::InsertBill(int _roleid, const string& _time, const string& _id, int _num, int _buytype, int _point){

			MySQL* mysql = MyPool::Get();

			assert(NULL != mysql);

			Note("TRACE %s", SQLDef::Get(INSERT_BILL).c_str());

			PreparedStatement* ps = mysql->Get(SQLDef::Get(INSERT_BILL));

			assert(NULL != ps);

			ps->setInt(1, _roleid);

			ps->setString(2, _time);

			ps->setString(3, _id);

			ps->setInt(4, _num);

			ps->setInt(5, _buytype);

			ps->setInt(6, _point);

			mysql->Update(ps);

			delete ps;

			MyPool::Release(mysql);

			return 1;

		} //InsertBill

	} //DB

} //PWRD
