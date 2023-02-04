#pragma once

#include <cstdint>
#include <string>
#include <ForwardsZone.h>
#include "Task.h"
#include "Manager/WarpMgr.h"

namespace Sapphire::World
{

class WarpTask : public Task
{
public:
  WarpTask( Entity::Player& player, Common::WarpType warpType,
            Common::FFXIVARR_POSITION3 targetPos, float targetRot, uint64_t delayTime );

  void onQueue() override;
  void execute() override;
  std::string toString() override;

private:
  Manager::WarpInfo m_warpInfo;
  uint32_t m_playerId;

};

template< typename... Args >
std::shared_ptr< WarpTask > makeWarpTask( Args... args )
{
  return std::make_shared< WarpTask >( args... );
}

}
