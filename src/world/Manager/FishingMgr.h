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
    static constexpr uint32_t SceneFlags = 0x00040001;
    static constexpr uint8_t EventStartFlags = 0;
    static constexpr uint32_t EventStartArg = 0;

    enum class FishingState : uint32_t
    {
      None = 0,
      CastingOut = 1,
      PullingPoleIn = 2,
      Quitting = 3,
      PoleReady = 4,
      Bite = 5,
      Hooking = 6,
      ReleasingCatch = 7,
      ConfirmingCollectable = 8,
      AmbitiousLure = 9,
      ModestLure = 10,
      LineInWater = 12,
    };

    void startFishing( Entity::Player& player );
    void quitFishing( Entity::Player& player );
    void onFishingActionRequest( Entity::Player& player, uint32_t actionId, uint16_t requestId, uint64_t targetId );
    void onStartActionResultEvent( Entity::Player& player, uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3 );

    bool isFishing( uint64_t characterId ) const;

  private:
    struct Session
    {
      FishingState state{ FishingState::None };
      uint64_t startedAtMs{};
      uint64_t stateChangedAtMs{};
    };

    void onCastSceneReturn( Entity::Player& player, const Event::SceneResult& result );
    void onRestSceneReturn( Entity::Player& player, const Event::SceneResult& result );
    void onPoleReadySceneReturn( Entity::Player& player, const Event::SceneResult& result );
    void onQuitSceneReturn( Entity::Player& player, const Event::SceneResult& result );

    void cleanupSession( Entity::Player& player, bool setIdle );

    std::unordered_map< uint64_t, Session > m_sessions;
  };
}
