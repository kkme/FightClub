#include <Stringpool.hpp>

namespace PWRD{

	namespace ActiveObject{

		StrPool* Stringpool::strpool_ = NULL;

		StrPool* Stringpool::Instance(){

			if(NULL == strpool_){

				strpool_ = new StrPool();

			}

			return strpool_;
		}


	}

}
