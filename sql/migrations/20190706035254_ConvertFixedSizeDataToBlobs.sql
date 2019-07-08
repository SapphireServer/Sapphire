-- Migration generated at 2019/07/06 03:52:54
-- 20190706035254_ConvertFixedSizeDataToBlobs.sql

ALTER TABLE `charainfo`
	CHANGE COLUMN `TitleList` `TitleList` BLOB NULL DEFAULT NULL AFTER `ActiveTitle`,
	CHANGE COLUMN `Achievement` `Achievement` BLOB NULL DEFAULT NULL AFTER `TitleList`,
	CHANGE COLUMN `Aetheryte` `Aetheryte` BLOB NULL DEFAULT NULL AFTER `Achievement`,
	CHANGE COLUMN `HowTo` `HowTo` BLOB NULL DEFAULT NULL AFTER `Aetheryte`,
	CHANGE COLUMN `Minions` `Minions` BLOB NULL DEFAULT NULL AFTER `HowTo`,
	CHANGE COLUMN `Mounts` `Mounts` BLOB NULL DEFAULT NULL AFTER `Minions`,
	CHANGE COLUMN `Orchestrion` `Orchestrion` BLOB NULL DEFAULT NULL AFTER `Mounts`,
	CHANGE COLUMN `QuestCompleteFlags` `QuestCompleteFlags` BLOB NULL DEFAULT NULL AFTER `ConfigFlags`,
	CHANGE COLUMN `QuestTracking` `QuestTracking` BLOB NULL DEFAULT NULL AFTER `OpeningSequence`,
	CHANGE COLUMN `Discovery` `Discovery` BLOB NULL DEFAULT NULL AFTER `GrandCompanyRank`,
	CHANGE COLUMN `Unlocks` `Unlocks` BLOB NULL DEFAULT NULL AFTER `Pose`;
