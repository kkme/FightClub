#include <FileTools.hpp>

namespace PWRD{

	namespace Utils{


		char FileTools::buf_[BUFSIZ];

		
		/*
		 * @protected
		 */

		int FileTools::init(){

			*buf_ = 0;

			return 1;

		}

		int FileTools::fini(){

			return 1;

		}
	
		/*
		 * @public
		 */
		FileTools::Content(string _name, string& _content){
			
			int fd = open();


		}

	}

}
