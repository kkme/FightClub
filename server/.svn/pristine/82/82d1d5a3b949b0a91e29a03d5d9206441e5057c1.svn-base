--------------------------------init a player---------------------------------
INSERT INTO UserTable(UUID, RoleName, CreateTime, LastLogoutTime) VALUES(?, ?, ?, ?) ON DUPLICATE KEY UPDATE RoleName=?, CreateTime=?, LastLogoutTime=?;
INSERT INTO Item(RoleID, ItemList) VALUES(?, ?);
INSERT INTO Equipment(RoleID, EquipmentList) VALUES(?, ?);
INSERT INTO Buff(RoleID, BuffList) VALUES(?, ?);
INSERT INTO Friend(RoleID, FriendList) VALUES(?, ?);
INSERT INTO PKResult(RoleID) VALUES(?);
INSERT INTO RankResult(RoleID) VALUES(?);
--------------------------------select a player---------------------------------
SELECT UserTable.RoleName, UserTable.PKLevel, UserTable.PKExp, UserTable.RankLevel, UserTable.RankExp, PKResult.Win, PKResult.Total, RankResult.Win, RankResult.Total, UserTable.Money, UserTable.Gold, UserTable.CashStat, Item.ItemList, Equipment.EquipmentList, Buff.BuffList, Friend.FriendList FROM UserTable, PKResult, RankResult, Item, Equipment, Buff, Friend WHERE PKResult.RoleID = UserTable.RoleID AND RankResult.RoleID = UserTable.RoleID AND Item.RoleID = UserTable.RoleID AND Equipment.RoleID = UserTable.RoleID AND Buff.RoleID = UserTable.RoleID AND Friend.RoleID = UserTable.RoleID AND UserTable.RoleID = ?;
--------------------------------update player's PKLevel---------------------------------
UPDATE UserTable SET PKLevel=? WHERE RoleID = ?;
--------------------------------update player's PKExp---------------------------------
UPDATE UserTable SET PKExp=? WHERE RoleID = ?;
--------------------------------update player's RankLevel---------------------------------
UPDATE UserTable SET RankLevel=? WHERE RoleID = ?;
--------------------------------update player's RankExp---------------------------------
UPDATE UserTable SET RankExp=? WHERE RoleID = ?;
--------------------------------update player's Money---------------------------------
UPDATE UserTable SET Money=? WHERE RoleID = ?;
--------------------------------update player's Gold---------------------------------
UPDATE UserTable SET Gold=? WHERE RoleID = ?;
--------------------------------update player's CashStat---------------------------------
UPDATE UserTable SET CashStat=CashStat+? WHERE RoleID = ?;
--------------------------------update player's LastLogoutTime---------------------------------
UPDATE UserTable SET LastLogoutTime=? WHERE RoleID = ?;
--------------------------------update player's ItemList---------------------------------
UPDATE Item SET ItemList=? WHERE RoleID = ?;
--------------------------------update player's EquipmentList---------------------------------
UPDATE Equipment SET EquipmentList=? WHERE RoleID = ?;
--------------------------------update player's Buff---------------------------------
UPDATE Buff SET BuffList=? WHERE RoleID = ?;
--------------------------------update player's FriendList---------------------------------
UPDATE Friend SET FriendList=? WHERE RoleID = ?;
--------------------------------update player's PKResult Win---------------------------------
UPDATE PKResult SET Win=Win+1, Total=Total+1 WHERE RoleID = ?;
--------------------------------update player's PKResult Lost---------------------------------
UPDATE PKResult SET Total=Total+1 WHERE RoleID = ?;
--------------------------------update player's RankResult Win---------------------------------
UPDATE RankResult SET Win=Win+1, Total=Total+1 WHERE RoleID = ?;
--------------------------------update player's RankResult Lost---------------------------------
UPDATE RankResult SET Total=Total+1 WHERE RoleID = ?;

--------------------------------insert a bill--------------------------------------------------
INSERT INTO BillTable(RoleID, Time, ItemID, Num, BuyType, Point) VALUES(?, ?, ?, ?, ?, ?); 

