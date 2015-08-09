#include <MyPool.hpp>

namespace PWRD{

	namespace DB{

		int MyPool::maxsize_ = 10;

		int MyPool::currsize_ = 0;

		Mutex MyPool::lock_;

		MySQL* MyPool::mysql_ = NULL;

		MyPool* MyPool::instance_ = NULL;

		ConnectionPool* MyPool::pool_ = NULL;

		/*==============================================================
		 * @protected
		 ==============================================================*/

		int MyPool::init(){

			pool_ = new ConnectionPool();

			assert(NULL != pool_);

			Conf* conf = Conf::GetInstance();

			if(NULL == conf){

				Error("Conf is NULL!");

				return -1;

			}

			string size = conf->find("Database", "size");

			maxsize_ = StringTool::Str2Int(size);

			if(0 < maxsize_ && maxsize_ > 100){

				maxsize_ = 10;

			}

			Note("Max MySQL Pool Size: maxsize=%d", maxsize_);

			string host = conf->find("DataBase", "host");

			string user = conf->find("DataBase", "user");

			string pass = conf->find("DataBase", "pass");

			string name = conf->find("DataBase", "name");


			for(int step = 0; step < maxsize_; step++){

				MySQL* mysql = new MySQL(host, user, pass, name);

				assert(NULL != mysql);

				++currsize_;

				mysql->Connect();

				pool_->push(mysql);


			}

			mysql_ = new MySQL(host, user, pass, name);

			assert(mysql_);

			mysql_->Connect();

			++currsize_;

			return 1;

		}

		int MyPool::fini(){

			for(int step = 0; step < maxsize_; step++){

				MySQL* mysql = pool_->front();

				pool_->pop();

				delete mysql;

			}

			delete pool_;

			return 1;

		}

		/*==============================================================
		 * @public
		 ==============================================================*/
		MyPool* MyPool::Instance(){

			if(NULL == instance_){

				instance_ = new MyPool();

			}

			return instance_;

		}//Instance

		MySQL* MyPool::Get(){

			ScopedLock locker(lock_);

			MySQL* mysql = NULL;

			if(pool_->size() > 0){

				mysql = pool_->front();

				pool_->pop();

				--currsize_;

				Note("Get a Connection: MySQL=%p", mysql);

				return mysql;
			
			}

			return mysql_;


		}//Get

		void MyPool::Release(MySQL* _mysql){

			ScopedLock locker(lock_);

			assert(NULL != _mysql);

			pool_->push(_mysql);

			++currsize_;

			Note("Relase a Connection: MySQL=%p", _mysql);

			return ;


		}//Release

	}//DB

}//PWRD
