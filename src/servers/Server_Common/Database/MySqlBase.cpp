#include "MySqlBase.h"
#include "Connection.h"

Core::Db::MySqlBase::MySqlBase() 
{
}

Core::Db::MySqlBase::~MySqlBase()
{

}

std::string Core::Db::MySqlBase::getVersionInfo()
{
   return std::string( mysql_get_client_info() );
}

Core::Db::Connection * Core::Db::MySqlBase::connect( const std::string& hostName, const std::string& userName, const std::string& password )
{
   return new Connection( this, hostName, userName, password );
}

Core::Db::Connection * Core::Db::MySqlBase::connect( const std::string& hostName, const std::string& userName, const std::string& password, const optionMap& options )
{
   return new Connection( this, hostName, userName, password, options );
}
