CREATE TABLE IF NOT EXISTS charainfofriendlist (
	`CharacterId` int(20) NOT NULL,
	`CharacterIdList` blob,
	`InviteDataList` blob,
	`IS_DELETE` int(3) DEFAULT 0,
	`IS_NOT_ACTIVE_FLG` int(3) DEFAULT 0,
	`UPDATE_DATE` datetime,
	PRIMARY KEY (`CharacterId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
