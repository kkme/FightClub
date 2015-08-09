#include <Player.hpp>

namespace PWRD{

	namespace FC{

		/*=============================================================
		 * @private:
		 ==============================================================*/
		
		/*=============================================================
		 * @protected:
		 ==============================================================*/
		int Player::init(){

			return 1;

		} //init

		int Player::fini(){

			return 1;

		} //fini

		/*=============================================================
		 * @public:
		 ==============================================================*/
		Player::Player(string _roleid, string _rolename, int _pklevel, int _pkexp, int _ranklevel, int _rankexp, int _pkwin, int _pktotal, int _rankwin, int _ranktotal, int _money, int _gold, String* _item, String* _equip, String* _buff, String* _friend){
			
			get<ROLEID_INDEX>(player_f_t_) = _roleid;//roleid

			get<ROLENAME_INDEX>(player_f_t_) = _rolename; //rolename

			get<PKLEVEL_INDEX>(player_f_t_) = _pklevel;//pklevel

			get<PKEXP_INDEX>(player_f_t_) = _pkexp; //pkexp

			get<RANKLEVEL_INDEX>(player_f_t_) = _ranklevel; //ranklevel

			get<RANKEXP_INDEX>(player_f_t_) = _rankexp; //rankexp

			get<PKWIN_INDEX>(player_f_t_) = _pkwin; //pkwin

			get<PKTATOL_INDEX>(player_f_t_) = _pktotal; //pktatol

			get<RANKWIN_INDEX>(player_f_t_) = _rankwin; //rankwin

			get<RANKTATOL_INDEX>(player_f_t_) = _ranktotal; //ranktatol

			get<MONEY_INDEX>(player_e_t_) = _money; //money

			get<GOLD_INDEX>(player_e_t_) = _gold; //gold

			get<ITEM_INDEX>(player_e_t_) = *_item; //items

			//Note("Item=======> %s", _item->Serialize().c_str());

			get<EQUIP_INDEX>(player_e_t_) = *_equip; //equips

			//Note("Equipe=======> %s", _equip->Serialize().c_str());

			get<BUFF_INDEX>(player_e_t_) = *_buff; //buffs

			//Note("Buff=======> %s", _buff->Serialize().c_str());

			get<FRIENDS_INDEX>(player_e_t_) = *_friend; //friends

			//Note("Friend=======> %s", _friend->Serialize().c_str());

			get<DIRTY_INDEX>(player_e_t_) = false;


		} //Player

		Player::Player(const Player_F_t& _player_f_t, const Player_E_t& _player_e_t){
			
			get<ROLEID_INDEX>(player_f_t_) = _player_f_t.get<ROLEID_INDEX>(); //roleid

			get<ROLENAME_INDEX>(player_f_t_) = _player_f_t.get<ROLENAME_INDEX>(); //rolename

			get<PKLEVEL_INDEX>(player_f_t_) = _player_f_t.get<PKLEVEL_INDEX>(); //pklevel

			get<PKEXP_INDEX>(player_f_t_) = _player_f_t.get<PKEXP_INDEX>(); //pkexp

			get<RANKLEVEL_INDEX>(player_f_t_) = _player_f_t.get<RANKLEVEL_INDEX>(); //ranklevel

			get<RANKEXP_INDEX>(player_f_t_) = _player_f_t.get<RANKEXP_INDEX>(); //rankexp

			get<PKWIN_INDEX>(player_f_t_) = _player_f_t.get<PKWIN_INDEX>(); //pkwin

			get<PKTATOL_INDEX>(player_f_t_) = _player_f_t.get<PKTATOL_INDEX>(); //pktatol

			get<RANKWIN_INDEX>(player_f_t_) = _player_f_t.get<RANKWIN_INDEX>(); //rankwin

			get<RANKTATOL_INDEX>(player_f_t_) = _player_f_t.get<RANKTATOL_INDEX>(); //ranktatol

			get<MONEY_INDEX>(player_e_t_) = _player_e_t.get<MONEY_INDEX>(); //money

			get<GOLD_INDEX>(player_e_t_) = _player_e_t.get<GOLD_INDEX>(); //gold

			get<ITEM_INDEX>(player_e_t_) = _player_e_t.get<ITEM_INDEX>(); //items

			get<EQUIP_INDEX>(player_e_t_) = _player_e_t.get<EQUIP_INDEX>(); //equips

			get<BUFF_INDEX>(player_e_t_) = _player_e_t.get<BUFF_INDEX>(); //buffs

			get<FRIENDS_INDEX>(player_e_t_) = _player_e_t.get<FRIENDS_INDEX>(); //friends

			get<DIRTY_INDEX>(player_e_t_) = false;

		} //Player

	} //FC

}//PWRD
