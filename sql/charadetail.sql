-- MySQL dump 10.13  Distrib 5.7.13, for Win64 (x86_64)
--
-- Host: localhost    Database: sapphire
-- ------------------------------------------------------
-- Server version	5.7.13-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `charadetail`
--

DROP TABLE IF EXISTS `charadetail`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

CREATE TABLE charadetail (
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
  `Aetheryte` binary(12) DEFAULT NULL,
  `HowTo` binary(32) DEFAULT NULL,
  `Minions` binary(32) DEFAULT NULL,
  `Mounts` binary(11) DEFAULT NULL,
  `EquippedMannequin` int(5) DEFAULT NULL,
  `ConfigFlags` smallint(5) NOT NULL DEFAULT '0',
  `GatheringHistoryPointId` binary(8) DEFAULT NULL,
  `GatheringDivisionOpenFla` binary(40) DEFAULT NULL,
  `GatheringItemGetFlags` binary(60) DEFAULT NULL,
  `RecipeDivisionOpenFlags` binary(80) DEFAULT NULL,
  `RecipeCreateFlags` binary(100) DEFAULT NULL,
  `QuestCompleteFlags` binary(200) DEFAULT NULL,
  `LeveCompleteFlags` binary(200) DEFAULT NULL,
  `OpeningSequence` int(3) DEFAULT NULL,
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
  `CFPenaltyUntil` int unsigned NOT NULL DEFAULT '0',
  `TownWarpFstFlags` binary(2) DEFAULT NULL,
  `PathId` int(10) DEFAULT NULL,
  `StepIndex` int(5) DEFAULT NULL,
  `ChocoboTaxiStandFlags` binary(8) DEFAULT NULL,
  `unlocks` binary(64) DEFAULT NULL,
  `CharacterId` int(20) NOT NULL DEFAULT '0',
  `IS_DELETE` int(3) DEFAULT '0',
  `IS_NOT_ACTIVE_FLG` int(3) DEFAULT '0',
  `UPDATE_DATE` datetime DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;


ALTER TABLE charadetail
  ADD PRIMARY KEY (`CharacterId`);

/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `charadetail`
--

LOCK TABLES `charadetail` WRITE;
/*!40000 ALTER TABLE `charadetail` DISABLE KEYS */;
/*!40000 ALTER TABLE `charadetail` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-12-09 17:37:12
