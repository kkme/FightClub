#ifndef __FILETOOLS_HPP
#define __FILETOOLS_HPP

#include <Global.hpp>
#include <Deamon.hpp>

using namespace PWRD;


namespace PWRD{

	namespace Utils{

		class FileTools{


			public:

				static void Content(string _name, string& _content);

			protected:

				static int init();

				static int fini();
					

			private:

				static char buf_[BUFSIZ];
		}

	}

}

#endif
