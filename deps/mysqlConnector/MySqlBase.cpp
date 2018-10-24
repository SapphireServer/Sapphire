#include "MySqlBase.h"
#include "Connection.h"
#include <memory>

Mysql::MySqlBase::MySqlBase() 
{
}

Mysql::MySqlBase::~MySqlBase()
{

}

std::string Mysql::MySqlBase::getVersionInfo()
{
   return std::string( mysql_get_client_info() );
}

std::shared_ptr< Mysql::Connection > Mysql::MySqlBase::connect( const std::string& hostName, const std::string& userName,
                                                                const std::string& password, uint16_t port = 3306 )
{
   return std::make_shared< Mysql::Connection >( shared_from_this(), hostName, userName, password, port );
}

std::shared_ptr< Mysql::Connection > Mysql::MySqlBase::connect( const std::string& hostName, const std::string& userName,
                                                                const std::string& password, const optionMap& options,
                                                                uint16_t port = 3306 )
{
   return std::shared_ptr< Mysql::Connection >( new Mysql::Connection( shared_from_this(), hostName, userName, password, options, port ) );
}
