#include <MySQL.hpp>
#include <Global.hpp>
#include <Conf.hpp>
#include <Daemon.hpp>
#include <MyPool.hpp>
#include <Test.hpp>

using namespace PWRD;
using namespace PWRD::DB;

int main(int argc, char *argv[])
{
	if(argc != 2){

		Error("Usage: %s <conf>", argv[0]);

		return -1;
	}

	Conf::GetInstance(argv[1]);

	MyPool::Instance();

	TestUser(MyPool::Get());
	TestEquipment(MyPool::Get());
	TestFriend(MyPool::Get());
	TestPKResult(MyPool::Get());
	TestRankResult(MyPool::Get());
	TestMail(MyPool::Get());
	TestRankTop(MyPool::Get());
	TestPKTop(MyPool::Get());
	TestBill(MyPool::Get());

	/*
	MySQL* mysql = MyPool::Get();

	PreparedStatement* ps = mysql->Get("SELECT RoleID, Time, ItemID, Num, BuyType, Point FROM BillTable WHERE RoleID=3");

	ResultSet* result = mysql->Query(ps);

	Note("Result Count: %d", result->rowsCount());
	*/

	return 1;
}
