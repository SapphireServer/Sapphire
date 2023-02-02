ALTER TABLE `freecompany`
  DROP `Reputation_1`,
  DROP `Reputation_2`;
ALTER TABLE `freecompany` CHANGE `Reputation_0` `ReputationList` BINARY(24) NULL DEFAULT NULL; 
ALTER TABLE `freecompany`
  DROP `ActiveActionList_1`,
  DROP `ActiveActionList_2`;
ALTER TABLE `freecompany` CHANGE `ActiveActionList_0` `ActiveActionList` BINARY(24) NULL DEFAULT NULL; 
ALTER TABLE `freecompany`
  DROP `ActiveActionLeftTime_1`,
  DROP `ActiveActionLeftTime_2`;
ALTER TABLE `freecompany` CHANGE `ActiveActionLeftTime_0` `ActiveActionLeftTimeList` BINARY(24) NULL DEFAULT NULL; 
ALTER TABLE `freecompany`
  DROP `StockActionList_0`,
  DROP `StockActionList_1`,
  DROP `StockActionList_2`,
  DROP `StockActionList_3`,
  DROP `StockActionList_4`,
  DROP `StockActionList_5`,
  DROP `StockActionList_6`,
  DROP `StockActionList_7`,
  DROP `StockActionList_8`,
  DROP `StockActionList_9`,
  DROP `StockActionList_10`,
  DROP `StockActionList_11`,
  DROP `StockActionList_12`,
  DROP `StockActionList_13`;
ALTER TABLE `freecompany` CHANGE `StockActionList_14` `StockActionList` BINARY(120) NULL DEFAULT NULL; 