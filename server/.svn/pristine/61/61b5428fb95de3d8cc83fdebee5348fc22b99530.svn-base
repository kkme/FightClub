#include <SQLDef.hpp>

namespace PWRD{

		namespace DB{

				/*=============================================================
				 * @private
				 ==============================================================*/
				SQLMap SQLDef::map_;

				SQLDef* SQLDef::instance_ = NULL;

				/*=============================================================
				 * @protected
				 ==============================================================*/
				int SQLDef::init(){

						map_[INIT_MAX] = "SELECT MAX(RoleID) FROM UserTable;";

						//map_[INIT_USER] = "INSERT INTO UserTable(UUID, RoleName, CreateTime, LastLogoutTime) VALUES(?, ?, ?, ?) ON DUPLICATE KEY UPDATE RoleName=?, CreateTime=?, LastLogoutTime=?;";
						
						map_[INIT_USER] = "INSERT INTO UserTable(UUID, RoleName, CreateTime, LastLogoutTime) VALUES(?, ?, ?, ?);";

						map_[INIT_ITEM] = "INSERT INTO Item(RoleID, ItemList) VALUES(?, ?);";

						map_[INIT_EQUIP] = "INSERT INTO Equipment(RoleID, EquipmentList) VALUES(?, ?); ";

						map_[INIT_BUFF] = "INSERT INTO Buff(RoleID, BuffList) VALUES(?, ?); ";

						map_[INIT_FRIEND] = "INSERT INTO Friend(RoleID) VALUES(?);";

						map_[INIT_PK] = "INSERT INTO PKResult(RoleID) VALUES(?); ";

						map_[INIT_RANK] = "INSERT INTO RankResult(RoleID) VALUES(?); ";

						map_[SELECT_USER] = "SELECT UserTable.RoleName, UserTable.PKLevel, UserTable.PKExp, UserTable.RankLevel, UserTable.RankExp, PKResult.Win, PKResult.Total, RankResult.Win, RankResult.Total, UserTable.Money, UserTable.Gold, UserTable.CashStat, Item.ItemList, Equipment.EquipmentList, Buff.BuffList, Friend.FriendList FROM UserTable, PKResult, RankResult, Item, Equipment, Buff, Friend WHERE PKResult.RoleID = UserTable.RoleID AND RankResult.RoleID = UserTable.RoleID AND Item.RoleID = UserTable.RoleID AND Equipment.RoleID = UserTable.RoleID AND Buff.RoleID = UserTable.RoleID AND Friend.RoleID = UserTable.RoleID AND UserTable.RoleID = ?;";

						map_[UPDATE_PKEXP] = "UPDATE UserTable SET PKExp=? WHERE RoleID = ?;";

						map_[UPDATE_PKLEVEL] = "UPDATE UserTable SET PKLevel=? WHERE RoleID = ?; ";

						map_[UPDATE_RANKEXP] = "UPDATE UserTable SET RankExp=? WHERE RoleID = ?; ";

						map_[UPDATE_RANKLEVEL] = "UPDATE UserTable SET RankLevel=? WHERE RoleID = ?; ";

						map_[UPDATE_MONEY] = "UPDATE UserTable SET Money=? WHERE RoleID = ?; ";

						map_[UPDATE_GOLD] = "UPDATE UserTable SET Gold=? WHERE RoleID = ?; ";

						map_[UPDATE_CASHSTAT] = "UPDATE UserTable SET CashStat=CashStat+? WHERE RoleID = ?; ";

						map_[UPDATE_LASTLOGOUT] = "UPDATE UserTable SET LastLogoutTime=? WHERE RoleID = ?; ";
						
						map_[UPDATE_ITEM] = "UPDATE Item SET ItemList=? WHERE RoleID = ?; ";

						map_[UPDATE_EQUIP] = "UPDATE Equipment SET EquipmentList=? WHERE RoleID = ?; ";

						map_[UPDATE_BUFF] = "UPDATE Buff SET BuffList=? WHERE RoleID = ?; ";

						map_[UPDATE_FRIEND] = "UPDATE Friend SET FriendList=? WHERE RoleID = ?;";

						map_[UPDATE_PKWIN] = "UPDATE PKResult SET Win=Win+1, Total=Total+1 WHERE RoleID = ?; ";

						map_[UPDATE_PKLOST] = "UPDATE PKResult SET Total=Total+1 WHERE RoleID = ?; ";

						map_[UPDATE_RANKWIN] = "UPDATE RankResult SET Win=Win+1, Total=Total+1 WHERE RoleID = ?; ";

						map_[UPDATE_RANKLOST] = "UPDATE RankResult SET Total=Total+1 WHERE RoleID = ?; ";

						map_[INSERT_BILL] = "INSERT INTO BillTable(RoleID, Time, ItemID, Num, BuyType, Point) VALUES(?, ?, ?, ?, ?, ?);";


						return 1;

				} //init

				int SQLDef::fini(){

						return 1;

				} //fini


				/*=============================================================
				 * @public
				 ==============================================================*/
				SQLDef* SQLDef::Instance(){

						if(NULL == instance_){

								instance_ = new SQLDef();

						}

						return instance_;
				}

				SQLVector SQLDef::Get(){
					
					SQLVector vect;

					vect.push_back(map_[INIT_USER]);
					vect.push_back(map_[INIT_ITEM]);
					vect.push_back(map_[INIT_EQUIP]);
					vect.push_back(map_[INIT_BUFF]);
					vect.push_back(map_[INIT_FRIEND]);
					vect.push_back(map_[INIT_PK]);
					vect.push_back(map_[INIT_RANK]);

					return vect;

				}

				string SQLDef::Get(GAMERSQL _type){
				
						return map_[_type];

				} //Get


		} //DB

} //PWRD
