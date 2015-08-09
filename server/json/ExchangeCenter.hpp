#ifndef __EXCHANGE_HPP
#define __EXCHANGE_HPP
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


		typedef boost::tuple<string, int, int, int, int> Exchange_t;

		typedef map<string, Exchange_t> ExchangeList;

		class ExchangeCenter{

			typedef enum{

				ITEMTYPE = 0,
				PRICEMONEY, 
				PRICEGOLD,
				VALUEMONEY,
				VALUEGOLD


			}ITEMCENTER_TYPE;

			public:
			static ExchangeCenter* Instance();

			static string GetItemType(const string& _itemid);

			static int GetPriceMoney(const string& _itemid);

			static int GetPriceGold(const string& _itemid);

			static int GetValueMoney(const string& _itemid);

			static int GetValueGold(const string& _itemid);

			static void Load(const string& _file);

			static void Print();

			static int Size(){ return list_.size(); };

			private:

			static ExchangeList list_;

			static ExchangeCenter* instance_;

		}; //ExchangeCenter

	} //FC

} //PWRD
#endif
