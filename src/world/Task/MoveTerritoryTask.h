#pragma once

#include <cstdint>
#include <string>
#include <ForwardsZone.h>
#include "Task.h"
#include "Manager/WarpMgr.h"

namespace Sapphire::World
{

class MoveTerritoryTask : public Task
{
public:
  MoveTerritoryTask( Entity::Player& player, Common::WarpType warpType,
                     uint32_t targetTerritoryId, Common::FFXIVARR_POSITION3 targetPos, float targetRot, uint64_t delayTime );

  void onQueue() override;
  void execute() override;
  std::string toString() override;

private:
  Manager::WarpInfo m_warpInfo;
  uint32_t m_playerId;

};

template< typename... Args >
std::shared_ptr< MoveTerritoryTask > makeMoveTerritoryTask( Args... args )
{
  return std::make_shared< MoveTerritoryTask >( args... );
}

}
