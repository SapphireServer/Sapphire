#include "ZoneDbConnection.h"
#include <MySqlConnector.h>

Sapphire::Db::ZoneDbConnection::ZoneDbConnection( ConnectionInfo& connInfo ) :
  DbConnection( connInfo )
{
}

Sapphire::Db::ZoneDbConnection::ZoneDbConnection( Common::Util::LockedWaitQueue< std::shared_ptr< Operation > >* q,
                                                  ConnectionInfo& connInfo ) :
  DbConnection( q, connInfo )
{
}

Sapphire::Db::ZoneDbConnection::~ZoneDbConnection()
{
}

void Sapphire::Db::ZoneDbConnection::doPrepareStatements()
{
  if( !m_reconnecting )
    m_stmts.resize( MAX_STATEMENTS );

  /// CHARA
  prepareStatement( CHARA_SEL,
                    "SELECT EntityId, Name, Hp, Mp, Tp, Gp, Mode, Mount, InvincibleGM, Voice, "
                    "Customize, ModelMainWeapon, ModelSubWeapon, ModelSystemWeapon, "
                    "ModelEquip, EmoteModeType, FirstLoginTime, Language, IsNewGame, "
                    "IsNewAdventurer, TerritoryType, TerritoryId, PosX, PosY, PosZ, PosR, "
                    "OTerritoryType, OTerritoryId, OPosX, OPosY, OPosZ, OPosR, GuardianDeity, "
                    "BirthDay, BirthMonth, Class, Status, TotalPlayTime, FirstClass, HomePoint, "
                    "FavoritePoint, RestPoint, StartTown, ActiveTitle, TitleList, "
                    "Aetheryte, HowTo, Minions, Mounts, Orchestrion, EquippedMannequin, ConfigFlags, "
                    "QuestCompleteFlags, OpeningSequence, QuestTracking, GrandCompany, "
                    "GrandCompanyRank, Discovery, GMRank, EquipDisplayFlags, Unlocks, CFPenaltyUntil, "
                    "Pose "
                    "FROM charainfo WHERE CharacterId = ?;",
                    CONNECTION_SYNC );


  prepareStatement( CHARA_UP,
                    "UPDATE charainfo SET "
                    "Hp = ?, Mp = ?, Tp = ?, Gp = ?, Mode = ?, Mount = ?, InvincibleGM = ?, Voice = ?, "
                    "Customize = ?, ModelMainWeapon = ?, ModelSubWeapon = ?, ModelSystemWeapon = ?, "
                    "ModelEquip = ?, EmoteModeType = ?, Language = ?, IsNewGame = ?, IsNewAdventurer = ?, "
                    "TerritoryType = ?, TerritoryId = ?, PosX = ?, PosY = ?, PosZ = ?, PosR = ?, "
                    "OTerritoryType = ?, OTerritoryId = ?, OPosX = ?, OPosY = ?, OPosZ = ?, OPosR = ?, "
                    "Class = ?, Status = ?, TotalPlayTime = ?, HomePoint = ?, FavoritePoint = ?, RestPoint = ?, "
                    "ActiveTitle = ?, TitleList = ?, Aetheryte = ?, HowTo = ?, Minions = ?, Mounts = ?, Orchestrion = ?, "
                    "EquippedMannequin = ?, ConfigFlags = ?, QuestCompleteFlags = ?, OpeningSequence = ?, "
                    "QuestTracking = ?, GrandCompany = ?, GrandCompanyRank = ?, Discovery = ?, GMRank = ?, EquipDisplayFlags = ?, Unlocks = ?, "
                    "CFPenaltyUntil = ?, Pose = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );


  prepareStatement( CHARA_SEL_MINIMAL,
                    "SELECT Name, Customize, ModelMainWeapon, ModelSubWeapon, ModelEquip, TerritoryType, GuardianDeity, "
                    "Class, EntityId, BirthDay, BirthMonth, EquipDisplayFlags "
                    "FROM charainfo WHERE CharacterId = ?;",
                    CONNECTION_SYNC );

  prepareStatement( CHARA_INS,
                    "INSERT INTO charainfo (AccountId, CharacterId, EntityId, Name, Hp, Mp, "
                    "Customize, Voice, IsNewGame, TerritoryType, PosX, PosY, PosZ, PosR, ModelEquip, "
                    "IsNewAdventurer, GuardianDeity, Birthday, BirthMonth, Class, Status, FirstClass, "
                    "HomePoint, StartTown, Discovery, HowTo, QuestCompleteFlags, Unlocks, QuestTracking, "
                    "Aetheryte, GMRank, Mounts, Orchestrion, ModelMainWeapon, UPDATE_DATE ) "
                    "VALUES ( ?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,NOW() );",
                    CONNECTION_SYNC );

  prepareStatement( CHARA_UP_NAME, "UPDATE charainfo SET Name = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_HPMP, "UPDATE charainfo SET Hp = ?, Mp = ?, Tp = ?, Gp = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_MODE, "UPDATE charainfo SET Mode = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_MOUNT, "UPDATE charainfo SET Mount = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_INVINCIBLE, "UPDATE charainfo SET InvincibleGM = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_CUSTOMIZE, "UPDATE charainfo SET Customize = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_MODELMAINWEAP, "UPDATE charainfo SET ModelMainWeapon = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_MODELSUBWEAP, "UPDATE charainfo SET ModelSubWeapon = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_MODELSYSWEAP, "UPDATE charainfo SET ModelSystemWeapon = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_MODELEQUIP, "UPDATE charainfo SET ModelEquip = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_EMOTEMODETYPE, "UPDATE charainfo SET EmoteModeType = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_FIRSTLOGINTIME, "UPDATE charainfo SET FirstLoginTime = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_LANGUAGE, "UPDATE charainfo SET Language = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_ISNEWGAME, "UPDATE charainfo SET IsNewGame = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_ISNEWADV, "UPDATE charainfo SET IsNewAdventurer = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_TERRITORY,
                    "UPDATE charainfo SET TerritoryType = ?, TerritoryId = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_POS,
                    "UPDATE charainfo SET OPosX = ?, OPosY = ?, OPosZ = ?, OPosR = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_CLASS, "UPDATE charainfo SET Class = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_STATUS, "UPDATE charainfo SET Status = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_TOTALPLAYTIME, "UPDATE charainfo SET TotalPlayTime = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_HOMEPOINT, "UPDATE charainfo SET Homepoint = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_FAVOPOINT, "UPDATE charainfo SET FavoritePoint = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_TITLE, "UPDATE charainfo SET ActiveTitle = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_TITLELIST, "UPDATE charainfo SET TitleList = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_AETHERYTE, "UPDATE charainfo SET Aetheryte = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_HOWTO, "UPDATE charainfo SET HowTo = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_MINIONS, "UPDATE charainfo SET Minions = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_MOUNTS, "UPDATE charainfo SET Mounts = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_GEARSET, "UPDATE charainfo SET EquippedMannequin = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_CONFIGFLAGS, "UPDATE charainfo SET ConfigFlags = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_QUESTCOMPLETE, "UPDATE charainfo SET QuestCompleteFlags = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_OPENINGSEQ, "UPDATE charainfo SET OpeningSequence = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_QUESTTRACKING, "UPDATE charainfo SET QuestTracking = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_GRANDCOMPANY, "UPDATE charainfo SET GrandCompany = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_GRANDCOMPANYRANKS, "UPDATE charainfo SET GrandCompanyRank = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_DISCOVERY, "UPDATE charainfo SET Discovery = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_GMRANK, "UPDATE charainfo SET GMRank = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_EQUIPDISPLAYFLAGS, "UPDATE charainfo SET EquipDisplayFlags = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_UNLOCKS, "UPDATE charainfo SET Unlocks = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_UP_CFPENATLY, "UPDATE charainfo SET CFPenaltyUntil = ? WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );

  /// SEARCH INFO
  prepareStatement( CHARA_SEARCHINFO_INS,
                    "INSERT INTO charainfosearch (CharacterId, UPDATE_DATE ) VALUES ( ?, NOW() );", CONNECTION_BOTH );
  prepareStatement( CHARA_SEARCHINFO_UP_SELECTCLASS,
                    "UPDATE charainfosearch SET SelectClassId = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_SEARCHINFO_UP_SELECTREGION,
                    "UPDATE charainfosearch SET SelectRegion = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_SEARCHINFO_UP_SEARCHCOMMENT,
                    "UPDATE charainfosearch SET SearchComment = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
  prepareStatement( CHARA_SEL_SEARCHINFO, "SELECT * FROM charainfosearch WHERE CharacterId = ?;", CONNECTION_SYNC );

  /// QUEST INFO
  prepareStatement( CHARA_QUEST_INS,
                    "INSERT INTO charaquest ( CharacterId, SlotId, QuestId, Sequence, Flags, Variables_0, "
                    "Variables_1, Variables_2, Variables_3, Variables_4, "
                    "Variables_5, Variables_6 ) VALUES( ?,?,?,?,?,?,?,?,?,?,?,? );", CONNECTION_ASYNC );

  prepareStatement( CHARA_QUEST_UP, "UPDATE charaquest SET Sequence = ?, Flags = ?, Variables_0 = ?, "
                                    "Variables_1 = ?, Variables_2 = ?, Variables_3 = ?, "
                                    "Variables_4 = ?, Variables_5 = ?, Variables_6 = ? "
                                    "WHERE CharacterId = ? AND QuestId = ?;", CONNECTION_ASYNC );

  prepareStatement( CHARA_QUEST_DEL, "DELETE FROM charaquest WHERE CharacterId = ? AND QuestId = ?;",
                    CONNECTION_ASYNC );

  prepareStatement( CHARA_SEL_QUEST, "SELECT * FROM charaquest WHERE CharacterId = ?;", CONNECTION_SYNC );

  /// CLASS INFO
  prepareStatement( CHARA_CLASS_SEL, "SELECT ClassIdx, Exp, Lvl, BorrowAction FROM characlass WHERE CharacterId = ?;",
                    CONNECTION_SYNC );
  prepareStatement( CHARA_CLASS_INS, "INSERT INTO characlass ( CharacterId, ClassIdx, Exp, Lvl, BorrowAction ) VALUES( ?,?,?,?,? );",
                    CONNECTION_BOTH );
  prepareStatement( CHARA_CLASS_UP, "UPDATE characlass SET Exp = ?, Lvl = ?, BorrowAction = ? WHERE CharacterId = ? AND ClassIdx = ?;",
                    CONNECTION_ASYNC );
  prepareStatement( CHARA_CLASS_DEL, "DELETE FROM characlass WHERE CharacterId = ?;", CONNECTION_ASYNC );

  /// INVENTORY INFO
  prepareStatement( CHARA_ITEMINV_INS,
                    "INSERT INTO charaiteminventory ( CharacterId, storageId, UPDATE_DATE ) VALUES ( ?, ?, NOW() );",
                    CONNECTION_BOTH );

  prepareStatement( CHARA_CURRENCYINV_INS,
                    "INSERT INTO charaitemcurrency ( CharacterId, storageId, idx, UPDATE_DATE ) VALUES ( ?, 2000, 2, NOW() );",
                    CONNECTION_BOTH );

  /// ITEM GLOBAL
  prepareStatement( CHARA_ITEMGLOBAL_INS,
                    "INSERT INTO charaglobalitem ( CharacterId, ItemId, catalogId, stack, UPDATE_DATE ) VALUES ( ?, ?, ?, ?, NOW() );",
                    CONNECTION_SYNC );

  prepareStatement( CHARA_ITEMGLOBAL_SELECT,
                    "SELECT catalogId, stack, reservedFlag, signatureId, flags, durability, refine, materia_0, materia_1, "
                    "materia_2, materia_3, materia_4, stain, pattern, buffer_0, buffer_1, buffer_2, buffer_3, buffer_4 "
                    "FROM charaglobalitem WHERE itemId = ?",
                    CONNECTION_SYNC );

  /// CHARA MONSTERNOTE
  prepareStatement( CHARA_MONSTERNOTE_INS,
                    "INSERT INTO charamonsternote ( CharacterId, Category_0, Category_1, Category_2,"
                    "                               Category_3, Category_4, Category_5, Category_6,"
                    "                               Category_7, Category_8, Category_9, Category_10,"
                    "                               Category_11, UPDATE_DATE ) "
                    " VALUES ( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, NOW() );",
                    CONNECTION_SYNC );

  prepareStatement( CHARA_MONSTERNOTE_UP, "UPDATE charamonsternote "
                                          " SET Category_0 = ?,"
                                              " Category_1 = ?,"
                                              " Category_2 = ?,"
                                              " Category_3 = ?,"
                                              " Category_4 = ?,"
                                              " Category_5 = ?,"
                                              " Category_6 = ?,"
                                              " Category_7 = ?,"
                                              " Category_8 = ?,"
                                              " Category_9 = ?,"
                                              " Category_10 = ?,"
                                              " Category_11 = ?"
                                              " WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );

  /// CLASS INFO
  prepareStatement( CHARA_MONSTERNOTE_SEL, "SELECT Category_0, Category_1, Category_2, "
                                                  "Category_3, Category_4, Category_5, "
                                                  "Category_6, Category_7, Category_8, "
                                                  "Category_9, Category_10, Category_11 FROM charamonsternote "
                                                  "WHERE CharacterId = ?;",
                    CONNECTION_SYNC );

  /// CHARA ACHIEVEMENT
  prepareStatement( CHARA_ACHIEV_INS,
                    "INSERT INTO charainfoachievement ( CharacterId, UnlockList, ProgressData, HistoryList, UPDATE_DATE ) "
                    " VALUES ( ?, ?, ?, ?, NOW() );",
                    CONNECTION_SYNC );

  prepareStatement( CHARA_ACHIEV_UP, "UPDATE charainfoachievement "
                                         " SET UnlockList = ?,"
                                         " ProgressData = ?,"
                                         " HistoryList = ?"
                                         " WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );

  prepareStatement( CHARA_ACHIEV_SEL, "SELECT UnlockList, ProgressData, HistoryList FROM charainfoachievement "
                                          "WHERE CharacterId = ?;",
                    CONNECTION_SYNC );


  /// CHARA FRIENDLIST
  prepareStatement( CHARA_FRIENDLIST_INS,
                    "INSERT INTO charainfofriendlist ( CharacterId, CharacterIdList, InviteDataList, UPDATE_DATE ) "
                    " VALUES ( ?, ?, ?, NOW() );",
                    CONNECTION_SYNC );

  prepareStatement( CHARA_FRIENDLIST_UP, "UPDATE charainfofriendlist "
                                          " SET CharacterIdList = ?,"
                                          " InviteDataList = ?"
                                          " WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );

  prepareStatement( CHARA_FRIENDLIST_SEL, "SELECT CharacterIdList, InviteDataList FROM charainfofriendlist "
                                           "WHERE CharacterId = ?;",
                     CONNECTION_SYNC );

  /// CHARA BLACKLIST
  prepareStatement( CHARA_BLACKLIST_INS,
                    "INSERT INTO charainfoblacklist ( CharacterId, CharacterIdList, UPDATE_DATE ) "
                    " VALUES ( ?, ?, NOW() );",
                    CONNECTION_SYNC );

  prepareStatement( CHARA_BLACKLIST_UP, "UPDATE charainfoblacklist "
                                        " SET CharacterIdList = ?"
                                        " WHERE CharacterId = ?;",
                    CONNECTION_ASYNC );

  prepareStatement( CHARA_BLACKLIST_SEL, "SELECT CharacterIdList FROM charainfoblacklist "
                                          " WHERE CharacterId = ?;",
                     CONNECTION_SYNC );

  /// CHARA LINKSHELL
  prepareStatement( CHARA_LINKSHELL_INS,
                    "INSERT INTO infolinkshell ( LinkshellId, MasterCharacterId, CharacterIdList, "
                    "LinkshellName, LeaderIdList, InviteIdList, UPDATE_DATE ) "
                    " VALUES ( ?, ?, ?, ?, ?, ?, NOW() );",
                    CONNECTION_SYNC );

  /// ZONE QUERIES
  prepareStatement( ZONE_SEL_BNPCS_BY_TERI,
                    "SELECT bnpcgroup.territoryTypeId, bnpc.TerritoryName, bnpc.name, bnpc.instanceId, bnpc.x, bnpc.y, bnpc.z, bnpc.BaseId, bnpc.PopWeather, "
                    "bnpc.PopTimeStart, bnpc.PopTimeEnd, bnpc.MoveAI, bnpc.WanderingRange, bnpc.Route, bnpc.EventGroup, bnpc.NameId, bnpc.DropItem, "
                    "bnpc.SenseRangeRate, bnpc.Level, bnpc.ActiveType, bnpc.PopInterval, bnpc.PopRate, bnpc.PopEvent, bnpc.LinkGroup, bnpc.LinkFamily, bnpc.LinkRange,"
                    "bnpc.LinkCountLimit, bnpc.NonpopInitZone, bnpc.InvalidRepop, bnpc.LinkParent, bnpc.LinkOverride, bnpc.LinkReply, bnpc.HorizontalPopRange, "
                    "bnpc.VerticalPopRange, bnpc.BNpcBaseData, bnpc.RepopId, bnpc.BNPCRankId, bnpc.TerritoryRange, bnpc.BoundInstanceID, bnpc.FateLayoutLabelId,"
                    "bnpc.NormalAI, bnpc.ServerPathId, bnpc.EquipmentID, bnpc.CustomizeID, bnpc.rotation, bnpc.Nonpop, bnpc.groupid "
                    "FROM battlenpc as bnpc LEFT JOIN battlenpcgroupmapping AS bnpcgroup "
                    "ON bnpc.groupid = bnpcgroup.layergroupid where bnpcgroup.territorytypeid = ?;",
                    CONNECTION_BOTH );

  prepareStatement( CHARA_ITEMGLOBAL_UP,
                    "UPDATE charaglobalitem SET stack = ?, durability = ?, stain = ?, pattern = ? WHERE ItemId = ?;",
                    CONNECTION_BOTH );

  prepareStatement( CHARA_ITEMGLOBAL_DELETE,
                    "UPDATE charaglobalitem SET deleted = 1 WHERE ItemId = ?;",
                    CONNECTION_BOTH );

  /// HOUSING
  prepareStatement( HOUSING_HOUSE_INS,
                    "INSERT INTO house ( LandSetId, HouseId, HouseName ) VALUES ( ?, ?, ? );",
                    CONNECTION_BOTH );

  prepareStatement( HOUSING_HOUSE_UP,
                    "UPDATE house SET BuildTime = ?, Aetheryte = ?, Comment = ?, HouseName = ?, Endorsements = ? WHERE HouseId = ?;",
                    CONNECTION_BOTH );

  prepareStatement( HOUSING_HOUSE_DEL,
                    "DELETE from house WHERE HouseId = ?;",
                    CONNECTION_BOTH );

  prepareStatement( LAND_INV_SEL_ALL,
                    "SELECT houseiteminventory.*, charaglobalitem.catalogId, charaglobalitem.stain, charaglobalitem.CharacterId, "
                    "landplaceditems.PosX, landplaceditems.PosY, landplaceditems.PosZ, landplaceditems.Rotation "
                    "FROM houseiteminventory "
                    "LEFT JOIN charaglobalitem "
                    "ON houseiteminventory.ItemId = charaglobalitem.itemId "
                    "LEFT JOIN landplaceditems "
                    "ON houseiteminventory.ItemId = landplaceditems.ItemId;",
                    CONNECTION_BOTH );

  prepareStatement( LAND_INV_SEL_HOUSE,
                    "SELECT LandIdent, ContainerId, ItemId, SlotId FROM houseiteminventory WHERE LandIdent = ?",
                    CONNECTION_SYNC );

  prepareStatement( LANDSET_SEL,
                    "SELECT * FROM land WHERE LandSetId = ?;",
                    CONNECTION_SYNC );

  prepareStatement( LAND_SEL_ALL,
                    "SELECT land.*, house.Welcome, house.Aetheryte, house.Comment, house.HouseName, house.BuildTime, house.Endorsements "
                    "FROM land "
                    "LEFT JOIN house "
                    "ON land.HouseId = house.HouseId;",
                    CONNECTION_SYNC );

  prepareStatement( LAND_INV_UP,
                    "INSERT INTO houseiteminventory ( LandIdent, ContainerId, SlotId, ItemId ) "
                    "VALUES ( ?, ?, ?, ? ) "
                    "ON DUPLICATE KEY UPDATE ItemId = ?;",
                    CONNECTION_BOTH );

  prepareStatement( LAND_INV_DEL,
                    "DELETE FROM houseiteminventory "
                    "WHERE LandIdent = ? AND ContainerId = ? AND SlotId = ?;",
                    CONNECTION_BOTH );

  prepareStatement( LAND_INV_UP_ITEMPOS,
                    "INSERT INTO landplaceditems ( ItemId, PosX, PosY, PosZ, Rotation ) "
                    "VALUES ( ?, ?, ?, ?, ? ) "
                    "ON DUPLICATE KEY UPDATE PosX = ?, PosY = ?, PosZ = ?, Rotation = ?;",
                    CONNECTION_BOTH );

  prepareStatement( LAND_INV_DEL_ITEMPOS,
                    "DELETE FROM landplaceditems "
                    "WHERE ItemId = ?;",
                    CONNECTION_BOTH );

  prepareStatement( LINKSHELL_SEL_ALL,
                    "SELECT LinkshellId, MasterCharacterId, CharacterIdList, LinkshellName, LeaderIdList, InviteIdList "
                    "FROM infolinkshell "
                    "ORDER BY LinkshellId ASC;",
                    CONNECTION_SYNC );

  prepareStatement( LINKSHELL_UP,
                    "UPDATE infolinkshell SET CharacterIdList = ?, LinkshellName = ?, LeaderIdList = ?, InviteIdList = ?, MasterCharacterId = ? WHERE LinkshellId = ?;",
                    CONNECTION_BOTH );

  prepareStatement( LINKSHELL_DEL,
                    "DELETE FROM infolinkshell WHERE LinkshellId = ?;",
                    CONNECTION_BOTH );

  prepareStatement( FC_SEL_ALL,
                    "SELECT FreeCompanyId, MasterCharacterId, FcName, FcTag, FcCredit, FcCreditAccumu, FcRank, FcPoint, CrestId, CreateDate, GrandCompanyID, "
                            "ReputationList, FcStatus, FcBoard, FcMotto, ActiveActionList, ActiveActionLeftTimeList, StockActionList "
                    "FROM freecompany "
                    "ORDER BY FreeCompanyId ASC;",
                    CONNECTION_SYNC );

  prepareStatement( FC_INS,
                    "INSERT INTO freecompany ( FreeCompanyId, MasterCharacterId, FcName, FcTag, FcCredit, FcCreditAccumu, FcRank, FcPoint,"
                                "ReputationList, CrestId, CreateDate, GrandCompanyID, FcStatus, FcBoard, FcMotto ) VALUES ( ?, ?, ?, ?, ?, ?, ?,"
                                "?, ?, ?, ?, ?, ?, ?, ? );",
                    CONNECTION_BOTH );

  prepareStatement( FC_UP,
                    "UPDATE freecompany SET MasterCharacterId = ?, FcName = ?, FcTag = ?, FcCredit = ?, FcCreditAccumu = ?,"
                            "FcRank = ?, FcPoint = ?, ReputationList = ?, CrestId = ?,"
                            "CreateDate = ?, GrandCompanyID = ?, FcStatus = ?, FcBoard = ?, "
                            "FcMotto = ?, ActiveActionList = ?, ActiveActionLeftTimeList = ?, StockActionList = ? "
                            "WHERE FreeCompanyId = ?;",
                    CONNECTION_BOTH );

  prepareStatement( FC_DEL,
                    "DELETE FROM freecompany WHERE FreeCompanyId = ?;",
                    CONNECTION_BOTH );

  prepareStatement( FC_MEMBERS_SEL_ALL,
                    "SELECT FreeCompanyId, FcMemberId, HierarchyType, LastLogout "
                    "FROM fcmember "
                    "ORDER BY FreeCompanyId ASC;",
                    CONNECTION_SYNC );

  prepareStatement( FC_MEMBERS_SEL_FC,
                    "SELECT FcMemberId, HierarchyType, LastLogout "
                    "FROM fcmember "
                    "WHERE FreeCompanyId = ?;",
                    CONNECTION_SYNC );

  prepareStatement( FC_MEMBERS_INS,
                    "INSERT INTO fcmember ( FreeCompanyId, FcMemberId, HierarchyType, LastLogout ) VALUES ( ?, ?, ?, ? );",
                    CONNECTION_BOTH );

  prepareStatement( FC_MEMBERS_UP,
                    "UPDATE fcmember SET HierarchyType = ?, LastLogout = ? "
                    "WHERE FcMemberId = ?;",
                    CONNECTION_BOTH );

  prepareStatement( FC_DEL,
                    "DELETE FROM fcmember WHERE FcMemberId = ?;",
                    CONNECTION_BOTH );

}
