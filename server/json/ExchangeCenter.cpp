#include <ExchangeCenter.hpp>

namespace PWRD{

	namespace FC{


		/*=========================================================
		 * @private
		 =========================================================*/
		ExchangeList ExchangeCenter::list_;
		ExchangeCenter* ExchangeCenter::instance_ = NULL;

		/*=========================================================
		 * @public
		 =========================================================*/
		ExchangeCenter* ExchangeCenter::Instance(){

			if(NULL == instance_){

				instance_ = new ExchangeCenter();

			}

			return instance_;
		}

		string ExchangeCenter::GetItemType(const string& _itemid){
			
			if(list_.end() == list_.find(_itemid)){

				Error("Can't Find this Exchange: itemid=%s", _itemid.c_str());

				return "";

			}

			Exchange_t item_t = list_[_itemid];

			return boost::tuples::get<ITEMTYPE>(item_t);

		} //GetExchangeType

		int ExchangeCenter::GetPriceMoney(const string& _itemid){
			
			if(list_.end() == list_.find(_itemid)){

				Error("Can't Find this Exchange: itemid=%s", _itemid.c_str());

				return -1;

			}

			Exchange_t item_t = list_[_itemid];

			return boost::tuples::get<PRICEMONEY>(item_t);

		} //GetPriceCash

		int ExchangeCenter::GetPriceGold(const string& _itemid){
			
			if(list_.end() == list_.find(_itemid)){

				Error("Can't Find this Exchange: itemid=%s", _itemid.c_str());

				return -1;

			}

			Exchange_t item_t = list_[_itemid];

			return boost::tuples::get<PRICEGOLD>(item_t);

		} //GetPriceGold

		int ExchangeCenter::GetValueMoney(const string& _itemid){
			
			if(list_.end() == list_.find(_itemid)){

				Error("Can't Find this Exchange: itemid=%s", _itemid.c_str());

				return -1;

			}

			Exchange_t item_t = list_[_itemid];

			return boost::tuples::get<VALUEMONEY>(item_t);

		} //GetPriceCash

		int ExchangeCenter::GetValueGold(const string& _itemid){
			
			if(list_.end() == list_.find(_itemid)){

				Error("Can't Find this Exchange: itemid=%s", _itemid.c_str());

				return -1;

			}

			Exchange_t item_t = list_[_itemid];

			return boost::tuples::get<VALUEGOLD>(item_t);

		} //GetPriceGold
		void ExchangeCenter::Load(const string& _file){
			
			ifstream is(_file.c_str(), ios::in);

			ptree pt;
			json_parser::read_json(is, pt);

			BOOST_FOREACH(const boost::property_tree::ptree::value_type& v, pt){


				Exchange_t item_t;

				boost::tuples::get<ITEMTYPE>(item_t) = v.second.get<string>("itemType");

				boost::tuples::get<PRICEMONEY>(item_t) = v.second.get<int>("price_dollor");

				boost::tuples::get<PRICEGOLD>(item_t) = v.second.get<int>("price_gold");

				boost::tuples::get<VALUEMONEY>(item_t) = v.second.get<int>("value_cash");

				boost::tuples::get<VALUEGOLD>(item_t) = v.second.get<int>("value_gold");

				list_[v.second.get<std::string>("ID")] = item_t;

			} //BOOST_FOREACH

		} //Load

		void ExchangeCenter::Print(){

			ExchangeList::iterator it = list_.begin();

			for(; it != list_.end(); it++){
				
				Error("ID: %s,  itemType: %s, price_dollor: %d, price_gold: %d, value_cash: %d, value_gold: %d", it->first.c_str(), it->second.get<ITEMTYPE>().c_str(), it->second.get<PRICEMONEY>(), it->second.get<PRICEGOLD>(), it->second.get<VALUEMONEY>(), it->second.get<VALUEGOLD>());

			}
			
		} //Print

	} //FC

} //PWRD
