CREATE TABLE `housepartsstorage` (
	`LandSetId` INT UNSIGNED NULL,
	`HouseId` INT UNSIGNED NULL,
	`StorageId` BIGINT, 
	`Type` INT NULL,
	`Index` INT NULL,
	`Container_0` INT UNSIGNED DEFAULT '0',
	`Container_1` INT UNSIGNED DEFAULT '0',
	`Container_2` INT UNSIGNED DEFAULT '0',
	`Container_3` INT UNSIGNED DEFAULT '0',
	`Container_4` INT UNSIGNED DEFAULT '0',
	`Container_5` INT UNSIGNED DEFAULT '0',
	`Container_6` INT UNSIGNED DEFAULT '0',
	`Container_7` INT UNSIGNED DEFAULT '0',
	`UPDATE_DATE` DATETIME NULL
)
COLLATE='latin1_swedish_ci'
ENGINE=InnoDB;