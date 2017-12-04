-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               10.1.24-MariaDB - mariadb.org binary distribution
-- Server OS:                    Win32
-- HeidiSQL Version:             9.4.0.5125
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE `charainfo` (
  `AccountId` int(11) NOT NULL,
  `CharacterId` decimal(20,0) NOT NULL,
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
  `Aetheryte` binary(16) DEFAULT NULL,
  `HowTo` binary(33) DEFAULT NULL,
  `Minions` binary(33) DEFAULT NULL,
  `Mounts` binary(13) DEFAULT NULL,
  `EquippedMannequin` int(5) DEFAULT '0',
  `ConfigFlags` smallint(5) NOT NULL DEFAULT '0',
  `QuestCompleteFlags` binary(200) DEFAULT NULL,
  `OpeningSequence` int(3) DEFAULT '0',
  `QuestTracking` binary(10) DEFAULT NULL,
  `GrandCompany` int(3) DEFAULT '0',
  `GrandCompanyRank` binary(3) DEFAULT NULL,
  `Discovery` blob,
  `GMRank` int(3) DEFAULT '0',
  `Unlocks` binary(64) DEFAULT NULL,
  `CFPenaltyUntil` int(11) DEFAULT NULL,
  `UPDATE_DATE` DATETIME NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`CharacterId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- Dumping data for table sapphire.charainfo: 0 rows
DELETE FROM `charainfo`;
/*!40000 ALTER TABLE `charainfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `charainfo` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
