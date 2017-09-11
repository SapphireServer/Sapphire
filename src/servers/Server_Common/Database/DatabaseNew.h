#ifndef SAPPHIRE_DATABASENEW_H
#define SAPPHIRE_DATABASENEW_H

#include <mutex>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

namespace Core
{
namespace Db
{

struct DbParams
{
   std::string hostname;
   std::string username;
   std::string password;
   std::string databaseName;
   uint16_t port;
   uint32_t bufferSize;
   uint32_t connectionCount;
};

struct DbConnection
{
   std::mutex lock;
   sql::Connection *conn;
};

class DatabaseNew
{
private:
   sql::Driver * m_driver;
   sql::Connection *m_con;
   sql::Statement *m_stmt;
   sql::ResultSet *m_res;

   DbConnection *m_pConnections;

public:
   DatabaseNew();
   ~DatabaseNew();

   bool initialize( const DbParams& params );


};

}
}




#endif //SAPPHIRE_DATABASENEW_H
