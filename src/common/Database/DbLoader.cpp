#include "DbLoader.h"
#include <mysqld_error.h>
#include "ZoneDbConnection.h"
#include "DbWorkerPool.h"
#include "Logging/Logger.h"

Sapphire::Db::DbLoader::DbLoader()
{
}

template< class T >
Sapphire::Db::DbLoader& Sapphire::Db::DbLoader::addDb( Sapphire::Db::DbWorkerPool< T >& pool, const ConnectionInfo& info )
{

  m_open.push( [ this, info, &pool ]()->bool
               {
                 const uint8_t asyncThreads = info.asyncThreads;
                 const uint8_t synchThreads = info.syncThreads;

                 if( asyncThreads < 1 || asyncThreads > 32 )
                 {
                   Logger::error(
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
                     Logger::error( "DatabasePool failed to open." );
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
                      Logger::error( "Could not prepare statements of the database, see log for details." );
                      return false;
                    }
                    return true;
                  } );

  return *this;
}

bool Sapphire::Db::DbLoader::initDbs()
{
  if( !openDatabases() )
    return false;

  if( !prepareStatements() )
    return false;

  return true;
}

bool Sapphire::Db::DbLoader::openDatabases()
{
  return process( m_open );
}

bool Sapphire::Db::DbLoader::prepareStatements()
{
  return process( m_prepare );
}

bool Sapphire::Db::DbLoader::process( std::queue< Predicate >& queue )
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
Sapphire::Db::DbLoader&
Sapphire::Db::DbLoader::addDb< Sapphire::Db::ZoneDbConnection >( Sapphire::Db::DbWorkerPool< Sapphire::Db::ZoneDbConnection >&,
                                                                 const ConnectionInfo& );

