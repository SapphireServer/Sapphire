#pragma once

#include <Common.h>

#include <mutex>
#include <map>
#include <set>
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
    void removeSession( const Entity::Player& player );

    World::SessionPtr getSession( uint32_t id );
    World::SessionPtr getSession( uint64_t characterId );

    size_t getSessionCount() const;

    uint16_t getWorldId() const;
    void setWorldId( uint16_t worldId );

    void mainLoop();

    bool isRunning() const;

    void printBanner() const;

    bool loadSettings( int32_t argc, char* argv[] );

    void queueForPlayer( uint64_t characterId, Sapphire::Network::Packets::FFXIVPacketBasePtr pPacket );
    void queueChatForPlayer( uint64_t characterId, Sapphire::Network::Packets::FFXIVPacketBasePtr pPacket );
    void queueForPlayers( const std::set< uint64_t >& characterIds, Sapphire::Network::Packets::FFXIVPacketBasePtr pPacket );
    void queueForPlayer( uint64_t characterId, std::vector< Sapphire::Network::Packets::FFXIVPacketBasePtr > packets );
    void queueForPlayers(  const std::set< uint64_t >& characterIds, std::vector< Sapphire::Network::Packets::FFXIVPacketBasePtr > packets );

    void queueForLinkshell( uint64_t lsId, Sapphire::Network::Packets::FFXIVPacketBasePtr pPacket, std::set< uint64_t > exceptionCharIdList = {} );
    void queueForFreeCompany( uint64_t fcId, Sapphire::Network::Packets::FFXIVPacketBasePtr pPacket, std::set< uint64_t > exceptionCharIdList = {} );

    Sapphire::Common::Config::WorldConfig& getConfig();

  private:
    uint16_t m_port;
    std::string m_ip;
    int64_t m_lastDBPingTime;
    uint64_t m_lastServerTick{ 0 };
    bool m_bRunning;
    uint16_t m_worldId;

    std::string m_configName;
    std::mutex m_sessionMutex;

    Sapphire::Common::Config::WorldConfig m_config;

    std::map< uint32_t, SessionPtr > m_sessionMapById;
    std::map< uint64_t, SessionPtr > m_sessionMapByCharacterId;

  public:
    void updateSessions( uint32_t currTime );

    void DbKeepAlive( uint32_t currTime );
  };

}
