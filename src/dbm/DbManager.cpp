#include "DbManager.h"
#include <MySqlConnector.h>
DbManager::DbManager( const std::string& host, const std::string& database, const std::string& user, const std::string& pw, uint16_t port ) :
  m_host( host ),
  m_database( database ),
  m_user( user ),
  m_password( pw ),
  m_port( port )	
{
}

DbManager::~DbManager()
{

}

bool DbManager::execute( const std::string& sql )
{
  try
  {
    auto stmt = m_pConnection->createStatement();
    bool result = stmt->execute( sql );
    return result;
  }
  catch( std::runtime_error& e )
  {
    m_lastError = e.what();
    return false;
  }
}

bool DbManager::connect()
{
  std::shared_ptr< Mysql::MySqlBase > base( new Mysql::MySqlBase() );
  Mysql::optionMap options;
  options[ Mysql::MYSQL_OPT_RECONNECT ] = "1";
  options[ Mysql::MYSQL_SET_CHARSET_NAME ] = "utf8";

  try
  {
    m_pConnection = base->connect( m_host, m_user, m_password, options, m_port );
  }
  catch( std::runtime_error& e )
  {
    m_lastError = e.what();
    return false;
  }
  return true;
}

bool DbManager::selectSchema()
{
  if( !m_pConnection )
  {
    m_lastError = "No valid db connection!";	  
    return false;
  }

  try
  {
    m_pConnection->setSchema( m_database );
  }
  catch( std::runtime_error& e )
  {
    m_lastError = e.what();
    return false;
  }
  return true;
}

const std::string& DbManager::getLastError()
{
  return m_lastError;
}

void DbManager::setMode( Mode mode )
{
  m_mode = mode;
}

Mode DbManager::getMode() const
{
  return m_mode;
}

bool DbManager::performAction()
{
  bool result = false;
  execute( " SET autocommit = 0 " );
  m_pConnection->beginTransaction();

  switch( m_mode )
  {
    case Mode::INIT:
      result = modeInit();
      break;
    case Mode::LIQUIDATE:
      break;
    case Mode::UPDATE:
      break;
    case Mode::CHECK:
      break;
    case Mode::CLEAN_CHARS:
      break;
  }
  if( !result )
    m_pConnection->rollbackTransaction();
  else
    m_pConnection->commitTransaction();

  return result;
}

bool DbManager::modeInit()
{

  bool result = false;

  if( selectSchema() )
  {
    m_lastError = "Database already existing, use <liquidate> mode first to remove it.";
    return false;
  }

  if( !execute( "CREATE DATABASE " + m_database ) )
    return false;

  if( !execute( "CREATE TABLE `dbversion` (\n"
                "  `major` int(11) NOT NULL,\n"
                "  `minor` int(11) NOT NULL\n"
                ") ENGINE=InnoDB DEFAULT CHARSET=latin1;" ) )
    return false;


  return false;
}
