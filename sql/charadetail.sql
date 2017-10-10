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

-- Dumping structure for table sapphire.charadetail
CREATE TABLE IF NOT EXISTS `charadetail` (
  `GuardianDeity` int(3) DEFAULT NULL,
  `BirthDay` int(3) DEFAULT NULL,
  `BirthMonth` int(3) NOT NULL,
  `Class` int(3) DEFAULT NULL,
  `MakeValid` int(3) DEFAULT NULL,
  `RetainerId` int(20) DEFAULT NULL,
  `RetainerName` varchar(32) DEFAULT NULL,
  `CreateUnixTime` int(20) DEFAULT NULL,
  `IsActive` int(3) DEFAULT NULL,
  `IsRename` int(3) DEFAULT NULL,
  `Status` int(3) DEFAULT NULL,
  `Platform` varchar(32) DEFAULT NULL,
  `TotalPlayTime` int(10) DEFAULT '0',
  `TotalPlayTimeSecond` float DEFAULT NULL,
  `FirstClass` int(3) DEFAULT NULL,
  `HomePoint` int(3) DEFAULT NULL,
  `FavoritePoint` binary(3) DEFAULT NULL,
  `RestPoint` int(10) DEFAULT NULL,
  `RentalTimer` float DEFAULT NULL,
  `StartTown` int(3) DEFAULT NULL,
  `ActiveTitle` int(5) DEFAULT NULL,
  `TitleList` binary(32) DEFAULT NULL,
  `Achievement` binary(16) DEFAULT NULL,
  `Aetheryte` binary(16) DEFAULT NULL,
  `HowTo` binary(33) DEFAULT NULL,
  `Minions` binary(33) DEFAULT NULL,
  `Mounts` binary(13) DEFAULT NULL,
  `EquippedMannequin` int(5) DEFAULT NULL,
  `ConfigFlags` smallint(5) NOT NULL DEFAULT '0',
  `GatheringHistoryPointId` binary(8) DEFAULT NULL,
  `GatheringDivisionOpenFla` binary(40) DEFAULT NULL,
  `GatheringItemGetFlags` binary(60) DEFAULT NULL,
  `RecipeDivisionOpenFlags` binary(80) DEFAULT NULL,
  `RecipeCreateFlags` binary(100) DEFAULT NULL,
  `QuestCompleteFlags` binary(200) DEFAULT NULL,
  `LeveCompleteFlags` binary(200) DEFAULT NULL,
  `OpeningSequence` int(3) DEFAULT '0',
  `QuestTracking` binary(10) DEFAULT NULL,
  `LeveTicketNum` int(3) DEFAULT NULL,
  `LeveTicketLastGetTime` int(10) DEFAULT NULL,
  `GuildleveAssignmentSeed` int(5) DEFAULT NULL,
  `GuildleveAssignmentCount` int(3) DEFAULT NULL,
  `GuildleveFactionCreditBr` int(5) DEFAULT NULL,
  `GuildleveFactionCreditAz` int(5) DEFAULT NULL,
  `GuildleveFactionCreditHo` int(5) DEFAULT NULL,
  `GrandCompany` int(3) DEFAULT NULL,
  `GrandCompanyRank` binary(3) DEFAULT NULL,
  `Discovery` blob,
  `ContentRetryTime` blob,
  `ContentJoinTime` int(10) DEFAULT NULL,
  `ContentClearFlag` blob,
  `CFPenaltyUntil` int(10) unsigned NOT NULL DEFAULT '0',
  `TownWarpFstFlags` binary(2) DEFAULT NULL,
  `PathId` int(10) DEFAULT NULL,
  `StepIndex` int(5) DEFAULT NULL,
  `ChocoboTaxiStandFlags` binary(8) DEFAULT NULL,
  `GMRank` int(3) DEFAULT '0',
  `EquipDisplayFlags` int(3) DEFAULT '0',
  `unlocks` binary(64) DEFAULT NULL,
  `Orchestrion` binary(38) DEFAULT NULL,
  `CharacterId` int(20) NOT NULL DEFAULT '0',
  `IS_DELETE` int(3) DEFAULT '0',
  `IS_NOT_ACTIVE_FLG` int(3) DEFAULT '0',
  `UPDATE_DATE` datetime DEFAULT NULL,
  PRIMARY KEY (`CharacterId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- Dumping data for table sapphire.charadetail: 0 rows
DELETE FROM `charadetail`;
/*!40000 ALTER TABLE `charadetail` DISABLE KEYS */;
/*!40000 ALTER TABLE `charadetail` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
