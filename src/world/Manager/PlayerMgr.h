#pragma once

#include "ForwardsZone.h"
#include <spdlog/fmt/fmt.h>

namespace Sapphire::World::Manager
{
class PlayerMgr
  {
  public:
    PlayerMgr() = default;

    void movePlayerToLandDestination( Sapphire::Entity::Player& player, uint32_t landId, uint16_t param = 0 );

    void onOnlineStatusChanged( Sapphire::Entity::Player& player, bool updateProfile = true );

    void onEquipDisplayFlagsChanged( Sapphire::Entity::Player& player );

    void onSendStateFlags( Sapphire::Entity::Player& player, bool updateInRange );

    void onSendStats( Sapphire::Entity::Player& player );

    void onPlayerStatusUpdate( Sapphire::Entity::Player& player );

    void onChangeClass( Sapphire::Entity::Player& player );

    void onPlayerHpMpTpChanged( Sapphire::Entity::Player& player );

    void onPlayerItemLevelUpdate( Sapphire::Entity::Player& player );

    void onLevelUp( Sapphire::Entity::Player& player );

    void onGainExp( Sapphire::Entity::Player& player, uint32_t exp );

    void onUnlockOrchestrion( Sapphire::Entity::Player& player, uint8_t songId, uint32_t itemId );

    void onChangeGear( Sapphire::Entity::Player& player );

    void onGcUpdate( Sapphire::Entity::Player& player );

    void onMountUpdate( Sapphire::Entity::Player& player, uint32_t mountId );

    void onMobKill( Sapphire::Entity::Player& player, uint16_t nameId );

    void onHateListChanged( Sapphire::Entity::Player& player );

    void onLogin( Sapphire::Entity::Player& player );

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

  };
}
