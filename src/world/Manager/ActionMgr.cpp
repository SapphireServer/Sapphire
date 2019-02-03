#include "ActionMgr.h"

using namespace Sapphire;

World::Manager::ActionMgr::ActionMgr( Sapphire::FrameworkPtr pFw ) :
  BaseManager( pFw )
{

}

void World::Manager::ActionMgr::handleAoEPlayerAction( Entity::Player& player, uint8_t type,
                                                       uint32_t actionId, Common::FFXIVARR_POSITION3 pos )
{

}

void World::Manager::ActionMgr::handleTargetedPlayerAction( Entity::Player& player, uint8_t type,
                                                            uint32_t actionId, uint64_t targetId )
{

}