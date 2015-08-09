#include <ItemCenter.hpp>

namespace PWRD{

	namespace FC{


		/*=========================================================
		 * @private
		 =========================================================*/
		ItemList ItemCenter::list_;
		ItemCenter* ItemCenter::instance_ = NULL;

		/*=========================================================
		 * @public
		 =========================================================*/
		ItemCenter* ItemCenter::Instance(){

			if(NULL == instance_){

				instance_ = new ItemCenter();

			}

			return instance_;
		}

		int ItemCenter::GetItemType(const string& _itemid){
			
			if(list_.end() == list_.find(_itemid)){

				Error("Can't Find this Item: itemid=%s", _itemid.c_str());

				return -1;

			}

			Item_t item_t = list_[_itemid];

			return boost::tuples::get<ITEMTYPE>(item_t);

		} //GetItemType

		int ItemCenter::GetPriceMoney(const string& _itemid){
			
			if(list_.end() == list_.find(_itemid)){

				Error("Can't Find this Item: itemid=%s", _itemid.c_str());

				return -1;

			}

			Item_t item_t = list_[_itemid];

			return boost::tuples::get<PRICEMONEY>(item_t);

		} //GetPriceCash

		int ItemCenter::GetPriceGold(const string& _itemid){
			
			if(list_.end() == list_.find(_itemid)){

				Error("Can't Find this Item: itemid=%s", _itemid.c_str());

				return -1;

			}

			Item_t item_t = list_[_itemid];

			return boost::tuples::get<PRICEGOLD>(item_t);

		} //GetPriceGold

		void ItemCenter::Load(const string& _file){
			
			ifstream is(_file.c_str(), ios::in);

			ptree pt;
			json_parser::read_json(is, pt);

			BOOST_FOREACH(const boost::property_tree::ptree::value_type& v, pt){


				Item_t item_t;

				boost::tuples::get<ITEMTYPE>(item_t) = v.second.get<int>("itemType");

				boost::tuples::get<PRICEMONEY>(item_t) = v.second.get<int>("price_cash");

				boost::tuples::get<PRICEGOLD>(item_t) = v.second.get<int>("price_gold");

				list_[v.second.get<std::string>("ID")] = item_t;

			} //BOOST_FOREACH

		} //Load

		void ItemCenter::Print(){

			ItemList::iterator it = list_.begin();

			for(; it != list_.end(); it++){
				
				Error("ID: %s,  itemType: %d, price_money: %d, price_gold: %d", it->first.c_str(), it->second.get<ITEMTYPE>(), it->second.get<PRICEMONEY>(), it->second.get<PRICEGOLD>());

			}
			
		} //Print

	} //FC

} //PWRD
