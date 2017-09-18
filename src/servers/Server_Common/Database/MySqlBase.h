#ifndef SAPPHIRE_MYSQLBASE_H
#define SAPPHIRE_MYSQLBASE_H

#include <boost/shared_ptr.hpp>
#include <mysql.h>
#include <string>
#include <map>

namespace Core
{
namespace Db
{

typedef std::map< enum mysql_option, std::string > optionMap;

class Connection;

class MySqlBase
{
public:
   MySqlBase();

   ~MySqlBase();

   Connection * connect( const std::string& hostName, const std::string& userName, const std::string& password );
   Connection * connect( const std::string& hostName, const std::string& userName, const std::string& password, const optionMap& map );

   std::string getVersionInfo();

private:
   MySqlBase( const MySqlBase& );
   void operator=( MySqlBase& );
};

}
}

#endif //SAPPHIRE_MYSQLBASE_H
