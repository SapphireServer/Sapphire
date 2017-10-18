-- -------------------------------------------
-- ALTER TABLE `charaiteminventory` ADD `container_25` INT(20) NOT NULL AFTER `container_24`, 
--								 ADD `container_26` INT(20) NOT NULL AFTER `container_25`,
--								 ADD `container_27` INT(20) NOT NULL AFTER `container_26`,
--								 ADD `container_28` INT(20) NOT NULL AFTER `container_27`,
--								 ADD `container_29` INT(20) NOT NULL AFTER `container_28`,
--								 ADD `container_30` INT(20) NOT NULL AFTER `container_29`,
--								 ADD `container_31` INT(20) NOT NULL AFTER `container_30`,
--								 ADD `container_32` INT(20) NOT NULL AFTER `container_31`,
--								 ADD `container_33` INT(20) NOT NULL AFTER `container_32`,
--								 ADD `container_34` INT(20) NOT NULL AFTER `container_33`;
--
-- -------------------------------------------
-- update.sql Before Merge into Other SQL's 30/08/2017
-- -------------------------------------------
-- ALTER TABLE `charadetail` ADD `EquipDisplayFlags` int(3) DEFAULT '0' AFTER `GMRank`;
-- -------------------------------------------
-- update.sql before titles added 09/10/2017

ALTER TABLE `charadetail` CHANGE `TitleList` `Titlelist` BINARY(48) NULL DEFAULT NULL;
ALTER TABLE `charadetail` ADD COLUMN `Orchestrion` BINARY(38) DEFAULT NULL AFTER `unlocks`;