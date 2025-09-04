#ifndef SAPPHIRE_MYSQLBASE_H
#define SAPPHIRE_MYSQLBASE_H

#include <memory>
#include <string>
#include <map>
#include <cstdint>
#include "MysqlCommon.h"


namespace Mysql
{

using optionMap = std::map< enum mysqlOption, std::string >;

class Connection;

class MySqlBase : public std::enable_shared_from_this< MySqlBase >
{
public:
   MySqlBase();

   ~MySqlBase();

   std::shared_ptr< Connection > connect( const std::string& hostName, const std::string& userName,
                                          const std::string& password, uint16_t port );
   std::shared_ptr< Connection > connect( const std::string& hostName, const std::string& userName,
                                          const std::string& password, const optionMap& map, uint16_t port );

   std::string getVersionInfo();

private:
   MySqlBase( const MySqlBase& );
   void operator=( MySqlBase& );
};

}

#endif //SAPPHIRE_MYSQLBASE_H
