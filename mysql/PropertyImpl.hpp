#ifndef __PROPERTY_HPP
#define __PROPERTY_HPP

#include <MySQL.hpp>
#include <Packet.pb.h>
#include <AsyncMySQL.hpp>

using namespace PWRD;

using namespace PWRD::DB;

namespace PWRD{

	namespace DB{

		class PropertyImpl{

			public:

					static PropertyImpl* Instance(){ return instance_ ? instance_ : instance_ = new PropertyImpl(); }

					virtual ~PropertyImpl(){ fini(); }

					static Property* Get(string _uid);

					static void Print(Property*);

			protected:

					PropertyImpl(){ init();}

					static int init();

					static int fini();

			private:

					static PWRD::DB::MySQL* mysql_;

					static PropertyImpl* instance_;
		};

	}//DB

}//PWRD

#endif
