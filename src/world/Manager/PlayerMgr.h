#pragma once

#include "ForwardsZone.h"
#include <spdlog/fmt/fmt.h>
#include "MgrUtil.h"

namespace Sapphire::World::Manager
{
  class PlayerMgr
  {
  public:
    PlayerMgr() = default;

    std::string getPlayerNameFromDb( uint64_t characterId, bool forceDbLoad = false );
    Entity::PlayerPtr getPlayer( uint32_t entityId );
    Entity::PlayerPtr getPlayer( uint64_t characterId );
    Entity::PlayerPtr getPlayer( const std::string& playerName );
    std::vector< Entity::PlayerPtr > searchPlayersByName( const std::string& playerName );
    Entity::PlayerPtr addPlayer( uint64_t characterId );
    Entity::PlayerPtr loadPlayer( uint32_t entityId );
    Entity::PlayerPtr loadPlayer( uint64_t characterId );
    Entity::PlayerPtr loadPlayer( const std::string& playerName );
    bool loadPlayers();
    Entity::PlayerPtr syncPlayer( uint64_t characterId );

    void onMobKill( Sapphire::Entity::Player& player, Sapphire::Entity::BNpc& bnpc );

    void onSkillProc( Entity::Player& player, uint8_t index );

    void sendLoginMessage( Sapphire::Entity::Player& player );

    void onLogin( Sapphire::Entity::Player& player );
    void onLogout( Sapphire::Entity::Player& player );
    void onDeath( Sapphire::Entity::Player& player );
    void onMoveZone( Sapphire::Entity::Player& player );

    void onUpdate( Sapphire::Entity::Player& player, uint64_t tickCount );

    void onGainExp( Sapphire::Entity::Player& player, uint32_t exp );

    bool isAllAreaDiscovered( Sapphire::Entity::Player& player, int16_t mapId );

    void onDiscoverArea( Sapphire::Entity::Player& player, int16_t mapId, int16_t subId );

    void onUpdateHuntingLog( Sapphire::Entity::Player& player, uint8_t id );

    void onExitInstance( Sapphire::Entity::Player& player );

    void onClassJobChanged( Sapphire::Entity::Player& player, Common::ClassJob classJob );

    void onLevelChanged( Sapphire::Entity::Player& player, uint8_t level );

    void onSongLearned( Sapphire::Entity::Player& player, uint8_t songId, uint32_t itemId );

  //////////// Helpers

    static void sendServerNotice( Sapphire::Entity::Player& player, const std::string& message );
    template< typename... Args >
    static void sendServerNotice( Sapphire::Entity::Player& player, const std::string& message, const Args&... args )
    {
      sendServerNotice( player, fmt::format( message, args... ) );
    }

    static void sendUrgent( Sapphire::Entity::Player& player, const std::string& message );
    template< typename... Args >
    static void sendUrgent( Sapphire::Entity::Player& player, const std::string& message, const Args&... args )
    {
      sendUrgent( player, fmt::format( message, args... ) );
    }

    static void sendDebug( Sapphire::Entity::Player& player, const std::string& message );

    template< typename... Args >
    static void sendDebug( Sapphire::Entity::Player& player, const std::string& message, const Args&... args )
    {
      sendDebug( player, fmt::format( message, args... ) );
    }

    static void sendLogMessage( Sapphire::Entity::Player& player, uint32_t messageId, uint32_t param2 = 0, uint32_t param3 = 0,
                                uint32_t param4 = 0, uint32_t param5 = 0, uint32_t param6 = 0 );

    static void sendBattleTalk( Sapphire::Entity::Player& player, uint32_t battleTalkId, uint32_t handlerId, uint32_t kind,
                                uint32_t nameId, uint32_t talkerId, uint32_t time,
                                uint32_t param1 = 0, uint32_t param2 = 0, uint32_t param3 = 0, uint32_t param4 = 0,
                                uint32_t param5 = 0, uint32_t param6 = 0, uint32_t param7 = 0, uint32_t param8 = 0 );

  private:
    std::map< uint32_t, Entity::PlayerPtr > m_playerMapById;
    std::map< uint64_t, Entity::PlayerPtr > m_playerMapByCharacterId;
    std::map< std::string, Entity::PlayerPtr > m_playerMapByName;

    void checkAutoAttack( Entity::Player& player, uint64_t tickCount ) const;
  };


}
