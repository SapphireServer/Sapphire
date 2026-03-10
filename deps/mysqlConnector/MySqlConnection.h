#pragma once

#include <string>
#include <memory>
#include <cstdint>

#include "MySqlBase.h"

namespace Mysql
{
  class Statement;
  class PreparedStatement;

  class Connection : public std::enable_shared_from_this< Connection >
  {
  public:
    Connection( std::shared_ptr< MySqlBase > pBase, const std::string& hostName, const std::string& userName,
                const std::string& password, uint16_t port = 3306 );

    Connection( std::shared_ptr< MySqlBase > pBase, const std::string& hostName, const std::string& userName,
                const std::string& password, const OptionMap& options, uint16_t port = 3306 );

    virtual ~Connection();

    void close();
    bool isClosed() const;

    bool ping();

    void setOption( Option option, const void* arg );
    void setOption( Option option, bool arg );
    void setOption( Option option, uint32_t arg );
    void setOption( Option option, const std::string& arg );

    std::shared_ptr< MySqlBase > getMySqlBase() const;

    void setAutoCommit( bool autoCommit );
    bool getAutoCommit();

    [[nodiscard]] std::string escapeString( std::string_view inData );

    void setSchema( const std::string& catalog );

    std::shared_ptr< Statement > createStatement();

    void beginTransaction();
    void commitTransaction();
    void rollbackTransaction();

    std::string getSchema();

    std::string getError();
    uint32_t getErrorNo();

    bool isReadOnly();
    void setReadOnly( bool readOnly );

    bool isValid();

    bool reconnect();

    std::shared_ptr< Mysql::PreparedStatement > prepareStatement( const std::string& sql );

    std::string getLastStatementInfo();

  private:
    friend class Statement;
    friend class PreparedStatement;

    std::shared_ptr< MySqlBase > m_pBase;
    NativeConnectionHandle m_pRawCon{};
    bool m_bConnected{};

    Connection( const Connection& );
    void operator=( Connection& );
  };
}// namespace Mysql

#include "MySqlPreparedStatement.h"
