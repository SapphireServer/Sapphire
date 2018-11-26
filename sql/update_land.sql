ALTER TABLE `land` ADD `Type` SMALLINT(6) NOT NULL DEFAULT '0' AFTER `LandId`;
ALTER TABLE `house` ADD `HouseName` binary(23) DEFAULT "" AFTER `Comment`;
ALTER TABLE `house` ADD `HousePartModels` BINARY(32) DEFAULT "" AFTER `Endorsements`;
ALTER TABLE `house` ADD `HousePartColours` BINARY(8) DEFAULT "" AFTER `HousePartModels`;