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

}