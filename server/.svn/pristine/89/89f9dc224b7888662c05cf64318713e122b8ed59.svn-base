#ifndef __ITEMCENTER_HPP
#define __ITEMCENTER_HPP

#include <Global.hpp>
#include <Daemon.hpp>
#include <StringTool.hpp>
#include <boost/foreach.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp> 

using namespace std;
using namespace PWRD;
using namespace PWRD::Utils;
using namespace boost::property_tree;

namespace PWRD{

	namespace FC{

		typedef enum{

			ITEMTYPE = 0,
			PRICEMONEY, 
			PRICEGOLD

		}ITEMCENTER_TYPE;

		typedef boost::tuple<int, int, int> Item_t;

		typedef map<string, Item_t> ItemList;

		class ItemCenter{

			public:
				static ItemCenter* Instance();

				static int GetItemType(const string& _itemid);

				static int GetPriceMoney(const string& _itemid);

				static int GetPriceGold(const string& _itemid);

				static void Load(const string& _file);

				static void Print();

				static int Size(){ return list_.size(); };

			private:

				static ItemList list_;

				static ItemCenter* instance_;

		}; //ItemCenter

	} //FC

} //PWRD

#endif
