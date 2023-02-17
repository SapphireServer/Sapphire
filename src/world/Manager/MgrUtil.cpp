#include "ForwardsZone.h"
#include <Service.h>
#include "WorldServer.h"
#include "MgrUtil.h"
#include "PlayerMgr.h"

using namespace Sapphire;
using namespace Sapphire::World::Manager;

World::Manager::PlayerMgr& Sapphire::World::Manager::playerMgr()
{
  return Common::Service< World::Manager::PlayerMgr >::ref();
}

World::WorldServer& Sapphire::World::Manager::server()
{
  return Common::Service< World::WorldServer >::ref();
}
