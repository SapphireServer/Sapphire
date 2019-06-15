#ifndef SAPPHIRE_DBMANAGER
#define SAPPHIRE_DBMANAGER
#include <string>
#include <stdint.h>
#include <memory>

namespace Mysql 
{
  class Connection;
}

enum class Mode
{
  INIT,
  LIQUIDATE,
  MIGRATE,
  CHECK,
  CLEAN_CHARS,
  ADD_MIGRATION,
};

class DbManager
{
  public:
    DbManager( const std::string& host, const std::string& database, const std::string& user, const std::string& pw, uint16_t port );
    
    void setMode( Mode mode );
    Mode getMode() const;

    bool connect();
    bool selectSchema();

    bool execute( const std::string& sql );

    bool performAction();

    bool modeInit();

    bool modeLiquidate();

    bool modeCheck();

    bool modeMigrate();

    bool modeAddMigration();

    virtual ~DbManager();

    const std::string& getLastError();

    const std::string& getSchemaFile() const;
    const std::string& getInsertFile() const;
    
    void setSchemaFile( const std::string& schemaFile );
    void setInsertFile( const std::string& insertFile );

    void setForceMode( bool mode );

    void setMigratioName( const std::string& name );

  private:
    std::string m_host;
    std::string m_database;
    std::string m_user;
    std::string m_password;
    uint16_t m_port;
    std::shared_ptr< Mysql::Connection > m_pConnection;
    std::string m_lastError;
    Mode m_mode;
    std::string m_iFile;
    std::string m_sFile;
    bool m_force;

    std::string m_migrationName;
};



#endif
