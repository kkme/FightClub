CREATE TABLE `UserTable` (
  `RoleID` int(11) NOT NULL auto_increment,
  `UUID` char(20) NOT NULL,
  `RoleName` char(20) NOT NULL,
  `CreateTime` char(20) NOT NULL,
  `LastLogoutTime` char(20) NOT NULL,
  `PKLevel` int(11) NOT NULL default 0,
  `PKExp` int(11) NOT NULL default 0,
  `RankLevel` int(11) NOT NULL default 0,
  `RankExp` int(11) NOT NULL default 0,
  `Money` int(11) NOT NULL default 0,
  `Gold` int(11) NOT NULL default 0,
  `CashStat` int(11) default 0,
  PRIMARY KEY  (`RoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8; 

CREATE TABLE `Item` (
  `RoleID` int(11) NOT NULL,
  `ItemList` text default NULL,
  PRIMARY KEY  (`RoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8; 

CREATE TABLE `Buff` (
  `RoleID` int(11) NOT NULL,
  `BuffList` text default NULL,
  PRIMARY KEY  (`RoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8; 

CREATE TABLE `Equipment` (
  `RoleID` int(11) NOT NULL,
  `EquipmentList` text default NULL,
  PRIMARY KEY  (`RoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8; 

CREATE TABLE `Friend` (
  `RoleID` int(11) NOT NULL,
  `FriendList` text default NULL,
  PRIMARY KEY  (`RoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8; 

CREATE TABLE `PKResult` (
  `RoleID` int(11) NOT NULL,
  `Win` int(11) NOT NULL DEFAULT 0,
  `Total` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY  (`RoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8; 

CREATE TABLE `RankResult` (
  `RoleID` int(11) NOT NULL,
  `Win` int(11) NOT NULL DEFAULT 0,
  `Total` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY  (`RoleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8; 

CREATE TABLE `Mail` (
  `ID` int not NULL auto_increment,
  `RoleID` int(11) NOT NULL,
  `SendRoleID` int(11) NOT NULL,
  `TimeStamp` char(20) NOT NULL,
  `Content` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8; 

CREATE VIEW RankTop AS SELECT RoleID, RankExp FROM UserTable ORDER BY RankExp DESC LIMIT 100;

CREATE VIEW PKTop AS SELECT RoleID, PKExp FROM UserTable ORDER BY PKExp DESC LIMIT 100;

CREATE TABLE `BillTable` (
  `ID` int(11) NOT NULL auto_increment,
  `RoleID` int(11) NOT NULL,
  `Time` char(20) NOT NULL,
  `ItemID` varchar(20) NOT NULL,
  `Num` int(11) NOT NULL default 0,
  `BuyType` int(11) NOT NULL default 0,
  `Point` int(11) NOT NULL default 0,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8; 
