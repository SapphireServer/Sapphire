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
  `CharacterId` int(20) NOT NULL DEFAULT '0',
  `ClassIdx` int(3) DEFAULT '0',
  `Exp` int(10) DEFAULT '0',
  `Lvl` int(5) DEFAULT '0',
  INDEX `CharacterId` (`CharacterId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- Dumping data for table sapphire.characlass: 0 rows
DELETE FROM `characlass`;
/*!40000 ALTER TABLE `characlass` DISABLE KEYS */;
/*!40000 ALTER TABLE `characlass` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
