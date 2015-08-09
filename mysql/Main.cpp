#include <MySQL.hpp>
#include <Global.hpp>
#include <Conf.hpp>
#include <Daemon.hpp>
#include <AsyncMySQL.hpp>
#include <PropertyImpl.hpp>

using namespace PWRD;
using namespace PWRD::DB;

int main(int argc, char *argv[])
{
	if(argc != 2){

		Error("Usage: %s <conf>", argv[0]);

		return -1;
	}

	Conf::GetInstance(argv[1]);

	PropertyImpl::Instance();

	Property* pro = PropertyImpl::Get("LiTanHua");

	PropertyImpl::Print(pro);

	return 1;
}
