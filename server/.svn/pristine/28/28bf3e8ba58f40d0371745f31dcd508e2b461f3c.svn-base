#ifndef __SEQUNCE_HPP
#define __SEQUNCE_HPP

#include <Global.hpp>

#include <Daemon.hpp>

#include <BitMap.cpp>

using namespace PWRD;

using namespace PWRD::Utils;

namespace PWRD{

	namespace Utils{

		class Sequnce{

			public:
				
				Sequnce* Instance(){
				
					if(NULL == instance_){
					
						instance_ = new Sequnce();

					}

					return instance_;

				}


				virtual ~Sequnce(){ fini(); };

				static void Start();

				static int Generate(int _size);

			protected:

				Sequnce(){ init(); };
				
				static int init();

				static int fini();

			private:

				static int size_;

				static BitMap* bitmap_;

				static Sequnce* instance_;

		};

	}//Utils

}//PWRD

#endif
