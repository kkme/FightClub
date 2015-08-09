#include <Experience.hpp>

using namespace PWRD{

	using namespace Game{

		/*=========================================================
		 * @private
		 =========================================================*/
		ExpMap Experience::minuemap_;

		ExpMap Experience::equalmap_;

		ExpMap Experience::classmap_;

		Experience* Experience::Instance_ = NULL;
		
		/*=========================================================
		 * @protected
		 =========================================================*/
		int Experience::init(){

			int sum = 0;

			string sumstr = "";

			Conf* conf = Conf::GetInstance();

			assert(NULL != conf);

			sumstr = conf->find("MinueExp", "sum");

			sum = StringTool::Str2Int(sumstr);

			//MinueExp
			for(int index = 1; index <= sum; index++){

				string indexstr = StringTool::Int2Str(index);

				string expstr = conf->find("MinueExp", indexstr);

				int exp = StringTool::Str2Int(expstr);

				Trace("TRACE MinueExp: index=%d <----> exp=%d", index, exp);

				minuemap_[index] = exp;
			
			} //for MinueExp

			sumstr = conf->find("EqualExp", "sum");

			sum = StringTool::Str2Int(sumstr);

			//EqualExp
			for(int index = 1; index <= sum; index++){
			
				string indexstr = StringTool::Int2Str(index);

				string expstr = conf->find("EqualExp", indexstr);

				int exp = StringTool::Str2Int(expstr);

				Trace("TRACE EqualExp: index=%d <----> exp=%d", index, exp);

				equalmap_[index] = exp;
			
			} //for EqualExp

			//ClassExp
			sumstr = conf->find("ClassExp", "sum");

			sum = StringTool::Str2Int(sumstr);

			//ClassExp
			for(int index = 1; index <= sum; index++){
			
				string indexstr = StringTool::Int2Str(index);

				string expstr = conf->find("ClassExp", indexstr);

				int exp = StringTool::Str2Int(expstr);

				Trace("TRACE ClassExp: index=%d <----> exp=%d", index, exp);

				classmap_[index] = exp;
			
			} //for ClassExp


			return 1;
		
		} //init

		int Experience::fini(){
		
			return 1;

		} //fini

		double Experience::Arccot(int _x){

			return PI/2 - atan((_x));
		
		} //Arccot

	
		/*=========================================================
		 * @public
		 =========================================================*/
		Experience* Experience::Instance(){

			if(NULL != instance_){
			
				instance_ = new Experience();
			
			}

			return instance_;
		
		} //Instance

		int Experience::Compute(int _winner, int _loser){

			if(_winner == _loser){

				int exp = (int)(minuemap_[_winner] - minuemap_[_loser])/3;

				return (int)((Arccot(exp)*PI*20 + 100)*(9*equalmap_[_winner])/10;
			
			}
			else{
				int exp = (int)(minuemap_[_winner] - minuemap_[_loser])/3;

				return (int)(Arccot(exp)*PI*20 + 100);
			
			}
		
		} //Compute

		int Experience::Upgrade(int _level, int _exp){

			if(classmap_[_level] <= _exp){

				return true;
			
			}

			return false;
		
		} //Upgrade
	
	} //Game

} //PWRD
