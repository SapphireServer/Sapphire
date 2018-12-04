CREATE TABLE `houseiteminventory` (
	`landIdent` BIGINT(20) UNSIGNED NOT NULL,
	`containerId` INT(10) UNSIGNED NOT NULL,
	`itemId` INT(20) NOT NULL,
	INDEX `landIdent` (`landIdent`)
)
COLLATE='latin1_swedish_ci'
ENGINE=InnoDB
;
