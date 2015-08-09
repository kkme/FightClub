#ifndef __RANDOM_HPP
#define __RANDOM_HPP

#include <Global.hpp>

#include <Daemon.hpp>

#include <StringTool.hpp>

using namespace PWRD;

using namespace PWRD::Utils;

namespace PWRD{

	namespace Utils{

		class Random{

			public:
				
				static Random* Instance(){
				
					if(NULL == instance_){
					
						instance_ = new Random();

					}

					return instance_;

				}


				virtual ~Random(){ fini(); };

				static void Start();

				static int Generate(int _size);

			protected:

				Random(){ init(); };
				
				static int init();

				static int fini();

			private:

				static Random* instance_;

				static random_device rd_;

		}; //Random

	}//Utils

}//PWRD

#endif
