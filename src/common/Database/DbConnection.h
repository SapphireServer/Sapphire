#ifndef _SAPPHIRE_DBCONNECTION_H
#define _SAPPHIRE_DBCONNECTION_H

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include "Util/LockedWaitQueue.h"
#include "DbCommon.h"

namespace Mysql
{
  class Connection;
  class ResultSet;
  class PreparedResultSet;
  class PreparedStatement;
}

namespace Sapphire::Db
{
  class DatabaseWorker;
  class PreparedStatement;
  class Operation;
  class DbWorker;
  using PreparedStmtScopedPtr = std::unique_ptr< PreparedStatement >;

  enum ConnectionFlags
  {
    CONNECTION_ASYNC = 0x1,
    CONNECTION_SYNC = 0x2,
    CONNECTION_BOTH = CONNECTION_ASYNC | CONNECTION_SYNC
  };

  using PreparedStatementMap = std::map< uint32_t, std::pair< std::string, ConnectionFlags > >;

  class DbConnection :
    public std::enable_shared_from_this< DbConnection >
  {
  public:
    // Constructor for synchronous connections.
    DbConnection( ConnectionInfo& connInfo );

    // Constructor for asynchronous connections.
    DbConnection( Common::Util::LockedWaitQueue< std::shared_ptr< Operation > >* queue, ConnectionInfo& connInfo );

    virtual ~DbConnection();

    virtual uint32_t open();

    void close();

    bool prepareStatements();

    bool execute( const std::string& sql );

    bool execute( std::shared_ptr< PreparedStatement > stmt );

    std::shared_ptr< Mysql::ResultSet > query( const std::string& sql );

    std::shared_ptr< Mysql::ResultSet > query( std::shared_ptr< PreparedStatement > stmt );

    void beginTransaction();

    void rollbackTransaction();

    void commitTransaction();

    bool ping();

    uint32_t getLastError();

    bool lockIfReady();

    void unlock();

    std::shared_ptr< Mysql::Connection > getConnection()
    {
      return m_pConnection;
    }

    std::shared_ptr< Mysql::PreparedStatement > getPreparedStatement( uint32_t index );

    void prepareStatement( uint32_t index, const std::string& sql, ConnectionFlags flags );

    virtual void doPrepareStatements() = 0;

  protected:
    std::vector< std::shared_ptr< Mysql::PreparedStatement > > m_stmts;
    PreparedStatementMap m_queries;
    bool m_reconnecting;
    bool m_prepareError;

  private:
    Common::Util::LockedWaitQueue< std::shared_ptr< Operation > >* m_queue;
    std::shared_ptr< DbWorker > m_worker;
    std::shared_ptr< Mysql::Connection > m_pConnection;
    ConnectionInfo& m_connectionInfo;
    ConnectionFlags m_connectionFlags;
    std::mutex m_mutex;

    DbConnection( DbConnection const& right ) = delete;

    DbConnection& operator=( DbConnection const& right ) = delete;
  };

}

#endif
