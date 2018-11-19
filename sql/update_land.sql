ALTER TABLE `land` ADD `Type` SMALLINT(6) NOT NULL DEFAULT '0' AFTER `LandId`;
ALTER TABLE `house` ADD `HouseName` binary(23) DEFAULT "" AFTER `Comment`;