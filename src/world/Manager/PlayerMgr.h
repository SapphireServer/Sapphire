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

    void onUnlockAchievement( Sapphire::Entity::Player& player, uint32_t achievementId );

    void onRestingTick( Sapphire::Entity::Player& player );

    void sendItemLevel( Sapphire::Entity::Player& player );

    void onLevelUp( Sapphire::Entity::Player& player );

    void onSetLevelForClass( Sapphire::Entity::Player& player, Common::ClassJob classJob );

    void onGainExp( Sapphire::Entity::Player& player, uint32_t exp );

    void onUnlockOrchestrion( Sapphire::Entity::Player& player, uint8_t songId, uint32_t itemId );

    void onCompanionUpdate( Entity::Player& player, uint8_t companionId );

    void onMountUpdate( Sapphire::Entity::Player& player, uint32_t mountId );

    void onMobKill( Sapphire::Entity::Player& player, Sapphire::Entity::BNpc& bnpc );

    void onHateListChanged( Sapphire::Entity::Player& player );

    void sendLoginMessage( Sapphire::Entity::Player& player );

    void onLogin( Sapphire::Entity::Player& player );
    void onLogout( Sapphire::Entity::Player& player );
    void onDeath( Sapphire::Entity::Player& player );
    void onMoveZone( Sapphire::Entity::Player& player );

    void onUpdate( Sapphire::Entity::Player& player, uint64_t tickCount );

    void onConditionChanged( Sapphire::Entity::Player& player, bool updateInRange );
    void onAchievementListChanged( Sapphire::Entity::Player& player );
    void onAchievementProgressChanged( Sapphire::Entity::Player& player, uint32_t achievementId );
    void onGearChanged( Sapphire::Entity::Player& player );

    void setCondition( Sapphire::Entity::Player& player, Common::PlayerCondition flag );
    void removeCondition( Sapphire::Entity::Player& player, Common::PlayerCondition flag );

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

  private:
    std::map< uint32_t, Entity::PlayerPtr > m_playerMapById;
    std::map< uint64_t, Entity::PlayerPtr > m_playerMapByCharacterId;
    std::map< std::string, Entity::PlayerPtr > m_playerMapByName;
  };


}
