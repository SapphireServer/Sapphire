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

-- Dumping structure for table sapphire.characlass
CREATE TABLE IF NOT EXISTS `characlass` (
  `Lv_0` int(5) DEFAULT '0',
  `Exp_0` int(10) DEFAULT '0',
  `Lv_1` int(5) DEFAULT '0',
  `Exp_1` int(10) DEFAULT '0',
  `Lv_2` int(5) DEFAULT '0',
  `Exp_2` int(10) DEFAULT '0',
  `Lv_3` int(5) DEFAULT '0',
  `Exp_3` int(10) DEFAULT '0',
  `Lv_4` int(5) DEFAULT '0',
  `Exp_4` int(10) DEFAULT '0',
  `Lv_5` int(5) DEFAULT '0',
  `Exp_5` int(10) DEFAULT '0',
  `Lv_6` int(5) DEFAULT '0',
  `Exp_6` int(10) DEFAULT '0',
  `Lv_7` int(5) DEFAULT '0',
  `Exp_7` int(10) DEFAULT '0',
  `Lv_8` int(5) DEFAULT '0',
  `Exp_8` int(10) DEFAULT '0',
  `Lv_9` int(5) DEFAULT '0',
  `Exp_9` int(10) DEFAULT '0',
  `Lv_10` int(5) DEFAULT '0',
  `Exp_10` int(10) DEFAULT '0',
  `Lv_11` int(5) DEFAULT '0',
  `Exp_11` int(10) DEFAULT '0',
  `Lv_12` int(5) DEFAULT '0',
  `Exp_12` int(10) DEFAULT '0',
  `Lv_13` int(5) DEFAULT '0',
  `Exp_13` int(10) DEFAULT '0',
  `Lv_14` int(5) DEFAULT '0',
  `Exp_14` int(10) DEFAULT '0',
  `Lv_15` int(5) DEFAULT '0',
  `Exp_15` int(10) DEFAULT '0',
  `Lv_16` int(5) DEFAULT '0',
  `Exp_16` int(10) DEFAULT '0',
  `Lv_17` int(5) DEFAULT '0',
  `Exp_17` int(10) DEFAULT '0',
  `Lv_18` int(5) DEFAULT '0',
  `Exp_18` int(10) DEFAULT '0',
  `Lv_19` int(5) NOT NULL DEFAULT '0',
  `Exp_19` int(10) NOT NULL DEFAULT '0',
  `Lv_20` int(5) NOT NULL DEFAULT '0',
  `Exp_20` int(10) NOT NULL DEFAULT '0',
  `Lv_21` int(5) NOT NULL DEFAULT '0',
  `Exp_21` int(10) NOT NULL DEFAULT '0',
  `Lv_22` int(5) NOT NULL DEFAULT '0',
  `Exp_22` int(10) NOT NULL DEFAULT '0',
  `Lv_23` int(5) DEFAULT '0',
  `Exp_23` int(10) DEFAULT '0',
  `Lv_24` int(5) NOT NULL DEFAULT '0',
  `Exp_24` int(10) NOT NULL DEFAULT '0',
  `Lv_25` int(5) NOT NULL DEFAULT '0',
  `Exp_25` int(19) NOT NULL DEFAULT '0',
  `CharacterId` int(20) NOT NULL DEFAULT '0',
  `IS_DELETE` int(3) DEFAULT '0',
  `IS_NOT_ACTIVE_FLG` int(3) DEFAULT '0',
  `UPDATE_DATE` datetime DEFAULT NULL,
  PRIMARY KEY (`CharacterId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- Dumping data for table sapphire.characlass: 0 rows
DELETE FROM `characlass`;
/*!40000 ALTER TABLE `characlass` DISABLE KEYS */;
/*!40000 ALTER TABLE `characlass` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
