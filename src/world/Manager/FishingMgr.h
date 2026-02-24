#pragma once

#include <cstdint>
#include <unordered_map>

#include <ForwardsZone.h>
#include "Event/EventHandler.h"

namespace Sapphire::World::Manager
{
  class FishingMgr
  {
  public:
    static constexpr uint32_t PrototypeEventId = 0x00150001;
    static constexpr uint16_t SceneStart = 1;
    static constexpr uint16_t SceneRest = 2;
    static constexpr uint16_t SceneQuit = 3;
    static constexpr uint16_t ScenePoleReady = 4;
    static constexpr uint32_t SceneFlags = 0x00040001;
    static constexpr uint8_t EventStartFlags = 0;
    static constexpr uint32_t EventStartArg = 0;

    enum class SessionState : uint8_t
    {
      None,
      Active,
      Quitting
    };

    void startFishing( Entity::Player& player );
    void quitFishing( Entity::Player& player );
    void onFishingActionRequest( Entity::Player& player, uint32_t actionId, uint16_t requestId, uint64_t targetId );
    void onStartActionResultEvent( Entity::Player& player, uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3 );

    bool isFishing( uint64_t characterId ) const;

  private:
    struct Session
    {
      SessionState state{ SessionState::None };
      uint64_t startedAtMs{};
    };

    void onStartSceneReturn( Entity::Player& player, const Event::SceneResult& result );
    void onRestSceneReturn( Entity::Player& player, const Event::SceneResult& result );
    void onPoleReadySceneReturn( Entity::Player& player, const Event::SceneResult& result );
    void onQuitSceneReturn( Entity::Player& player, const Event::SceneResult& result );

    void cleanupSession( Entity::Player& player, bool setIdle );

    std::unordered_map< uint64_t, Session > m_sessions;
  };
}
