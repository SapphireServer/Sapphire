#include "CharaDbConnection.h"
#include <libraries/sapphire/mysqlConnector/MySqlConnector.h>

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

   prepareStatement( CHAR_INS_TEST, "INSERT INTO zoneservers ( id, ip, port ) VALUES ( ?, ?, ?);", CONNECTION_BOTH );

   prepareStatement( CHAR_SEL_LOAD, "SELECT ContentId, Name, Hp, Mp, Tp, Gp, Mode, Mount, InvincibleGM, Voice, "
                                           "Customize, ModelMainWeapon, ModelSubWeapon, ModelSystemWeapon, "
                                           "ModelEquip, EmoteModeType, FirstLoginTime, Language, IsNewGame, "
                                           "IsNewAdventurer, TerritoryType, TerritoryId, PosX, PosY, PosZ, PosR, "
                                           "OTerritoryType, OTerritoryId, OPosX, OPosY, OPosZ, OPosR, GuardianDeity, "
                                           "BirthDay, BirthMonth, Class, Status, TotalPlayTime, FirstClass, HomePoint, "
                                           "FavoritePoint, RestPoint, StartTown, ActiveTitle, TitleList, Achievement, "
                                           "Aetheryte, HowTo, Minions, Mounts, EquippedMannequin, ConfigFlags, "
                                           "QuestCompleteFlags, OpeningSequence, QuestTracking, GrandCompany, "
                                           "GrandCompanyRank, Discovery, GMRank, Unlocks, CFPenaltyUntil "
                                           "FROM charainfo WHERE CharacterId = ?;", CONNECTION_SYNCH );


   prepareStatement( CHAR_SEL_LOAD_MINIMAL, "SELECT Name, Customize, ModelEquip, TerritoryId, GuardianDeity, "
                                            "Class, ContentId, BirthDay, BirthMonth "
                                            "FROM charainfo WHERE CharacterId = ?;", CONNECTION_SYNCH );

   prepareStatement( CHAR_SEL_LOAD_CLASSINFO, "SELECT * FROM characlass WHERE CharacterId = ?;", CONNECTION_SYNCH );
   prepareStatement( CHAR_SEL_LOAD_SEARCHINFO, "SELECT * FROM charainfosearch WHERE CharacterId = ?;", CONNECTION_SYNCH );
   prepareStatement( CHAR_SEL_LOAD_QUESTINFO, "SELECT * FROM charaquest WHERE CharacterId = ?;", CONNECTION_SYNCH );

   prepareStatement( CHAR_INS_CHARINFO, "INSERT INTO charainfo (AccountId, CharacterId, ContentId, Name, Hp, Mp, "
                                        "Customize, Voice, IsNewGame, TerritoryId, PosX, PosY, PosZ, PosR, ModelEquip, "
                                        "IsNewAdventurer, GuardianDeity, Birthday, BirthMonth, Class, Status, FirstClass, "
                                        "HomePoint, StartTown, Discovery, HowTo, QuestCompleteFlags, Unlocks, QuestTracking, "
                                        "Aetheryte, GMRank, UPDATE_DATE ) "
                                        "VALUES ( ?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,NOW() );",
                     CONNECTION_SYNCH );









}