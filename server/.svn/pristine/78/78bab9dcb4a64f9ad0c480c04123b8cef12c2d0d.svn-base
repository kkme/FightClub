#ifndef __STRING_HPP
#define __STRING_HPP

#include <Mutex.hpp>

#include <Daemon.hpp>

#include <Global.hpp>

#include <Element.pb.h>

#include <StringTool.hpp>

#include <boost/tokenizer.hpp> 

using namespace PWRD;

using namespace PWRD::IPC;

using namespace PWRD::Utils;

namespace PWRD{

	namespace FC{

		typedef boost::tokenizer<boost::char_separator<char> >  tokenizer;

		class String{

			public:

				String(Element_ELEMENT_TYPE _type = Element_ELEMENT_TYPE_NULL_TYPE , const char* _str = ""):type_(_type), str_(_str){ init(); }

				String(Element_ELEMENT_TYPE _type, const string& _str):type_(_type), str_(_str){ init(); };

				~String(){ fini(); };

				void Parse();

				Element* Get(){ return &ele_; };

				string Str(){ return str_; }

				string Serialize();

				//Getter
				string GetKeys();

				string GetKeys(int _num);

				string GetKeys(int index, int _num);

				int GetTotal(const string& _key);

				int GetUse(const string& _key);

				//Setter
				void SetTotal(const string& _key, int _total);

				void SetUse(const string& _key, int _use);


			protected:

				int init();

				int fini();

			private:

				Element_ELEMENT_TYPE type_;

				string str_;

				Element ele_;

				Mutex mutex_;

		}; //String

	} //FC

} //PWRD

#endif
