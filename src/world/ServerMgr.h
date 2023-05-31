#ifndef __GAMESERVER_H
#define __GAMESERVER_H

#include <Common.h>

#include <mutex>
#include <map>
#include "ForwardsZone.h"
#include <Config/ConfigDef.h>

namespace Sapphire::World
{

  class ServerMgr
  {
  public:
    ServerMgr( const std::string& configName );

    ~ServerMgr();

    using WorldConfigPtr = std::shared_ptr< Sapphire::Common::Config::WorldConfig >;

    void run( int32_t argc, char* argv[] );

    bool createSession( uint32_t sessionId );

    World::SessionPtr getSession( uint32_t id );
    World::SessionPtr getSession( uint64_t contentId );
    World::SessionPtr getSession( const std::string& playerName );

    size_t getSessionCount() const;

    uint16_t getWorldId() const;
    void setWorldId( uint16_t worldId );

    void mainLoop();

    bool isRunning() const;

    void printBanner() const;

    bool loadSettings( int32_t argc, char* argv[] );
    void loadBNpcTemplates();

    Entity::BNpcTemplatePtr getBNpcTemplate( const std::string& key );
    Entity::BNpcTemplatePtr getBNpcTemplate( uint32_t id );

    std::string getPlayerNameFromDb( uint32_t playerId, bool forceDbLoad = false );
    void updatePlayerName( uint32_t playerId, const std::string& playerNewName );

    Sapphire::Common::Config::WorldConfig& getConfig();

  private:
    uint16_t m_port;
    std::string m_ip;
    int64_t m_lastDBPingTime;
    bool m_bRunning;
    uint16_t m_worldId;

    std::string m_configName;

    std::mutex m_sessionMutex;

    Sapphire::Common::Config::WorldConfig m_config;

    std::map< uint32_t, SessionPtr > m_sessionMapById;
    std::map< uint64_t, SessionPtr > m_sessionMapByContentId;
    std::map< std::string, SessionPtr > m_sessionMapByName;
    std::map< uint32_t, std::string > m_playerNameMapById;
    std::map< uint32_t, uint32_t > m_zones;
    std::map< std::string, Entity::BNpcTemplatePtr > m_bNpcTemplateMap;

    void removeSession( uint32_t sessionId );
    void removeSession( uint64_t contentId );
    void removeSession( const std::string& playerName );
  };

}

#endif

