#ifndef __BITMAP_HPP
#define __BITMAP_HPP

#include <Global.hpp>

#include <Daemon.hpp>

using namespace PWRD;


#define MAXBITSIZE 8096

namespace PWRD{

	namespace Utils{

		class BitMap{

			public:

				static BitMap* Instance();

				virtual ~BitMap(){ fini(); }

				void Clear();

				static bool SetBit(int _index);

				static bool ClearBit(int _index);

				static bool IsSet(int _index);

			protected:

				BitMap(){ init(); }

				static int init();

				static int fini();

			private:
		
				static BitMap* instance_;

				static bitset<MAXBITSIZE> bitset_;

		}; //BitMap

	} //Utils

} //PWRD

#endif
