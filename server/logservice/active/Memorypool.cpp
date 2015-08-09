#include <Memorypool.hpp>

namespace PWRD{

	namespace ActiveObject{

		MemPool* Memorypool::pool_ =  NULL;

		MemPool* Memorypool::Instance(){

			if(NULL == pool_){

				pool_ = new MemPool();

			}

			return pool_;

		}

	}

}
