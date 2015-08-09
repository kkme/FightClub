#include <Sequnce.hpp>

namespace PWRD{


	namespace Utils{

		int Sequnce::size_ = 0;

		BitMap* Sequnce::bitmap_ = NULL;

		Sequnce* Sequnce::instance_ = NULL;

		/*=================================================
		 *@protected
		 ==================================================*/
		int Sequnce::init(){

			bitmap_ = new BitMap();

			return 1;

		}

		int Sequnce::fini(){

			delete bitmap_;

			return 1;
		}

		/*=================================================
		 *@public	
		 ==================================================*/

		void Sequnce::Start(){

			bitmap_->Clear();

		}

		int Sequnce::Generate(int _size){

			int res = 0;

			do{

				res = rand() % _size;

			}while(bitmap->IsSet(res));

			Note("Generate random: rand=%d", res);

			return res;


		}

	}//Utils


}//PWRD
