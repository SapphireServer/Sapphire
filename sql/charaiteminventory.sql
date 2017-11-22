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

-- Dumping structure for table sapphire.charaiteminventory
CREATE TABLE IF NOT EXISTS `charaiteminventory` (
  `CharacterId` int(20) NOT NULL,
  `storageId` int(10) NOT NULL,
  `type` int(5) DEFAULT '0',
  `idx` int(5) NOT NULL AUTO_INCREMENT,
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
  `IS_DELETE` int(3) DEFAULT '0',
  `IS_NOT_ACTIVE_FLG` int(3) DEFAULT '0',
  `UPDATE_DATE` DATETIME NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`CharacterId`,`storageId`),
  UNIQUE KEY `idx` (`idx`)
) ENGINE=MyISAM AUTO_INCREMENT=161 DEFAULT CHARSET=utf8;

-- Dumping data for table sapphire.charaiteminventory: 0 rows
DELETE FROM `charaiteminventory`;
/*!40000 ALTER TABLE `charaiteminventory` DISABLE KEYS */;
/*!40000 ALTER TABLE `charaiteminventory` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
