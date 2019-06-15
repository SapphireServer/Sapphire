
CREATE TABLE `accounts` (
  `account_id` int(11) NOT NULL DEFAULT '0',
  `account_name` varchar(255) COLLATE latin1_general_ci NOT NULL,
  `account_pass` varchar(255) COLLATE latin1_general_ci NOT NULL,
  `account_created` int(11) NOT NULL DEFAULT '0',
  `account_status` tinyint(4) NOT NULL DEFAULT '0',
   PRIMARY KEY (`account_id`),
   UNIQUE KEY `accountname` (`account_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `bnpctemplate` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `Name` varchar(32) NOT NULL,
  `bNPCBaseId` int(10) DEFAULT NULL,
  `bNPCNameId` int(10) NOT NULL,
  `mainWeaponModel` bigint(20) DEFAULT NULL,
  `secWeaponModel` bigint(20) DEFAULT NULL,
  `aggressionMode` int(3) DEFAULT NULL,
  `enemyType` int(3) DEFAULT NULL,
  `pose` int(3) DEFAULT NULL,
  `modelChara` int(5) DEFAULT NULL,
  `displayFlags` int(10) DEFAULT NULL,
  `Look` binary(26) DEFAULT NULL,
  `Models` binary(40) DEFAULT NULL,
   PRIMARY KEY (`Id`),
   KEY `templatename` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `spawnpoint` (
  `id` int(11) NOT NULL  AUTO_INCREMENT,
  `spawnGroupId` int(11) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `r` float NOT NULL,
  `gimmickId` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `spawngroupidx` (`spawnGroupId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `charainfo` (
  `AccountId` int(11) NOT NULL,
  `CharacterId` int(20) NOT NULL,
  `ContentId` bigint(20) DEFAULT NULL,
  `Name` varchar(32) CHARACTER SET latin1 COLLATE latin1_general_ci DEFAULT NULL,
  `Hp` bigint(20) DEFAULT '200',
  `Mp` bigint(20) DEFAULT '200',
  `Tp` bigint(20) DEFAULT '0',
  `Gp` bigint(20) DEFAULT '0',
  `Mode` smallint(6) DEFAULT '0',
  `Mount` smallint(6) DEFAULT '0',
  `InvincibleGM` smallint(6) DEFAULT '0',
  `Voice` smallint(6) DEFAULT '0',
  `Customize` binary(26) DEFAULT NULL,
  `ModelMainWeapon` decimal(20,0) DEFAULT '0',
  `ModelSubWeapon` decimal(20,0) DEFAULT '0',
  `ModelSystemWeapon` decimal(20,0) DEFAULT '0',
  `ModelEquip` binary(40) DEFAULT NULL,
  `EmoteModeType` smallint(6) DEFAULT '0',
  `FirstLoginTime` decimal(20,0) DEFAULT '0',
  `Language` bigint(20) DEFAULT '0',
  `IsNewGame` smallint(6) DEFAULT '1',
  `IsNewAdventurer` int(1) NOT NULL DEFAULT '1',
  `TerritoryType` int(11) DEFAULT '0',
  `TerritoryId` decimal(20,0) DEFAULT '0',
  `PosX` float DEFAULT '0',
  `PosY` float DEFAULT '0',
  `PosZ` float DEFAULT '0',
  `PosR` float DEFAULT '0',
  `OTerritoryType` int(11) DEFAULT '0',
  `OTerritoryId` decimal(20,0) DEFAULT '0',
  `OPosX` float DEFAULT '0',
  `OPosY` float DEFAULT '0',
  `OPosZ` float DEFAULT '0',
  `OPosR` float DEFAULT '0',
  `GuardianDeity` int(3) DEFAULT '0',
  `BirthDay` int(3) DEFAULT '0',
  `BirthMonth` int(3) DEFAULT '0',
  `Class` int(3) DEFAULT '0',
  `Status` int(3) DEFAULT '0',
  `TotalPlayTime` int(10) DEFAULT '0',
  `FirstClass` int(3) DEFAULT '0',
  `HomePoint` int(3) DEFAULT '0',
  `FavoritePoint` binary(3) DEFAULT NULL,
  `RestPoint` int(10) DEFAULT '0',
  `StartTown` int(3) DEFAULT '0',
  `ActiveTitle` int(5) DEFAULT '0',
  `TitleList` binary(48) DEFAULT NULL,
  `Achievement` binary(16) DEFAULT NULL,
  `Aetheryte` binary(17) DEFAULT NULL,
  `HowTo` binary(33) DEFAULT NULL,
  `Minions` binary(40) DEFAULT NULL,
  `Mounts` binary(17) DEFAULT NULL,
  `Orchestrion` binary(40) DEFAULT NULL,
  `EquippedMannequin` int(5) DEFAULT '0',
  `ConfigFlags` smallint(5) NOT NULL DEFAULT '0',
  `QuestCompleteFlags` varbinary(476) DEFAULT NULL,
  `OpeningSequence` int(3) DEFAULT '0',
  `QuestTracking` binary(10) DEFAULT NULL,
  `GrandCompany` int(3) DEFAULT '0',
  `GrandCompanyRank` binary(3) DEFAULT NULL,
  `Discovery` varbinary(421) DEFAULT NULL,
  `GMRank` int(3) DEFAULT '0',
  `EquipDisplayFlags` int(3) DEFAULT '0',
  `Pose` int(3) DEFAULT '0',
  `Unlocks` binary(64) DEFAULT NULL,
  `CFPenaltyUntil` int(11) DEFAULT NULL,
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`CharacterId`),
  KEY `index` (`AccountId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `characlass` (
  `CharacterId` int(20) NOT NULL DEFAULT '0',
  `ClassIdx` int(3) DEFAULT '0',
  `Exp` int(10) DEFAULT '0',
  `Lvl` int(5) DEFAULT '0',
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`CharacterId`,`ClassIdx`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `charaglobalitem` (
  `CharacterId` int(20) NOT NULL DEFAULT '0',
  `itemId` int(20) NOT NULL DEFAULT '0',
  `storageId` int(5) NOT NULL DEFAULT '0',
  `containerIndex` int(5) NOT NULL DEFAULT '0',
  `stack` int(10) DEFAULT '1',
  `catalogId` int(10) DEFAULT '0',
  `reservedFlag` int(10) DEFAULT '0',
  `signatureId` int(20) DEFAULT '0',
  `flags` int(3) DEFAULT '0',
  `durability` int(5) DEFAULT '30000',
  `refine` int(5) DEFAULT '0',
  `materia_0` int(5) DEFAULT '0',
  `materia_1` int(5) DEFAULT '0',
  `materia_2` int(5) DEFAULT '0',
  `materia_3` int(5) DEFAULT '0',
  `materia_4` int(5) DEFAULT '0',
  `stain` int(3) DEFAULT '0',
  `pattern` int(10) DEFAULT '0',
  `buffer_0` int(3) DEFAULT '0',
  `buffer_1` int(3) DEFAULT '0',
  `buffer_2` int(3) DEFAULT '0',
  `buffer_3` int(3) DEFAULT '0',
  `buffer_4` int(3) DEFAULT '0',
  `deleted` int(1) DEFAULT '0',
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`CharacterId`,`itemId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `charainfoblacklist` (
  `CharacterId` int(20) NOT NULL,
  `CharacterIdList` blob,
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`CharacterId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `charainfolinkshell` (
  `CharacterId` int(20) NOT NULL,
  `LinkshellIdList` binary(64) DEFAULT NULL,
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`CharacterId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `charainfosearch` (
  `CharacterId` int(20) NOT NULL,
  `SelectClassId` int(3) DEFAULT '0',
  `SelectRegion` int(3) DEFAULT '0',
  `SearchComment` binary(193) DEFAULT '\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0',
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`CharacterId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `charaitemcrystal` (
  `CharacterId` int(20) DEFAULT '0',
  `storageId` int(10) DEFAULT '2001',
  `type` int(5) DEFAULT '0',
  `idx` int(5) NOT NULL ,
  `container_0` int(20) DEFAULT '0',
  `container_1` int(20) DEFAULT '0',
  `container_2` int(20) DEFAULT '0',
  `container_3` int(20) DEFAULT '0',
  `container_4` int(20) DEFAULT '0',
  `container_5` int(20) DEFAULT '0',
  `container_6` int(20) DEFAULT '0',
  `container_7` int(20) DEFAULT '0',
  `container_8` int(20) DEFAULT '0',
  `container_9` int(20) DEFAULT '0',
  `container_10` int(20) DEFAULT '0',
  `container_11` int(20) DEFAULT '0',
  `container_12` int(20) DEFAULT '0',
  `container_13` int(20) DEFAULT '0',
  `container_14` int(20) DEFAULT '0',
  `container_15` int(20) DEFAULT '0',
  `container_16` int(20) DEFAULT '0',
  `container_17` int(20) DEFAULT '0',
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`CharacterId`,`storageId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `charaitemcurrency` (
  `CharacterId` int(20) NOT NULL,
  `storageId` int(10) DEFAULT '2000',
  `type` int(5) DEFAULT '0',
  `idx` int(5) NOT NULL,
  `container_0` int(20) DEFAULT '0',
  `container_1` int(20) DEFAULT '0',
  `container_2` int(20) DEFAULT '0',
  `container_3` int(20) DEFAULT '0',
  `container_4` int(20) DEFAULT '0',
  `container_5` int(20) DEFAULT '0',
  `container_6` int(20) DEFAULT '0',
  `container_7` int(20) DEFAULT '0',
  `container_8` int(20) DEFAULT '0',
  `container_9` int(20) DEFAULT '0',
  `container_10` int(20) DEFAULT '0',
  `container_11` int(20) DEFAULT '0',
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`CharacterId`,`storageId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `charaitemgearset` (
  `CharacterId` int(20) NOT NULL,
  `storageId` int(10) NOT NULL,
  `type` int(5) DEFAULT '0',
  `idx` int(5) DEFAULT '0',
  `container_0` int(20) DEFAULT '0',
  `container_1` int(20) DEFAULT '0',
  `container_2` int(20) DEFAULT '0',
  `container_3` int(20) DEFAULT '0',
  `container_4` int(20) DEFAULT '0',
  `container_5` int(20) DEFAULT '0',
  `container_6` int(20) DEFAULT '0',
  `container_7` int(20) DEFAULT '0',
  `container_8` int(20) DEFAULT '0',
  `container_9` int(20) DEFAULT '0',
  `container_10` int(20) DEFAULT '0',
  `container_11` int(20) DEFAULT '0',
  `container_12` int(20) DEFAULT '0',
  `container_13` int(20) DEFAULT '0',
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`CharacterId`,`storageId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `charaiteminventory` (
  `CharacterId` int(20) NOT NULL,
  `storageId` int(10) NOT NULL,
  `type` int(5) DEFAULT '0',
  `idx` int(5) DEFAULT '0',
  `container_0` int(20) DEFAULT '0',
  `container_1` int(20) DEFAULT '0',
  `container_2` int(20) DEFAULT '0',
  `container_3` int(20) DEFAULT '0',
  `container_4` int(20) DEFAULT '0',
  `container_5` int(20) DEFAULT '0',
  `container_6` int(20) DEFAULT '0',
  `container_7` int(20) DEFAULT '0',
  `container_8` int(20) DEFAULT '0',
  `container_9` int(20) DEFAULT '0',
  `container_10` int(20) DEFAULT '0',
  `container_11` int(20) DEFAULT '0',
  `container_12` int(20) DEFAULT '0',
  `container_13` int(20) DEFAULT '0',
  `container_14` int(20) DEFAULT '0',
  `container_15` int(20) DEFAULT '0',
  `container_16` int(20) DEFAULT '0',
  `container_17` int(20) DEFAULT '0',
  `container_18` int(20) DEFAULT '0',
  `container_19` int(20) DEFAULT '0',
  `container_20` int(20) DEFAULT '0',
  `container_21` int(20) DEFAULT '0',
  `container_22` int(20) DEFAULT '0',
  `container_23` int(20) DEFAULT '0',
  `container_24` int(20) DEFAULT '0',
  `container_25` int(20) DEFAULT '0',
  `container_26` int(20) DEFAULT '0',
  `container_27` int(20) DEFAULT '0',
  `container_28` int(20) DEFAULT '0',
  `container_29` int(20) DEFAULT '0',
  `container_30` int(20) DEFAULT '0',
  `container_31` int(20) DEFAULT '0',
  `container_32` int(20) DEFAULT '0',
  `container_33` int(20) DEFAULT '0',
  `container_34` int(20) DEFAULT '0',
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`CharacterId`,`storageId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `charaquest` (
  `CharacterId` int(20) DEFAULT '0',
  `slotId` int(20) DEFAULT '0',
  `QuestId` int(5) DEFAULT '0',
  `Sequence` int(3) DEFAULT '0',
  `Flags` int(3) DEFAULT '0',
  `Variables_0` int(3) DEFAULT '0',
  `Variables_1` int(3) DEFAULT '0',
  `Variables_2` int(3) DEFAULT '0',
  `Variables_3` int(3) DEFAULT '0',
  `Variables_4` int(3) DEFAULT '0',
  `Variables_5` int(3) DEFAULT '0',
  `Variables_6` int(3) DEFAULT '0',
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`CharacterId`,`slotId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `charastatus` (
  `CharacterId` int(20) NOT NULL,
  `Recast_0` binary(24) DEFAULT NULL,
  `Recast_1` binary(24) DEFAULT NULL,
  `Recast_2` binary(24) DEFAULT NULL,
  `Recast_3` binary(24) DEFAULT NULL,
  `Recast_4` binary(24) DEFAULT NULL,
  `Recast_5` binary(24) DEFAULT NULL,
  `Recast_6` binary(24) DEFAULT NULL,
  `Recast_7` binary(24) DEFAULT NULL,
  `Recast_8` binary(24) DEFAULT NULL,
  `Recast_9` binary(24) DEFAULT NULL,
  `Recast_10` binary(24) DEFAULT NULL,
  `Recast_11` binary(24) DEFAULT NULL,
  `Recast_12` binary(24) DEFAULT NULL,
  `Recast_13` binary(24) DEFAULT NULL,
  `Recast_14` binary(24) DEFAULT NULL,
  `Recast_15` binary(24) DEFAULT NULL,
  `Recast_16` binary(24) DEFAULT NULL,
  `Recast_17` binary(24) DEFAULT NULL,
  `Recast_18` binary(24) DEFAULT NULL,
  `Recast_19` binary(24) DEFAULT NULL,
  `Recast_20` binary(24) DEFAULT NULL,
  `Recast_21` binary(24) DEFAULT NULL,
  `Recast_22` binary(24) DEFAULT NULL,
  `Recast_23` binary(24) DEFAULT NULL,
  `Recast_24` binary(24) DEFAULT NULL,
  `Recast_25` binary(24) DEFAULT NULL,
  `Recast_26` binary(24) DEFAULT NULL,
  `Recast_27` binary(24) DEFAULT NULL,
  `Recast_28` binary(24) DEFAULT NULL,
  `Recast_29` binary(24) DEFAULT NULL,
  `Recast_30` binary(24) DEFAULT NULL,
  `Recast_31` binary(24) DEFAULT NULL,
  `Recast_32` binary(24) DEFAULT NULL,
  `Recast_33` binary(24) DEFAULT NULL,
  `Recast_34` binary(24) DEFAULT NULL,
  `Recast_35` binary(24) DEFAULT NULL,
  `Recast_36` binary(24) DEFAULT NULL,
  `Recast_37` binary(24) DEFAULT NULL,
  `Recast_38` binary(24) DEFAULT NULL,
  `Recast_39` binary(24) DEFAULT NULL,
  `Recast_40` binary(24) DEFAULT NULL,
  `Recast_41` binary(24) DEFAULT NULL,
  `Recast_42` binary(24) DEFAULT NULL,
  `Recast_43` binary(24) DEFAULT NULL,
  `Recast_44` binary(24) DEFAULT NULL,
  `Recast_45` binary(24) DEFAULT NULL,
  `Recast_46` binary(24) DEFAULT NULL,
  `Recast_47` binary(24) DEFAULT NULL,
  `Recast_48` binary(24) DEFAULT NULL,
  `Recast_49` binary(24) DEFAULT NULL,
  `Recast_50` binary(24) DEFAULT NULL,
  `Recast_51` binary(24) DEFAULT NULL,
  `Recast_52` binary(24) DEFAULT NULL,
  `Recast_53` binary(24) DEFAULT NULL,
  `Status_0` binary(78) DEFAULT NULL,
  `Status_1` binary(78) DEFAULT NULL,
  `Status_2` binary(78) DEFAULT NULL,
  `Status_3` binary(78) DEFAULT NULL,
  `Status_4` binary(78) DEFAULT NULL,
  `Status_5` binary(78) DEFAULT NULL,
  `Status_6` binary(78) DEFAULT NULL,
  `Status_7` binary(78) DEFAULT NULL,
  `Status_8` binary(78) DEFAULT NULL,
  `Status_9` binary(78) DEFAULT NULL,
  `Status_10` binary(78) DEFAULT NULL,
  `Status_11` binary(78) DEFAULT NULL,
  `Status_12` binary(78) DEFAULT NULL,
  `Status_13` binary(78) DEFAULT NULL,
  `Status_14` binary(78) DEFAULT NULL,
  `Status_15` binary(78) DEFAULT NULL,
  `Status_16` binary(78) DEFAULT NULL,
  `Status_17` binary(78) DEFAULT NULL,
  `Status_18` binary(78) DEFAULT NULL,
  `Status_19` binary(78) DEFAULT NULL,
  `Status_20` binary(78) DEFAULT NULL,
  `Status_21` binary(78) DEFAULT NULL,
  `Status_22` binary(78) DEFAULT NULL,
  `Status_23` binary(78) DEFAULT NULL,
  `Status_24` binary(78) DEFAULT NULL,
  `Status_25` binary(78) DEFAULT NULL,
  `Status_26` binary(78) DEFAULT NULL,
  `Status_27` binary(78) DEFAULT NULL,
  `Status_28` binary(78) DEFAULT NULL,
  `Status_29` binary(78) DEFAULT NULL,
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`CharacterId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `dbupdate` (
  `name` varchar(128) NOT NULL,
  `executionTime` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `discoveryinfo` (
  `id` int(10) NOT NULL,
  `map_id` int(3) NOT NULL,
  `discover_id` int(3) NOT NULL,
  PRIMARY KEY(`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `house` (
  `HouseId` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `LandSetId` int(10) UNSIGNED DEFAULT NULL,
  `BuildTime` bigint(20) DEFAULT NULL,
  `Aetheryte` smallint(6) DEFAULT NULL,
  `Welcome` smallint(6) DEFAULT NULL,
  `Comment` binary(193) DEFAULT '\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0',
  `HouseName` binary(23) DEFAULT '\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0',
  `Endorsements` bigint(20) DEFAULT NULL,
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`HouseId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `housepartsitem` (
  `HouseId` bigint(20) UNSIGNED NOT NULL,
  `itemId` bigint(20) UNSIGNED DEFAULT NULL,
  `CharacterId` bigint(20) UNSIGNED DEFAULT NULL,
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`HouseId`),
  KEY `index` (`CharacterId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `housepartsstorage` (
  `LandSetId` bigint(20) UNSIGNED NOT NULL,
  `HouseId` bigint(20) UNSIGNED NOT NULL,
  `storageId` bigint(20) NOT NULL,
  `type` int(11) DEFAULT NULL,
  `index` int(11) NOT NULL,
  `container_0` bigint(20) UNSIGNED DEFAULT NULL,
  `container_1` bigint(20) UNSIGNED DEFAULT NULL,
  `container_2` bigint(20) UNSIGNED DEFAULT NULL,
  `container_3` bigint(20) UNSIGNED DEFAULT NULL,
  `container_4` bigint(20) UNSIGNED DEFAULT NULL,
  `container_5` bigint(20) UNSIGNED DEFAULT NULL,
  `container_6` bigint(20) UNSIGNED DEFAULT NULL,
  `container_7` bigint(20) UNSIGNED DEFAULT NULL,
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`LandSetId`,`HouseId`,`storageId`,`index`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `infolinkshell` (
  `LinkshellId` bigint(20) NOT NULL AUTO_INCREMENT,
  `MasterCharacterId` int(20) DEFAULT NULL,
  `CharacterIdList` blob,
  `LinkshellName` varchar(32) DEFAULT NULL,
  `LeaderIdList` blob,
  `InviteIdList` blob,
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`LinkshellId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `land` (
  `LandSetId` bigint(20) UNSIGNED NOT NULL,
  `LandId` bigint(20) UNSIGNED NOT NULL,
  `Type` smallint(6) NOT NULL DEFAULT '0',
  `Size` smallint(6) DEFAULT NULL,
  `Status` smallint(6) DEFAULT NULL,
  `LandPrice` bigint(20) DEFAULT NULL,
  `UpdateTime` bigint(20) DEFAULT NULL,
  `OwnerId` bigint(20) UNSIGNED DEFAULT NULL,
  `HouseId` bigint(20) UNSIGNED DEFAULT NULL,
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`LandSetId`, `LandId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `landset` (
  `LandSetId` bigint(20) UNSIGNED NOT NULL,
  `LandId_0` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_1` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_2` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_3` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_4` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_5` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_6` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_7` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_8` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_9` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_10` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_11` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_12` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_13` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_14` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_15` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_16` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_17` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_18` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_19` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_20` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_21` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_22` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_23` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_24` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_25` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_26` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_27` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_28` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_29` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_30` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_31` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_32` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_33` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_34` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_35` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_36` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_37` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_38` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_39` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_40` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_41` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_42` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_43` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_44` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_45` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_46` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_47` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_48` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_49` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_50` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_51` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_52` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_53` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_54` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_55` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_56` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_57` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_58` bigint(20) UNSIGNED DEFAULT '0',
  `LandId_59` bigint(20) UNSIGNED DEFAULT '0',
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`LandSetId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `houseiteminventory` (
	`LandIdent` BIGINT(20) UNSIGNED NOT NULL,
	`ContainerId` INT(10) UNSIGNED NOT NULL,
	`SlotId` INT(10) UNSIGNED NOT NULL,
	`ItemId` INT(20) NOT NULL,
	PRIMARY KEY (`LandIdent`, `ContainerId`, `SlotId`),
	INDEX `landIdent` (`LandIdent`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `spawngroup` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `territoryTypeId` int(5) NOT NULL,
  `bNpcTemplateId` int(10) NOT NULL,
  `level` int(3) NOT NULL,
  `maxHp` int(10) NOT NULL,
  PRIMARY KEY(`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `uniqueiddata` (
  `NextId` int(20) NOT NULL AUTO_INCREMENT,
  `IdName` varchar(16) DEFAULT 'NOT SET',
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`NextId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `zonepositions` (
  `id` int(11) NOT NULL,
  `target_zone_id` int(11) NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `pos_o` float NOT NULL,
  `radius` int(11) NOT NULL DEFAULT '2',
  PRIMARY KEY(`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

CREATE TABLE `landplaceditems` (
	`ItemId` INT(20) UNSIGNED NOT NULL,
	`PosX` FLOAT NOT NULL,
	`PosY` FLOAT NOT NULL,
	`PosZ` FLOAT NOT NULL,
	`Rotation` FLOAT NOT NULL,
	PRIMARY KEY (`ItemId`)
)
COLLATE='latin1_swedish_ci' ENGINE=InnoDB;


CREATE TABLE `charamonsternote` (
  `CharacterId` int(20) NOT NULL,
  `Category_0` binary(41) DEFAULT NULL,
  `Category_1` binary(41) DEFAULT NULL,
  `Category_2` binary(41) DEFAULT NULL,
  `Category_3` binary(41) DEFAULT NULL,
  `Category_4` binary(41) DEFAULT NULL,
  `Category_5` binary(41) DEFAULT NULL,
  `Category_6` binary(41) DEFAULT NULL,
  `Category_7` binary(41) DEFAULT NULL,
  `Category_8` binary(41) DEFAULT NULL,
  `Category_9` binary(41) DEFAULT NULL,
  `Category_10` binary(41) DEFAULT NULL,
  `Category_11` binary(41) DEFAULT NULL,
  `UPDATE_DATE` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(`CharacterId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `__Migration` (
   `MigrationName` VARCHAR(250) NOT NULL,
   PRIMARY KEY (`MigrationName`)
) ENGINE=InnoDB;
