#ifndef __TESTCASE_HPP
#define __TESTCASE_HPP

#include <Conf.hpp>

#include <Client.hpp>

using namespace PWRD;

using namespace PWRD::Network;

namespace PWRD{

	class TestCase{
	
		public:

			virtual ~TestCase(){ fini(); }

			static TestCase* Instance(){
				
				if(NULL == instance_){
				
					instance_ = new TestCase();

				}

				return instance_;
			
			}

			static void T_Registe(Client* _handler);

			static void T_Login(Client* _handler);

			static void T_Request(Client* _handler);

			static void T_Fight(Client* _handler);

			static void T_HardBeat(Client* _handler);

			static void T_Item(Client* _handler);

			static void T_QTE(Client* _handler);

			static void T_PKList(Client* _handler);

			static void T_Property(Client* _handler);

			static void T_Friend(Client* _handler);

			static void T_FriendNum(Client* _handler);

			static void T_FriendIndex(Client* _handler);

			static void T_Bill(Client* _handler);

			static void T_Stat(Client* _handler);
			/*
			static void T_Version(Client* _handler);


			static void T_PKList(Client* _handler);

			static void T_Fight(Client* _handler);

			static void T_FightResult(Client* _handler);

			static void T_FightRequest(Client* _handler);

			static void T_FightResponse(Client* _handler);
			*/

		protected:
			
			static int init();

			static int fini();

			TestCase(){ init(); }

		private:

			static string rolename_;

			static string roleid_;

			static string froleid_;

			static string uuid_;
			
			static Head head_;

			static char buf_[BUFSIZ];

			static TestCase* instance_;

	};

}


#endif
