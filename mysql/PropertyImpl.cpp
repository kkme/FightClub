#include <PropertyImpl.hpp>

namespace PWRD{

	namespace DB{

		PWRD::DB::MySQL* PropertyImpl::mysql_ = NULL;

		PropertyImpl* PropertyImpl::instance_ = NULL;

		/*===============================================================
		 * @protected
		 ===============================================================*/
		int PropertyImpl::init(){

			Conf* conf = Conf::GetInstance();

			assert(NULL != conf);

			string user = conf->find("DataBase", "user");

			string pass = conf->find("DataBase", "pass");

			string name = conf->find("DataBase", "name");

			mysql_ = new MySQL(user, pass, name);

			assert(NULL != mysql_);

			mysql_->Connect();

			return 1;

		}

		int PropertyImpl::fini(){

			delete mysql_;

			delete instance_;

			return 1;

		}

		/*===============================================================
		 * @public
		 ===============================================================*/
		void PropertyImpl::Print(Property* _pro){

			assert(NULL != _pro);

			Note("Property member: uid=%s", _pro->uid().c_str());
			Note("Property member: name=%s", _pro->name().c_str());
			Note("Property member: hp=%d", _pro->hp());
			Note("Property member: rank=%d", _pro->rank());
			Note("Property member: faint=%d", _pro->faint());
			Note("Property member: dress.id=%d", _pro->dress().id());
			Note("Property member: prop.id=%d", _pro->prop().id());
			Note("Property member: energy=%d", _pro->energy().id());

		}

		Property* PropertyImpl::Get(string _uid){

			Conf* conf = Conf::GetInstance();

			string pro = conf->find("DataBase", "Property");

			Trace("SQL property: sql=%s", pro.c_str());

			sql::PreparedStatement *pstmt = sql::PreparedStatement(pro);

			pstmt->SetString(1, _uid);

			sql::ResultSet* res = mysql_->Qurey(pstmt);

			if(NULL != res){


				Property* property = new Property();

				assert(NULL != property);


				//set property
				property->set_uid(_uid);
				property->set_hp(res->getInt("hp"));
				property->set_rank(res->getInt("rank"));
				property->set_faint(res->getInt("faint"));
				property->dress().set_id(res->getInt("dress_id"));
				property->dress().set_defense(res->getInt("dress_defens"));
				property->prop().set_id(res->getInt("prop_id"));
				property->prop().set_harm(res->getInt("harm"));
				property->energy().set_id(res->getInt("energy_id"));
				property->energy().set_defense(res->getInt("energy_defense"));
				property->energy().set_addhp(res->getInt("addhp"));

				delete pstmt;

				return property;

			}//ResultSet

			Error("Can't find this user: uid=%s", _uid.c_str());

			return NULL;
		}//Get


	}//DB

}//PWRD
