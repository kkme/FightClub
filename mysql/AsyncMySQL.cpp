#include <AsyncMySQL.hpp>

namespace PWRD{

	namespace DB{

		void AsyncQureyMySQL::Run(){

			while(request_.AsyncWait() < 0){

				continue;

			}

			string* qurey = request_.Dequeue();

			assert(qurey != NULL);

			Trace("TRACE Receive a Request: sql=%s", qurey->c_str());

			ResultSet* set = Qurey(*qurey);

			assert(set != NULL);

			response_.Enqueue(set);

			delete qurey;

		}//AsyncQureyMySQL


		void AsyncUpdateMySQL::Run(){
			
			while(request_.AsyncWait() < 0){

				continue;

			}

			string* qurey = request_.Dequeue();

			assert(qurey != NULL);

			Trace("TRACE Receive a Request: sql=%s", qurey->c_str());

			Update(*qurey);

			delete qurey;


		}

	}

}
