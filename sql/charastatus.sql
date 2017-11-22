
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

DROP TABLE IF EXISTS `charastatus`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `charastatus` (
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
  `CharacterId` int(20) DEFAULT NULL,
  `IS_DELETE` int(3) DEFAULT '0',
  `IS_NOT_ACTIVE_FLG` int(3) DEFAULT '0',
  `UPDATE_DATE` DATETIME NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `_112_dbcharastatus`
--

LOCK TABLES `charastatus` WRITE;
/*!40000 ALTER TABLE `charastatus` DISABLE KEYS */;
/*!40000 ALTER TABLE `charastatus` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-12-09 17:36:59