#include "DbLoader.h"
#include <mysqld_error.h>
#include "ZoneDbConnection.h"
#include "DbWorkerPool.h"
#include "Logging/Logger.h"
#include "Framework.h"

extern Core::Framework g_fw;

Core::Db::DbLoader::DbLoader()
{
}

template< class T >
Core::Db::DbLoader& Core::Db::DbLoader::addDb( Core::Db::DbWorkerPool< T >& pool, const ConnectionInfo& info )
{

  m_open.push( [ this, info, &pool ]()->bool
               {

                 auto pLog = g_fw.get< Logger >();
                 const uint8_t asyncThreads = info.asyncThreads;
                 const uint8_t synchThreads = info.syncThreads;

                 if( asyncThreads < 1 || asyncThreads > 32 )
                 {
                   pLog->error(
                     "database: invalid number of worker threads specified. Please pick a value between 1 and 32." );
                   return false;
                 }

                 pool.setConnectionInfo( info, asyncThreads, synchThreads );
                 if( uint32_t error = pool.open() )
                 {
                   // Database does not exist
                   if( error == ER_BAD_DB_ERROR )
                   {
                     return false;
                   }

                   if( error )
                   {
                     pLog->error( "DatabasePool failed to open." );
                     return false;
                   }
                 }

                 m_close.push( [ &pool ]
                               { pool.close(); } );
                 return true;
               } );


  m_prepare.push( [ this, info, &pool ]()->bool
                  {
                    if( !pool.prepareStatements() )
                    {
                      auto pLog = g_fw.get< Logger >();
                      pLog->error( "Could not prepare statements of the database, see log for details." );
                      return false;
                    }
                    return true;
                  } );

  return *this;
}

bool Core::Db::DbLoader::initDbs()
{
  if( !openDatabases() )
    return false;

  if( !prepareStatements() )
    return false;

  return true;
}

bool Core::Db::DbLoader::openDatabases()
{
  return process( m_open );
}

bool Core::Db::DbLoader::prepareStatements()
{
  return process( m_prepare );
}

bool Core::Db::DbLoader::process( std::queue< Predicate >& queue )
{
  while( !queue.empty() )
  {
    if( !queue.front()() )
    {
      // Close all open databases which have a registered close operation
      while( !m_close.empty() )
      {
        m_close.top()();
        m_close.pop();
      }

      return false;
    }

    queue.pop();
  }
  return true;
}

template
Core::Db::DbLoader&
Core::Db::DbLoader::addDb< Core::Db::ZoneDbConnection >( Core::Db::DbWorkerPool< Core::Db::ZoneDbConnection >&,
                                                          const ConnectionInfo& );

