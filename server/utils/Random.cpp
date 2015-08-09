#include <Random.hpp>

namespace PWRD{


	namespace Utils{

		int Random::size_ = 0;
		
		random_device Random::rd_;

		Random* Random::instance_ = NULL;


		/*=================================================
		 *@protected
		 ==================================================*/
		int Random::init(){

			return 1;

		}

		int Random::fini(){

			return 1;
		}

		/*=================================================
		 *@public	
		 ==================================================*/
		int Random::Generate(int _size){

			std::mt19937 gen(rd_);

			return uniform_int_distribution<> dis_(0, _size);

		} //Generate

	}//Utils


}//PWRD
