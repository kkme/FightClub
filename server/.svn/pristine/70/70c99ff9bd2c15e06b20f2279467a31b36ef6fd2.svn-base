#include <StringTool.hpp>

namespace PWRD{

	namespace Utils{

		/*=====================================================================
		 * @public
		 ======================================================================*/

		string StringTool::Int2Str(int _value){

			string str;

			stringstream ss;

			ss << _value;

			ss >> str;

			return str;
		}//Int2Str

		int StringTool::Str2Int(const string& _str){

			int value;

			stringstream ss;

			ss << _str;

			ss >> value;

			return value;
		}//Str2Int

		string StringTool::Long2Str(long long _value){

			string str;

			stringstream ss;

			ss << _value;

			ss >> str;

			return str;
		}//Long2Str

		long long StringTool::Str2Long(const string& _str){

			long long value;

			stringstream ss;

			ss << _str;

			ss >> value;

			return value;
		}//Str2Long

		bool StringTool::Endwith(string _str, char _c){

			size_t pos = 0;

			bool endwith = false;

			if(_str.size() == (pos = _str.rfind(_c) + 1)){

				endwith = true;
			}

			return endwith;

		}//Endwith

		string StringTool::Trim(string& _str){

			string::size_type pos = _str.find_last_not_of(' ');

			if(pos != string::npos){

				_str.erase(pos + 1);

				pos = _str.find_first_not_of(' ');

				if(pos != string::npos){

					_str.erase(0, pos);
				} 
			}
			else{

				_str.erase(_str.begin(), _str.end());

			}

			return _str;

		} //Trim

		bool StringTool::ICompare(const string& _src, const string& _dst){

			if(!strcasecmp(_src.c_str(), _dst.c_str())){
				
				return true;
			
			}	

			return false;
		
		}
	}//Utils

}//PWRD
