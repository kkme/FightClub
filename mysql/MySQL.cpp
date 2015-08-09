#include "MySQL.hpp"

namespace PWRD{

	namespace DB{

		/*
		 *  @protected
		 */
		int MySQL::init(){

			driver_ = sql::mysql::get_driver_instance();

			if(NULL == driver_){

				Error("Create driver failed!");

				return -1;
			}

			sql_ = ""; conn_ = NULL; stmt_ = NULL; pstmt_ = NULL;

			Conf *conf = Conf::GetInstance();

			qurey_sql_ = conf->find("MySQL", "qurey");

			return 1;

		}

		int MySQL::fini(){

			if(NULL != conn_)

				delete conn_;

			if(NULL != stmt_)

				delete stmt_;

			if(NULL != pstmt_)

				delete pstmt_;

			return 1;

		}

		/*
		 *  @public
		 */
		int MySQL::Connect(){

			try{
				conn_ = driver_->connect(url_, user_, pass_);

				if(NULL == conn_){

					Error("Create connection failed");

					return -1;
				}

				stmt_ = conn_->createStatement();

				if(NULL == stmt_){

					Error("Create statement failed");

					return -1;
				}

				conn_->setSchema(db_);

			}
			catch(sql::SQLException &e){

				Error("Mysql exception: expno=%d, sqlstate=%s, expstr=%s", e.getErrorCode(),
						e.getSQLState().c_str(), e.what());
			}

			return 1;
		}

		int MySQL::Execute(const string& _sql){

			return Execute(_sql.c_str(), _sql.size());

		}

		int MySQL::Execute(const char *_sql, int _size UNUSED){

			try{
				if(conn_->isClosed()){

					Connect();
				}

				stmt_->execute(_sql);

				return 1;

			}
			catch(sql::SQLException &e){

				Error("Mysql exception: expno=%d, sqlstate=%s, expstr=%s",
						e.getErrorCode(), e.getSQLState().c_str(), e.what());

				return -1;

			}

		}//Execute


		int MySQL::Update(const string& _sql){

			return Update(_sql.c_str(), _sql.size());

		}//Update


		int MySQL::Update(const char *_sql, int _size UNUSED){

			stringstream msg;

			try{

				if(conn_->isClosed()){

					Connect();

				}

				int affected_rows = stmt_->executeUpdate(_sql);

				Trace("TRACE update indicates %d affected rows", affected_rows);

				if(-1 == affected_rows){

					msg.str("");

					msg << "update failed: sql=" << sql_;

					throw std::runtime_error(msg.str());

				}

			}	
			catch(sql::SQLException &e){

				Error("Mysql exception: expno=%d, sqlstate=%s, expstr=%s",
						e.getErrorCode(), e.getSQLState().c_str(), e.what());
				return -1;

			}
			catch (std::runtime_error &e) {

				Error("Update runtime error: errstr=%s", e.what());

				return -1;
			}

			return 1;

		}//Update

		int MySQL::Close(){

			return 1;

		}

		ResultSet* MySQL::Qurey(const string& _sql){


			return Qurey(_sql.c_str(), _sql.size());

		}//Qurey

		ResultSet* MySQL::Qurey(const char *_sql, int _size UNUSED){

			stringstream msg;

			try{

				if(conn_->isClosed()){

					Connect();

				}

				rstset_ = stmt_->executeQuery(_sql);

				if(NULL == rstset_){

					msg.str("");

					msg << "Lookup failed: sql=" << sql_;

					throw std::runtime_error(msg.str());
				}

				return rstset_;

			}
			catch(sql::SQLException &e){

				Error("Update runtime error: errstr=%s", e.what());

				return NULL;
			}
			catch (std::runtime_error &e) {

				Error("Lookup runtime error: errstr=%s", e.what());

				return NULL;

			}

		}//Qurey

		ResultSet* MySQL::Qurey(PreparedStatement* _ps){
			
			assert(NULL != _ps);

			try{


			}
			catch(sql::SQLException &e){

				Error("Qurey runtime error: errstr=%s", e.what());

				return NULL;

			}
			catch (std::runtime_error &e) {

				Error("Lookup runtime error: errstr=%s", e.what());

				return NULL;

			}
			
		}

	}//DB

}//PWRD
