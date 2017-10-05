#include "CharaDbConnection.h"
#include <libraries/sapphire/mysqlConnector/MySqlConnector.h>

Core::Db::CharaDbConnection::CharaDbConnection( ConnectionInfo& connInfo ) : DbConnection( connInfo )
{
}

Core::Db::CharaDbConnection::CharaDbConnection( Core::LockedWaitQueue< Operation * >* q,
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

   prepareStatement( CHAR_SEL_LOAD, "SELECT c.Name, c.PrimaryTerritoryId, c.Hp, c.Mp, c.Gp, c.Mode, "
                                           "c.Pos_0_0, c.Pos_0_1, c.Pos_0_2, c.Pos_0_3, c.FirstLogin, "
                                           "c.Customize, c.ModelMainWeapon, c.ModelSubWeapon, c.ModelEquip, "
                                           "cd.GuardianDeity, cd.BirthDay, cd.BirthMonth, cd.Status, cd.Class, "
                                           "cd.Homepoint, cd.HowTo, c.ContentId, c.Voice, cd.QuestCompleteFlags, "
                                           "cd.QuestTracking, c.IsNewGame, cd.Aetheryte, cd.unlocks, cd.Discovery, "
                                           "cd.StartTown, cd.TotalPlayTime, c.IsNewAdventurer, cd.GrandCompany, "
                                           "cd.GrandCompanyRank, cd.CFPenaltyUntil, cd.OpeningSequence, cd.GMRank "
                                           "FROM charabase AS c "
                                           " INNER JOIN charadetail AS cd "
                                           " ON c.CharacterId = cd.CharacterId "
                                           "WHERE c.CharacterId = ?;", CONNECTION_SYNCH );

   prepareStatement( CHAR_SEL_LOAD_CLASSINFO, "SELECT * FROM characlass WHERE CharacterId = ?;", CONNECTION_SYNCH );
   prepareStatement( CHAR_SEL_LOAD_SEARCHINFO, "SELECT * FROM charainfosearch WHERE CharacterId = ?;", CONNECTION_SYNCH );
   prepareStatement( CHAR_SEL_LOAD_QUESTINFO, "SELECT * FROM charaquest WHERE CharacterId = ?;", CONNECTION_SYNCH );







}