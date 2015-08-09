#include <String.hpp>

namespace PWRD{

	namespace FC{

		/*=============================================================
		 * @protected:
		 ==============================================================*/
		int String::init(){

			Parse(); 

			return 1;

		}

		int String::fini(){

			return 1;
		}

		/*=============================================================
		 * @public:
		 ==============================================================*/
		void String::Parse(){

			ScopedLock lock(mutex_);

			boost::char_separator<char> sep(";");

			tokenizer tokens(str_, sep);

			for (tokenizer::iterator tok_iter = tokens.begin();tok_iter != tokens.end(); ++tok_iter) {

				//Trace("TRACE Split by [;]: token=%s", (*tok_iter).c_str());

				boost::char_separator<char> sep(":");

				tokenizer token(*tok_iter, sep);

				int index = 0;

				Entity* entity = ele_.add_entity();

				for (tokenizer::iterator iter = token.begin(); iter != token.end(); ++iter, index++) {


					if(0 == index){

						//Note("Key: %s", (*iter).c_str());

						entity->set_key(*iter);

					}
					else if(1 == index){

						//Note("Total: %s", (*iter).c_str());

						entity->set_total(StringTool::Str2Int(*iter));

					}
					else if(2 == index){

						//Note("Use: %s", (*iter).c_str());

						entity->set_use(StringTool::Str2Int(*iter));

					}
					else{

						Error("Illeage Fromate: str=%s", (*tok_iter).c_str());

						break;

					} //else

				} //for :

			} //for ;

			return ;

		} //Parse

		string String::Serialize(){

			stringstream ss;

			ss.clear();

			ScopedLock lock(mutex_);

			for(int index = 0; index < ele_.entity_size(); index++ ){

				Entity entity = ele_.entity(index);

				ss << entity.key();
				ss << ":";
				ss << entity.total();
				ss << ":";
				ss << entity.use();
				ss << ";";

			} //for index

			return ss.str();

		} //Serialize

		string String::GetKeys(){

			stringstream ss;

			ss.clear();

			ScopedLock lock(mutex_);

			for(int index = 0; index < ele_.entity_size(); index++ ){

				Entity entity = ele_.entity(index);
				ss << entity.key();
				ss << ";";

			} //for index

			return ss.str();

		} //GetKeys all

		string String::GetKeys(int _num){

			if(_num <= 0){

				Error("Num of Request Error: num=%d", _num);

				return "";

			} //if num

			stringstream ss;

			ss.clear();

			ScopedLock lock(mutex_);

			int step = 0;

			for(int index = 0; index < ele_.entity_size() && step < _num; index++, step++){

				Entity entity = ele_.entity(index);
				ss << entity.key();
				ss << ";";

			} //for index

			return ss.str();

		} //GetKeys num

		string String::GetKeys(int _index, int _num){

			stringstream ss;

			ss.clear();

			ScopedLock lock(mutex_);

			int step = 0;

			for(int index = 0; index < ele_.entity_size() && step < _num; index++){

				if(index >= _index){
					
					Entity entity = ele_.entity(index);
					ss << entity.key();
					ss << ";";

					step++;

				} //if begin index

			} //for index

			return ss.str();

		} //GetKeys index num

		int String::GetTotal(const string& _key){
			
			ScopedLock lock(mutex_);

			for(int index = 0; index < ele_.entity_size(); index++ ){

				Entity entity = ele_.entity(index);

				if(!_key.compare(entity.key())){

					return entity.total();
					
				}

			}

			Error("Can't Find This KEY: key=%s", _key.c_str());

			return 0;


		} //GetTotal

		int String::GetUse(const string& _key){
			
			ScopedLock lock(mutex_);

			for(int index = 0; index < ele_.entity_size(); index++ ){

				Entity entity = ele_.entity(index);

				if(!_key.compare(entity.key())){

					return entity.use();
					
				}

			}

			Error("Can't Find This KEY: key=%s", _key.c_str());

			return 0;


		} //GetUse

		void String::SetTotal(const string& _key, int _total){
			
			ScopedLock lock(mutex_);

			for(int index = 0; index < ele_.entity_size(); index++ ){

				Entity* entity = ele_.mutable_entity(index);

				if(!_key.compare(entity->key())){
					
					entity->set_total(_total);
				
					return;
				}

			}

			Error("Can't Find This KEY: key=%s", _key.c_str());


		} //SetTotal

		void String::SetUse(const string& _key, int _use){
			
			ScopedLock lock(mutex_);

			for(int index = 0; index < ele_.entity_size(); index++ ){

				Entity* entity = ele_.mutable_entity(index);

				if(!_key.compare(entity->key())){
					
					entity->set_use(_use);

					return;
					
				}

			}

			Error("Can't Find This KEY: key=%s", _key.c_str());

		} //SetUse
	} //FC

} //PWRD
