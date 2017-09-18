#include "Statement.h"
#include "Connection.h"
#include "ResultSet.h"
#include "mysql_util.h"

Core::Db::Connection* Core::Db::Statement::getConnection()
{
   return m_pConnection;
}

Core::Db::Statement::Statement( Core::Db::Connection *conn ) :
   m_pConnection( conn )
{

}

void Core::Db::Statement::doQuery( const std::string &q )
{
   mysql_real_query( m_pConnection->getRawCon(), q.c_str(), q.length() );

   if( errNo() )
      throw std::runtime_error( m_pConnection->getError() );

   m_warningsCount = getWarningCount();
}

bool Core::Db::Statement::execute( const std::string &sql )
{
   doQuery( sql );
   bool ret = mysql_field_count( m_pConnection->getRawCon() ) == 0;
   m_lastUpdateCount = mysql_affected_rows( m_pConnection->getRawCon() );
   return ret;
}

uint64_t Core::Db::Statement::getUpdateCount()
{
   return m_lastUpdateCount;
}

uint32_t Core::Db::Statement::getWarningCount()
{
   return mysql_warning_count( m_pConnection->getRawCon() );
}

uint32_t Core::Db::Statement::errNo()
{
   return mysql_errno( m_pConnection->getRawCon() );
}

Core::Db::ResultSet* Core::Db::Statement::executeQuery( const std::string &sql )
{
   m_lastUpdateCount = UL64(~0);
   doQuery( sql );

   return new ResultSet( mysql_store_result( m_pConnection->getRawCon() ), this );
}

Core::Db::ResultSet *Core::Db::Statement::getResultSet()
{
   if( errNo() != 0 )
      throw std::runtime_error( "Error during getResultSet() : " + std::to_string( errNo() ) + ": " +
                                        m_pConnection->getError() );

   return new ResultSet( mysql_store_result( m_pConnection->getRawCon() ), this );
}

