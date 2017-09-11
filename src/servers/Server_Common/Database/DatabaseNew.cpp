#include "DatabaseNew.h"

#include "src/servers/Server_Common/Logging/Logger.h"

extern Core::Logger g_log;

Core::Db::DatabaseNew::DatabaseNew()
{
   m_driver = get_driver_instance();
}

Core::Db::DatabaseNew::~DatabaseNew()
{

}

bool Core::Db::DatabaseNew::initialize( const DbParams& params )
{
   uint32_t i;

   g_log.info( "Database: Connecting to " + params.hostname + ", database " + params.databaseName + "..." );

   m_pConnections = new DbConnection[params.connectionCount];
   for( i = 0; i < params.connectionCount; ++i )
   {
      try
      {
         std::string host = "tcp://" + params.hostname + ":" + std::to_string( params.port );
         m_pConnections[i].conn = m_driver->connect( host.c_str(), params.username.c_str(), params.password.c_str() );
         m_pConnections[i].conn->setSchema( params.databaseName.c_str() );
         bool myTrue = true;
         m_pConnections[i].conn->setClientOption( "OPT_RECONNECT", &myTrue );
         m_pConnections[i].conn->setClientOption( "SET_CHARSET_NAME", "utf8" );
      }
      catch( sql::SQLException &e )
      {
         g_log.fatal( "Database: Connection failed: " + std::string( e.what() ) );
         return false;
      }
   }


   return true;
}