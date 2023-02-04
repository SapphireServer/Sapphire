-- Migration generated at 2021/09/16 08:19:02
-- 20210916081902_RenameContentIdToActorId.sql

ALTER TABLE `accounts`
	CHANGE COLUMN `account_id` `account_id` BIGINT UNSIGNED NOT NULL FIRST;

ALTER TABLE `characlass`
	CHANGE COLUMN `CharacterId` `CharacterId` BIGINT UNSIGNED NOT NULL FIRST;

ALTER TABLE `charaglobalitem`
	CHANGE COLUMN `CharacterId` `CharacterId` BIGINT UNSIGNED NOT NULL FIRST;

ALTER TABLE `charainfo`
	CHANGE COLUMN `AccountId` `AccountId` BIGINT UNSIGNED NOT NULL FIRST,
	CHANGE COLUMN `CharacterId` `CharacterId` BIGINT UNSIGNED NOT NULL AFTER `AccountId`,
	CHANGE COLUMN `ContentId` `EntityId` INT UNSIGNED NULL DEFAULT '0' AFTER `CharacterId`;

ALTER TABLE `charainfoblacklist`
	CHANGE COLUMN `CharacterId` `CharacterId` BIGINT UNSIGNED NOT NULL FIRST;

ALTER TABLE `charainfolinkshell`
	CHANGE COLUMN `CharacterId` `CharacterId` BIGINT UNSIGNED NOT NULL FIRST;

ALTER TABLE `charainfosearch`
	CHANGE COLUMN `CharacterId` `CharacterId` BIGINT UNSIGNED NOT NULL FIRST;

ALTER TABLE `charaitemcrystal`
	CHANGE COLUMN `CharacterId` `CharacterId` BIGINT UNSIGNED NOT NULL FIRST;

ALTER TABLE `charaitemcurrency`
	CHANGE COLUMN `CharacterId` `CharacterId` BIGINT UNSIGNED NOT NULL FIRST;

ALTER TABLE `charaitemgearset`
	CHANGE COLUMN `CharacterId` `CharacterId` BIGINT UNSIGNED NOT NULL FIRST;

ALTER TABLE `charaiteminventory`
	CHANGE COLUMN `CharacterId` `CharacterId` BIGINT UNSIGNED NOT NULL FIRST;

ALTER TABLE `charamonsternote`
	CHANGE COLUMN `CharacterId` `CharacterId` BIGINT UNSIGNED NOT NULL FIRST;

ALTER TABLE `charaquest`
	CHANGE COLUMN `CharacterId` `CharacterId` BIGINT UNSIGNED NOT NULL FIRST;

ALTER TABLE `charastatus`
	CHANGE COLUMN `CharacterId` `CharacterId` BIGINT UNSIGNED NOT NULL FIRST;

ALTER TABLE `infolinkshell`
	CHANGE COLUMN `MasterCharacterId` `MasterCharacterId` BIGINT UNSIGNED NULL DEFAULT NULL AFTER `LinkshellId`;
