#include <BitMap.hpp>

namespace PWRD{

	namespace Utils{
		/*=================================================
		 *@private
		 ==================================================*/
		BitMap* BitMap::instance_ = NULL;

		bitset BitMap::bitset_;

		/*=================================================
		 *@protected
		 ==================================================*/
		int BitMap::init(){

			bitset_.reset();

			return 1;

		}

		int BitMap::fini(){

			return 1;
		}


		/*=================================================
		 *@public	
		 ==================================================*/

		BitMap* BitMap::Instance(){

			if(NULL == instance_){
			
				instance_ = new BitMap();

				assert(NULL != instance_);
			
			} //if

			return instance_;
		
		}
		void BitMap::Clear(){

			bitset_.reset();
		
		} //Clear

		bool BitMap::SetBit(int _index){

			if(MAXBITSIZE <= _index){
			
				Error("Beyond BitMap's Size: total=%d, current=%d", MAXBITSIZE, _index);
				return false;
			}

			bitset_.set(_index);

			return true;
		
		} //SetBit

		bool BitMap::ClearBit(int _index){

			if(MAXBITSIZE <= _index){
			
				Error("Beyond BitMap's Size: total=%d, current=%d", MAXBITSIZE, _index);
				return false;
			}

			bitset_.reset(_index);

			return true;
		
		
		} //ClearBit

		int  BitMap::IsSet(int _index){

			if(MAXBITSIZE <= _index){
			
				Error("Beyond BitMap's Size: total=%d, current=%d", MAXBITSIZE, _index);
				return false;
			}

			return bitset_[_index];
		
		} //IsSet

	}//Utils

}//PWRD
