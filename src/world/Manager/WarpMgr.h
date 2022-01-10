#pragma once

#include <cstdint>
#include <string>
#include <ForwardsZone.h>

namespace Sapphire::World::Manager
{
  struct QueuedWarp
  {
    Common::WarpType m_warpType;
    uint64_t m_characterId;
    uint16_t m_targetZoneId;
    Common::FFXIVARR_POSITION3 m_targetPosition;
    float m_targetRotation;
    uint64_t m_delayTime;

    QueuedWarp( uint64_t characterId, Common::WarpType warpType, uint16_t targetZoneId,
                const Common::FFXIVARR_POSITION3& targetPosition, float targetRotation, uint64_t delayTime ) :
      m_characterId( characterId ),
      m_warpType( warpType ),
      m_targetZoneId( targetZoneId ),
      m_targetPosition( targetPosition ),
      m_targetRotation( targetRotation ),
      m_delayTime( delayTime ),
    {
    }
  };

  class WarpMgr
  {
  public:
    WarpMgr() = default;

    // queue a new warp process to be executed when the delaytime (ms) expired
    void queueWarp( uint64_t characterId, Common::WarpType warpType, uint16_t targetZoneId,
                    const Common::FFXIVARR_POSITION3& targetPosition, float targetRotation, uint64_t delayTime );

    void update( uint64_t tickCount );

  private:
    uint64_t m_lastTick;
    std::vector< std::shared_ptr< QueuedWarp > > m_warpQueue;

  };

}
