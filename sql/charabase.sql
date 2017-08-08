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
-- Table structure for table `charabase`
--

DROP TABLE IF EXISTS `charabase`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `charabase` (
  `AccountId` int(11) NOT NULL,
  `Hp` int(10) DEFAULT NULL,
  `Mp` int(10) DEFAULT NULL,
  `Tp` int(10) DEFAULT NULL,
  `Gp` int(10) DEFAULT NULL,
  `Mode` int(3) DEFAULT '0',
  `Mount` int(3) DEFAULT NULL,
  `Voice` int(3) DEFAULT NULL,
  `Customize` binary(26) DEFAULT NULL,
  `ModelMainWeapon` int(20) DEFAULT NULL,
  `ModelSubWeapon` int(20) DEFAULT NULL,
  `ModelSystemWeapon` int(20) DEFAULT NULL,
  `ModelEquip` binary(40) DEFAULT NULL,
  `EmoteModeType` int(3) DEFAULT NULL,
  `CharacterId` int(20) NOT NULL DEFAULT '0',
  `CharacterType` int(5) DEFAULT NULL,
  `Name` varchar(32) DEFAULT NULL,
  `FirstLogin` int(20) DEFAULT NULL,
  `Language` int(10) DEFAULT NULL,
  `IsNewGame` int(3) DEFAULT NULL,
  `Invisible` int(3) DEFAULT NULL,
  `InstantiationTime` int(20) DEFAULT NULL,
  `PrimaryTerritoryType` int(5) DEFAULT NULL,
  `PrimaryTerritoryId` int(20) DEFAULT NULL,
  `Pos_0_0` float DEFAULT NULL,
  `Pos_0_1` float DEFAULT NULL,
  `Pos_0_2` float DEFAULT NULL,
  `Pos_0_3` float DEFAULT NULL,
  `PrimaryLayoutId` int(10) DEFAULT NULL,
  `PrimaryExclusiveId` int(10) DEFAULT NULL,
  `PrimaryMoveType` int(3) DEFAULT NULL,
  `PrimaryContentId` int(10) DEFAULT NULL,
  `SecondaryTerritoryType` int(5) DEFAULT NULL,
  `SecondaryTerritoryId` int(20) DEFAULT NULL,
  `Pos_1_0` float DEFAULT NULL,
  `Pos_1_1` float DEFAULT NULL,
  `Pos_1_2` float DEFAULT NULL,
  `Pos_1_3` float DEFAULT NULL,
  `SecondaryLayoutId` int(10) DEFAULT NULL,
  `Effectiveness` int(3) DEFAULT NULL,
  `Update` int(10) DEFAULT NULL,
  `Pos_0` float DEFAULT NULL,
  `Pos_1` float DEFAULT NULL,
  `Pos_2` float DEFAULT NULL,
  `Pos_3` float DEFAULT NULL,
  `ContentId` bigint(20) DEFAULT NULL,
  `IsNewAdventurer` int(1) NOT NULL DEFAULT '1',
  `IS_DELETE` int(3) DEFAULT '0',
  `IS_NOT_ACTIVE_FLG` int(3) DEFAULT '0',
  `UPDATE_DATE` datetime DEFAULT NULL,
  PRIMARY KEY (`CharacterId`),
  KEY `ContentId` (`ContentId`),
  KEY `Name` (`Name`),
  KEY `AccountId` (`AccountId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `charabase`
--

LOCK TABLES `charabase` WRITE;
/*!40000 ALTER TABLE `charabase` DISABLE KEYS */;
/*!40000 ALTER TABLE `charabase` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-12-09 17:37:07
