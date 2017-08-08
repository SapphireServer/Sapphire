RENAME TABLE `dbaccounts` TO `accounts`;
RENAME TABLE `dbbattlenpc` TO `battlenpc`;
RENAME TABLE `dbchara` TO `charabase`;
RENAME TABLE `dbcharapcclass` TO `characlass`;
RENAME TABLE `dbcharapc` TO `charadetail`;
RENAME TABLE `dbcharaitems` TO `charaglobalitem`;
RENAME TABLE `dbcharainfoblacklist` TO `charainfoblacklist`;
RENAME TABLE `dbcharainfofriendlist` TO `charainfofriendlist`;
RENAME TABLE `dbcharainfolinkshell` TO `charainfolinkshell`;
RENAME TABLE `dbcharainfoprofile` TO `charainfosearch`;
RENAME TABLE `dbcharaitemcrystal` TO `charaitemcrystal`;
RENAME TABLE `dbcharaitemcurrency` TO `charaitemcurrency`;
RENAME TABLE `dbcharaitemmannequin` TO `charaitemgearset`;
RENAME TABLE `dbcharaitembaggage` TO `charaiteminventory`;
RENAME TABLE `dbcharaquest` TO `charaquest`;
RENAME TABLE `dbdiscoveryref` TO `discoveryinfo`;
RENAME TABLE `dbinfolinkshell` TO `infolinkshell`;
RENAME TABLE `dbuniqueiddata` TO `uniqueiddata`;
RENAME TABLE `dbzonemapping` TO `zonemapping`;
RENAME TABLE `dbzonepositions` TO `zonepositions`;
RENAME TABLE `dbzoneservers` TO `zoneservers`;

ALTER TABLE `charaiteminventory` ADD `container_25` INT(20) NOT NULL AFTER `container_24`, ADD `container_26` INT(20) NOT NULL AFTER `container_25`, ADD `container_27` INT(20) NOT NULL AFTER `container_26`, ADD `container_28` INT(20) NOT NULL AFTER `container_27`, ADD `container_29` INT(20) NOT NULL AFTER `container_28`, ADD `container_30` INT(20) NOT NULL AFTER `container_29`, ADD `container_31` INT(20) NOT NULL AFTER `container_30`, ADD `container_32` INT(20) NOT NULL AFTER `container_31`, ADD `container_33` INT(20) NOT NULL AFTER `container_32`, ADD `container_34` INT(20) NOT NULL AFTER `container_33`;

ALTER TABLE `characlass` ADD `Lv_24` INT(5) NOT NULL DEFAULT '0' AFTER `Exp_23`, ADD `Exp_24` INT(10) NOT NULL DEFAULT '0' AFTER `Lv_24`, ADD `Lv_25` INT(5) NOT NULL DEFAULT '0' AFTER `Exp_24`, ADD `Exp_25` INT(19) NOT NULL DEFAULT '0' AFTER `Lv_25`;

ALTER TABLE `charadetail` CHANGE `Aetheryte` `Aetheryte` BINARY(16) NULL DEFAULT NULL, CHANGE `HowTo` `HowTo` BINARY(33) NULL DEFAULT NULL, CHANGE `Minions` `Minions` BINARY(33) NULL DEFAULT NULL, CHANGE `Mounts` `Mounts` BINARY(13) NULL DEFAULT NULL;