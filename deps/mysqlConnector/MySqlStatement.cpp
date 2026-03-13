#include "MySqlStatement.h"
#include "MySqlConnection.h"
#include "MySqlResultSet.h"
#include "detail/MySqlUtil.h"

namespace
{
  MYSQL* nativeConnection( Mysql::NativeConnectionHandle handle )
  {
    return static_cast< MYSQL* >( handle );
  }
}// namespace

std::shared_ptr< Mysql::Connection > Mysql::Statement::getConnection()
{
  return m_pConnection;
}

Mysql::Statement::Statement( std::shared_ptr< Mysql::Connection > conn ) : m_pConnection( conn )
{
}

void Mysql::Statement::doQuery( const std::string& q )
{
  mysql_real_query( nativeConnection( m_pConnection->m_pRawCon ), q.c_str(), static_cast< unsigned long >( q.length() ) );

  if( errNo() )
    throw std::runtime_error( m_pConnection->getError() );

  m_warningsCount = getWarningCount();
}

bool Mysql::Statement::execute( const std::string& sql )
{
  doQuery( sql );
  bool ret = mysql_field_count( nativeConnection( m_pConnection->m_pRawCon ) ) == 0;
  m_lastUpdateCount = mysql_affected_rows( nativeConnection( m_pConnection->m_pRawCon ) );
  return ret;
}

uint64_t Mysql::Statement::getUpdateCount()
{
  return m_lastUpdateCount;
}

uint32_t Mysql::Statement::getWarningCount()
{
  return mysql_warning_count( nativeConnection( m_pConnection->m_pRawCon ) );
}

uint32_t Mysql::Statement::errNo()
{
  return mysql_errno( nativeConnection( m_pConnection->m_pRawCon ) );
}

std::shared_ptr< Mysql::ResultSet > Mysql::Statement::executeQuery( const std::string& sql, bool streaming )
{
  m_lastUpdateCount = UL64( ~0 );
  doQuery( sql );

  auto result = streaming
    ? mysql_use_result( nativeConnection( m_pConnection->m_pRawCon ) )
    : mysql_store_result( nativeConnection( m_pConnection->m_pRawCon ) );

  if( !result && errNo() != 0 )
    throw std::runtime_error( "Error during executeQuery() : " + std::to_string( errNo() ) + ": " +
                              m_pConnection->getError() );

  return std::make_shared< ResultSet >( result, shared_from_this() );
}

