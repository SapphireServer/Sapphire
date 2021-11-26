#pragma once

#include <Common.h>

#include <mutex>
#include <map>
#include "ForwardsZone.h"
#include <Config/ConfigDef.h>

namespace Sapphire::World
{

  class WorldServer
  {
  public:
    WorldServer( const std::string& configName );

    ~WorldServer();

    using WorldConfigPtr = std::shared_ptr< Sapphire::Common::Config::WorldConfig >;

    void run( int32_t argc, char* argv[] );

    bool createSession( uint32_t sessionId );

    void removeSession( uint32_t sessionId );
    void removeSession( uint64_t characterId );
    void removeSession( const std::string& playerName );

    World::SessionPtr getSession( uint32_t id );
    World::SessionPtr getSession( uint64_t characterId );
    World::SessionPtr getSession( const std::string& playerName );
    std::vector< World::SessionPtr > searchSessionByName( const std::string& playerName );

    Entity::PlayerPtr getPlayer( uint32_t entityId );
    Entity::PlayerPtr getPlayer( uint64_t characterId );
    Entity::PlayerPtr getPlayer( const std::string& playerName );

    size_t getSessionCount() const;

    uint16_t getWorldId() const;
    void setWorldId( uint16_t worldId );

    void mainLoop();

    bool isRunning() const;

    void printBanner() const;

    bool loadSettings( int32_t argc, char* argv[] );

    std::string getPlayerNameFromDb( uint64_t characterId, bool forceDbLoad = false );

    void queueForPlayer( uint64_t characterId, Sapphire::Network::Packets::FFXIVPacketBasePtr pPacket );
    void queueForPlayer( uint64_t characterId, std::vector< Sapphire::Network::Packets::FFXIVPacketBasePtr > packets );

    Entity::PlayerPtr addPlayer( uint64_t characterId );

    Entity::PlayerPtr loadPlayer( uint32_t entityId );
    Entity::PlayerPtr loadPlayer( uint64_t characterId );
    Entity::PlayerPtr loadPlayer( const std::string& playerName );
    bool loadPlayers();

    Entity::PlayerPtr syncPlayer( uint64_t characterId );

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
    std::map< uint64_t, SessionPtr > m_sessionMapByCharacterId;
    std::map< std::string, SessionPtr > m_sessionMapByName;

    std::map< uint32_t, Entity::PlayerPtr > m_playerMapById;
    std::map< uint64_t, Entity::PlayerPtr > m_playerMapByCharacterId;
    std::map< std::string, Entity::PlayerPtr > m_playerMapByName;

    std::map< uint32_t, uint32_t > m_zones;

    using BNPCMap = std::map< uint32_t, std::shared_ptr< Common::BNPCInstanceObject > >;
    std::map< int32_t, BNPCMap > m_bNpcTerritoryMap;

  public:
    std::map< int32_t, BNPCMap >& getBNpcTeriMap();

  };

}
