#ifndef __EXPERINCE_HPP
#define __EXPERINCE_HPP

#include <cmath.hpp>

#include <Conf.hpp>

#include <Mutex.hpp>

#include <Deamon.hpp>

#include <Global.hpp>

#include <StringTool.hpp>

using namespace PWRD;

using namespace PWRD::IPC;

#define PI 3.14159265

namespace PWRD{

	namespace Game{
	
		typedef map<int, int> ExpMap;

		class Experience{
		
			public:

				static Experience* Instance();

				virtual ~Experience(){ fini(); }

				static int Compute(int _winner, int _loser);

				static bool Upgrade(int _level, int _exp);

			protected:

				Experience(){ init(); }

				static double Arccot(int _x);

				static int init();

				static int fini();

			private:

				static ExpMap minuemap_;

				static ExpMap equalmap_;

				static ExpMap classmap_;

				static Experience* instance_;
		
		}; //Experience
	
	
	} //Game

} //PWRD

#endif

