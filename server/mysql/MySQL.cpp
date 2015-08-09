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

			conn_ = NULL; stmt_ = NULL; pstmt_ = NULL;

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

		/*=====================================================================================
		 *  @public
		 ====================================================================================*/
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

				Error("MySQL exception: func=%s, line=%d, expno=%d, sqlstate=%s, expstr=%s",
						__func__, __LINE__, e.getErrorCode(), e.getSQLState().c_str(), e.what());

				return -1;
			}

			return 1;
		}

		/*--------------------------------------------------------------------------------
		 * @Execute
		 --------------------------------------------------------------------------------*/
		int MySQL::Execute(const string& _sql){

			return Execute(_sql.c_str(), _sql.size());

		}

		int MySQL::Execute(const char *_sql, int _size UNUSED){

			try{
				if(conn_->isClosed()){

					Connect();
				}

				conn_->setAutoCommit(0);

				stmt_->execute(_sql);

				conn_->commit();

				return 1;

			}
			catch(sql::SQLException &e){

				conn_->rollback();

				Error("MySQL exception: func=%s, line=%d, expno=%d, sqlstate=%s, expstr=%s",
						__func__, __LINE__, e.getErrorCode(), e.getSQLState().c_str(), e.what());

				return -1;

			}

		}//Execute

		/*--------------------------------------------------------------------------------
		 * @Update
		 --------------------------------------------------------------------------------*/

		int MySQL::Update(const string& _sql){

			return Update(_sql.c_str(), _sql.size());

		}//Update


		int MySQL::Update(const char *_sql, int _size UNUSED){

			stringstream msg;

			int affected_rows = 0;

			try{

				if(conn_->isClosed()){

					Connect();

				}

				conn_->setAutoCommit(0);

				affected_rows = stmt_->executeUpdate(_sql);

				Trace("TRACE update indicates %d affected rows", affected_rows);

				if(-1 == affected_rows){

					msg.str("");

					msg << "update failed: sql=" << _sql;

					throw std::runtime_error(msg.str());

				}

				conn_->commit();

			}	
			catch(sql::SQLException &e){

				conn_->rollback();

				Error("MySQL exception: func=%s, line=%d, expno=%d, sqlstate=%s, expstr=%s",
						__func__, __LINE__, e.getErrorCode(), e.getSQLState().c_str(), e.what());

				return -1;

			}
			catch (std::runtime_error &e) {

				conn_->rollback();

				Error("Update runtime error: errstr=%s", e.what());

				return -1;
			}

			return 1;

		}//Update

		int MySQL::Update(PreparedStatement* _ps){

			int affected_rows = 0;

			try{

				if(conn_->isClosed()){

					Connect();

				}

				conn_->setAutoCommit(0);

				affected_rows = _ps->executeUpdate();

				conn_->commit();



			}	
			catch(sql::SQLException &e){

				conn_->rollback();

				Error("MySQL exception: func=%s, line=%d, expno=%d, sqlstate=%s, expstr=%s",
						__func__, __LINE__, e.getErrorCode(), e.getSQLState().c_str(), e.what());

				return -1;

			}
			catch (std::runtime_error &e) {

				conn_->rollback();

				Error("Update runtime error: errstr=%s", e.what());

				return -1;
			}

			return affected_rows;

		}//Update

		int MySQL::Update(StringList* _list){

			assert(NULL != _list);

			try{

				if(conn_->isClosed()){

					Connect();

				}

				conn_->setAutoCommit(0);

				StringList::iterator it = _list->begin();

				for(; it != _list->end(); it++){

					PreparedStatement* pstmt = conn_->prepareStatement(*it);

					assert(pstmt);

					pstmt->executeUpdate();

				}

				conn_->commit();


			}	
			catch(sql::SQLException &e){

				conn_->rollback();

				Error("MySQL exception: func=%s, line=%d, expno=%d, sqlstate=%s, expstr=%s",
						__func__, __LINE__, e.getErrorCode(), e.getSQLState().c_str(), e.what());

				return -1;

			}
			catch (std::runtime_error &e) {

				conn_->rollback();

				Error("Update runtime error: errstr=%s", e.what());

				return -1;
			}

			return 1;


		} //Update List


		int MySQL::Update(PSList* _list){

			assert(NULL != _list);

			try{

				Note("=================>Size:%d<================", _list->size());

				if(conn_->isClosed()){

					Connect();

				}

				conn_->setAutoCommit(0);

				int index = 0;

				PSList::iterator it = _list->begin();

				for(; it != _list->end(); it++, index++){

					(*it)->executeUpdate();

					Note("================> %d <=================", index);

				}

				conn_->commit();


			}	
			catch(sql::SQLException &e){

				conn_->rollback();

				Error("MySQL exception: func=%s, line=%d, expno=%d, sqlstate=%s, expstr=%s",
						__func__, __LINE__, e.getErrorCode(), e.getSQLState().c_str(), e.what());

				return -1;

			}
			catch (std::runtime_error &e) {

				conn_->rollback();

				Error("Update runtime error: errstr=%s", e.what());

				return -1;
			}

			return 1;


		} //Update PSList

		ResultSet* MySQL::Update(PreparedStatement* _p1, PreparedStatement* _p2){

			assert(NULL != _p1 && NULL != _p2);
		
			ResultSet* result = NULL;

			try{

				if(conn_->isClosed()){

					Connect();

				}

				conn_->setAutoCommit(0);

				_p1->executeUpdate();

				result = _p2->executeQuery();

				conn_->commit();


			}	
			catch(sql::SQLException &e){

				conn_->rollback();

				Error("MySQL exception: func=%s, line=%d, expno=%d, sqlstate=%s, expstr=%s",
						__func__, __LINE__, e.getErrorCode(), e.getSQLState().c_str(), e.what());
				return NULL;

			}
			catch (std::runtime_error &e) {

				conn_->rollback();

				Error("Update runtime error: errstr=%s", e.what());

				return NULL;
			}

			return result;

		}

		/*--------------------------------------------------------------------------------
		 * @Close	
		 --------------------------------------------------------------------------------*/
		int MySQL::Close(){

			return 1;

		}

		/*--------------------------------------------------------------------------------
		 * @Query
		 --------------------------------------------------------------------------------*/
		ResultSet* MySQL::Query(const string& _sql){


			return Query(_sql.c_str(), _sql.size());

		}//Query

		ResultSet* MySQL::Query(const char *_sql, int _size UNUSED){

			stringstream msg;

			try{

				if(conn_->isClosed()){

					Connect();

				}

				rstset_ = stmt_->executeQuery(_sql);

				if(NULL == rstset_){

					msg.str("");

					msg << "Lookup failed: sql=" << _sql;

					throw std::runtime_error(msg.str());
				}

				return rstset_;

			}
			catch(sql::SQLException &e){

				Error("MySQL exception: func=%s, line=%d, expno=%d, sqlstate=%s, expstr=%s",
						__func__, __LINE__, e.getErrorCode(), e.getSQLState().c_str(), e.what());

				return NULL;
			}
			catch (std::runtime_error &e) {

				Error("Lookup runtime error: errstr=%s", e.what());

				return NULL;

			}

		}//Query

		ResultSet* MySQL::Query(PreparedStatement* _ps){

			assert(NULL != _ps);

			try{

				return _ps->executeQuery();

			}
			catch(sql::SQLException &e){

				Error("MySQL exception: func=%s, line=%d, expno=%d, sqlstate=%s, expstr=%s",
						__func__, __LINE__, e.getErrorCode(), e.getSQLState().c_str(), e.what());

				return NULL;

			}
			catch (std::runtime_error &e) {

				Error("Lookup runtime error: errstr=%s", e.what());

				return NULL;

			}

		}

		PreparedStatement* MySQL::Get(const string& _qurey){

			try{

				PreparedStatement* pstmt = conn_->prepareStatement(_qurey);

				assert(NULL != pstmt);

				return pstmt;


			}
			catch(sql::SQLException &e){

				Error("MySQL exception: func=%s, line=%d, expno=%d, sqlstate=%s, expstr=%s",
						__func__, __LINE__, e.getErrorCode(), e.getSQLState().c_str(), e.what());

				return NULL;

			}
			catch (std::runtime_error &e) {

				Error("Lookup runtime error: errstr=%s", e.what());

				return NULL;

			}

		}


	}//DB

}//PWRD
