#include "CharaDbConnection.h"
#include <MySqlConnector.h>

Core::Db::CharaDbConnection::CharaDbConnection( ConnectionInfo& connInfo ) : DbConnection( connInfo )
{
}

Core::Db::CharaDbConnection::CharaDbConnection( Core::LockedWaitQueue< boost::shared_ptr< Operation > >* q,
                                                ConnectionInfo& connInfo) : DbConnection( q, connInfo )
{
}

Core::Db::CharaDbConnection::~CharaDbConnection()
{
}

void Core::Db::CharaDbConnection::doPrepareStatements()
{
   if( !m_reconnecting )
      m_stmts.resize( MAX_STATEMENTS );

   /// CHARA
   prepareStatement( CHARA_SEL, "SELECT ContentId, Name, Hp, Mp, Tp, Gp, Mode, Mount, InvincibleGM, Voice, "
                                       "Customize, ModelMainWeapon, ModelSubWeapon, ModelSystemWeapon, "
                                       "ModelEquip, EmoteModeType, FirstLoginTime, Language, IsNewGame, "
                                       "IsNewAdventurer, TerritoryType, TerritoryId, PosX, PosY, PosZ, PosR, "
                                       "OTerritoryType, OTerritoryId, OPosX, OPosY, OPosZ, OPosR, GuardianDeity, "
                                       "BirthDay, BirthMonth, Class, Status, TotalPlayTime, FirstClass, HomePoint, "
                                       "FavoritePoint, RestPoint, StartTown, ActiveTitle, TitleList, Achievement, "
                                       "Aetheryte, HowTo, Minions, Mounts, Orchestrion, EquippedMannequin, ConfigFlags, "
                                       "QuestCompleteFlags, OpeningSequence, QuestTracking, GrandCompany, "
                                       "GrandCompanyRank, Discovery, GMRank, Unlocks, CFPenaltyUntil "
                                       "FROM charainfo WHERE CharacterId = ?;", CONNECTION_SYNC );


   prepareStatement( CHARA_UP,
                     "UPDATE charainfo SET "
                     "Hp = ?, Mp = ?, Tp = ?, Gp = ?, Mode = ?, Mount = ?, InvincibleGM = ?, Voice = ?, "
                     "Customize = ?, ModelMainWeapon = ?, ModelSubWeapon = ?, ModelSystemWeapon = ?, "
                     "ModelEquip = ?, EmoteModeType = ?, Language = ?, IsNewGame = ?, IsNewAdventurer = ?, "
                     "TerritoryType = ?, TerritoryId = ?, PosX = ?, PosY = ?, PosZ = ?, PosR = ?, "
                     "OTerritoryType = ?, OTerritoryId = ?, OPosX = ?, OPosY = ?, OPosZ = ?, OPosR = ?, "
                     "Class = ?, Status = ?, TotalPlayTime = ?, HomePoint = ?, FavoritePoint = ?, RestPoint = ?, "
                     "ActiveTitle = ?, TitleList = ?, Achievement = ?, Aetheryte = ?, HowTo = ?, Minions = ?, Mounts = ?, Orchestrion = ?, "
                     "EquippedMannequin = ?, ConfigFlags = ?, QuestCompleteFlags = ?, OpeningSequence = ?, "
                     "QuestTracking = ?, GrandCompany = ?, GrandCompanyRank = ?, Discovery = ?, GMRank = ?, Unlocks = ?, "
                     "CFPenaltyUntil = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );


   prepareStatement( CHARA_SEL_MINIMAL, "SELECT Name, Customize, ModelEquip, TerritoryId, GuardianDeity, "
                                               "Class, ContentId, BirthDay, BirthMonth "
                                                "FROM charainfo WHERE CharacterId = ?;", CONNECTION_SYNC );

   prepareStatement( CHARA_INS, "INSERT INTO charainfo (AccountId, CharacterId, ContentId, Name, Hp, Mp, "
                                        "Customize, Voice, IsNewGame, TerritoryId, PosX, PosY, PosZ, PosR, ModelEquip, "
                                        "IsNewAdventurer, GuardianDeity, Birthday, BirthMonth, Class, Status, FirstClass, "
                                        "HomePoint, StartTown, Discovery, HowTo, QuestCompleteFlags, Unlocks, QuestTracking, "
                                        "Aetheryte, GMRank, Mounts, Orchestrion, UPDATE_DATE ) "
                                        "VALUES ( ?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,NOW() );",
                     CONNECTION_SYNC );

   prepareStatement( CHARA_UP_NAME, "UPDATE charainfo SET Name = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_HPMP, "UPDATE charainfo SET Hp = ?, Mp = ?, Tp = ?, Gp = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_MODE, "UPDATE charainfo SET Mode = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_MOUNT, "UPDATE charainfo SET Mount = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_INVINCIBLE, "UPDATE charainfo SET InvincibleGM = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_CUSTOMIZE, "UPDATE charainfo SET Customize = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_MODELMAINWEAP, "UPDATE charainfo SET ModelMainWeapon = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_MODELSUBWEAP, "UPDATE charainfo SET ModelSubWeapon = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_MODELSYSWEAP, "UPDATE charainfo SET ModelSystemWeapon = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_MODELEQUIP, "UPDATE charainfo SET ModelEquip = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_EMOTEMODETYPE, "UPDATE charainfo SET EmoteModeType = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_FIRSTLOGINTIME, "UPDATE charainfo SET FirstLoginTime = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_LANGUAGE, "UPDATE charainfo SET Language = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_ISNEWGAME, "UPDATE charainfo SET IsNewGame = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_ISNEWADV, "UPDATE charainfo SET IsNewAdventurer = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_TERRITORY, "UPDATE charainfo SET TerritoryType = ?, TerritoryId = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_POS, "UPDATE charainfo SET OPosX = ?, OPosY = ?, OPosZ = ?, OPosR = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_CLASS, "UPDATE charainfo SET Class = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_STATUS, "UPDATE charainfo SET Status = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_TOTALPLAYTIME, "UPDATE charainfo SET TotalPlayTime = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_HOMEPOINT, "UPDATE charainfo SET Homepoint = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_FAVOPOINT, "UPDATE charainfo SET FavoritePoint = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_TITLE, "UPDATE charainfo SET ActiveTitle = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_TITLELIST, "UPDATE charainfo SET TitleList = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_ACHIEVEMENTS, "UPDATE charainfo SET Achievement = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_AETHERYTE, "UPDATE charainfo SET Aetheryte = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_HOWTO, "UPDATE charainfo SET HowTo = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_MINIONS, "UPDATE charainfo SET Minions = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_MOUNTS, "UPDATE charainfo SET Mounts = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_GEARSET, "UPDATE charainfo SET EquippedMannequin = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_CONFIGFLAGS, "UPDATE charainfo SET ConfigFlags = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_QUESTCOMPLETE, "UPDATE charainfo SET QuestCompleteFlags = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_OPENINGSEQ, "UPDATE charainfo SET OpeningSequence = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_QUESTTRACKING, "UPDATE charainfo SET QuestTracking = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_GRANDCOMPANY, "UPDATE charainfo SET GrandCompany = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_GRANDCOMPANYRANKS, "UPDATE charainfo SET GrandCompanyRank = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_DISCOVERY, "UPDATE charainfo SET Discovery = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_GMRANK, "UPDATE charainfo SET GMRank = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_UNLOCKS, "UPDATE charainfo SET Unlocks = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_UP_CFPENATLY, "UPDATE charainfo SET CFPenaltyUntil = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );

   /// SEARCH INFO
   prepareStatement( CHARA_SEARCHINFO_INS, "INSERT INTO charainfosearch (CharacterId, UPDATE_DATE ) VALUES ( ?, NOW() );", CONNECTION_BOTH );
   prepareStatement( CHARA_SEARCHINFO_UP_SELECTCLASS, "UPDATE charainfosearch SET SelectClassId = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_SEARCHINFO_UP_SELECTREGION, "UPDATE charainfosearch SET SelectRegion = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_SEARCHINFO_UP_SEARCHCOMMENT, "UPDATE charainfosearch SET SearchComment = ? WHERE CharacterId = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_SEARCHINFO_SEL, "SELECT * FROM charainfosearch WHERE CharacterId = ?;", CONNECTION_SYNC );

   /// QUEST INFO
   prepareStatement( CHARA_QUEST_INS, "INSERT INTO charaquestnew ( CharacterId, SlotId, QuestId, Sequence, Flags, Variables_0, "
                                                                  "Variables_1, Variables_2, Variables_3, Variables_4, "
                                                                  "Variables_5, Variables_6 ) VALUES( ?,?,?,?,?,?,?,?,?,?,?,? );", CONNECTION_ASYNC );

   prepareStatement( CHARA_QUEST_UP, "UPDATE charaquestnew SET Sequence = ?, Flags = ?, Variables_0 = ?, "
                                                              "Variables_1 = ?, Variables_2 = ?, Variables_3 = ?, "
                                                              "Variables_4 = ?, Variables_5 = ?, Variables_6 = ? "
                                                              "WHERE CharacterId = ? AND QuestId = ?;", CONNECTION_ASYNC );

   prepareStatement( CHARA_QUEST_DEL, "DELETE FROM charaquestnew WHERE CharacterId = ? AND QuestId = ?;", CONNECTION_ASYNC );

   prepareStatement( CHARA_QUEST_SEL, "SELECT * FROM charaquestnew WHERE CharacterId = ?;", CONNECTION_SYNC );

   /// CLASS INFO
   prepareStatement( CHARA_CLASS_SEL, "SELECT ClassIdx, Exp, Lvl FROM characlass WHERE CharacterId = ?;", CONNECTION_SYNC );
   prepareStatement( CHARA_CLASS_INS, "INSERT INTO characlass ( CharacterId, ClassIdx, Exp, Lvl ) VALUES( ?,?,?,? );", CONNECTION_BOTH );
   prepareStatement( CHARA_CLASS_UP, "UPDATE characlass SET Exp = ?, Lvl = ? WHERE CharacterId = ? AND ClassIdx = ?;", CONNECTION_ASYNC );
   prepareStatement( CHARA_CLASS_DEL, "DELETE FROM characlass WHERE CharacterId = ?;", CONNECTION_ASYNC );

   /// INVENTORY INFO
   prepareStatement( CHARA_ITEMINV_INS, "INSERT INTO charaiteminventory ( CharacterId, storageId, UPDATE_DATE ) VALUES ( ?, ?, NOW() );", CONNECTION_BOTH );

   /// ITEM GLOBAL
   prepareStatement( CHARA_ITEMGLOBAL_INS, "INSERT INTO charaglobalitem ( CharacterId, ItemId, catalogId, UPDATE_DATE ) VALUES ( ?, ?, ?, NOW() );", CONNECTION_BOTH );




}
