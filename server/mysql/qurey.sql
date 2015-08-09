SELAST	 SELECT LAST_INSERT_ID()

SEUSER 	 SELECT UUID, RoleName, Level, Exp, Rank_Exp, Rank_Level, Money, Gold, CashStat FROM UserTable WHERE RoleID=?
INUSER   INSERT INTO UserTable(UUID, RoleName, CreateTime, LastLogoutTime, Level, Exp, Rank_Exp, Rank_Level, Money, Gold, CashStat)  VALUES("XXX", "XXX", ?, ?, 1, 1, 1, 1, 0, 0, 0);
UPNAME	 UPDATE UserTable SET RoleName=? WHERE RoleID=?
UPCREAT	 UPDATE UserTable SET CreateTime=? WHERE RoleID=?
UPLAST	 UPDATE UserTable SET LastLogoutTime=? WHERE RoleID=?
UPLEVEL	 UPDATE UserTable SET Level=? WHERE RoleID=?
UPEXP 	 UPDATE UserTable SET Exp=Exp+? WHERE RoleID=?
UPRANKEXP UPDATE UserTable SET Rank_Exp=Rank_Exp+? WHERE RoleID=?
UPRANKLEVEL UPDATE UserTable SET Rank_Level=Rank_Exp+? WHERE RoleID=?
UPMONEY	 UPDATE UserTable SET Money=Money+? WHERE RoleID=?
UPGOLD 	UPDATE UserTable SET Gold=Gold+? WHERE RoleID=?
UPCASH 	UPDATE UserTable SET CashStat=CashStat+? WHERE RoleID=?

SEEQLIST SELECT EquipmentList FROM Equipment WHERE RoleID=?  
INEQLIST INSERT INTO Equipment(RoleID, EquipmentList) VALUES(?, ?) ON DUPLICATE KEY UPDATE RoleID=?, EquipmentList=?

SEFRLIST SELECT FriendList FROM Friend WHERE RoleID=?  
INFRLIST INSERT INTO Friend(RoleID, FriendList) VALUES(?, ?) ON DUPLICATE KEY UPDATE RoleID=?, FriendList=?

SEPKRESULT SELECT Win, Run, Total FROM PK_Result WHERE RoleID=?  
INPKRESULTWIN INSERT INTO PK_Result(RoleID, Win, Total) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE Win=Win+1, Total=Total+1
INPKRESULTRUN INSERT INTO PK_Result(RoleID, Run, Total) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE Run=Run+1, Total=Total+1

SERANKRESULT SELECT Win, Run, Total FROM Rank_Result WHERE RoleID=?  
INRANKRESULTWIN INSERT INTO Rank_Result(RoleID, Win, Total) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE Win=Win+1, Total=Total+1
INRANKRESULTRUN INSERT INTO Rank_Result(RoleID, Run, Total) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE Run=Run+1, Total=Total+1

SEMAIL SELECT TimeStamp, Content FROM Mail WHERE RoleID=?
INMAIL INSERT INTO Mail(RoleID, SendRoleID, TimeStamp, Content) VALUES(?, ?, ?, ?)

SERANKEXP SELECT Rank_Exp FROM Rank_Top WHERE RoleID=?  
INRANKEXP INSERT INTO Rank_Top(RoleID, Rank_Exp) VALUES(?, ?) ON DUPLICATE KEY UPDATE RoleID=?, Rank_Exp=?
SERANKTOP SELECT RoleID, Rank_Exp FROM Rank_Top ORDER BY Rank_Exp LIMIT ?

SEPKEXP SELECT PK_Exp FROM PK_Top WHERE RoleID=?  
INPKEXP INSERT INTO PK_Top(RoleID, FriendList) VALUES(?, ?) ON DUPLICATE KEY UPDATE RoleID=?, FriendList=?
SEPKTOP SELECT RoleID, PK_Exp FROM PK_Top ORDER BY PK_Exp LIMIT ?


