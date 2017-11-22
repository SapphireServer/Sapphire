SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";
DROP TABLE IF EXISTS `charaquestnew`;
CREATE TABLE charaquestnew (
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
  `IS_DELETE` int(3) DEFAULT '0',
  `IS_NOT_ACTIVE_FLG` int(3) DEFAULT '0',
  `UPDATE_DATE` DATETIME NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=MyISAM DEFAULT CHARSET=utf8;