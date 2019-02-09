#include "ActionMgr.h"

#include "Action/Action.h"
#include "Script/ScriptMgr.h"

#include "Actor/Player.h"

#include <Exd/ExdDataGenerated.h>

using namespace Sapphire;

World::Manager::ActionMgr::ActionMgr( Sapphire::FrameworkPtr pFw ) :
  BaseManager( pFw )
{

}

void World::Manager::ActionMgr::handleAoEPlayerAction( Entity::Player& player, uint8_t type,
                                                       Data::ActionPtr action, Common::FFXIVARR_POSITION3 pos )
{
  player.sendDebug( "got aoe act: {0}", action->name );
}

void World::Manager::ActionMgr::handleTargetedPlayerAction( Entity::Player& player, uint8_t type,
                                                            Data::ActionPtr action, uint64_t targetId )
{
  player.sendDebug( "got act: {0}", action->name );
}