#pragma once

#include "ForwardsZone.h"
#include <Service.h>
#include "WorldServer.h"

namespace Sapphire::World::Manager
{
  class PlayerMgr;

  World::Manager::PlayerMgr& playerMgr();
  World::WorldServer& server();
}