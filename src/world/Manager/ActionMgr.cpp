#include "ActionMgr.h"

#include "Action/Action.h"
#include "Script/ScriptMgr.h"

#include "Actor/Player.h"

#include <Exd/ExdDataGenerated.h>
#include "Framework.h"

using namespace Sapphire;

World::Manager::ActionMgr::ActionMgr( Sapphire::FrameworkPtr pFw ) :
  BaseManager( pFw )
{

}

void World::Manager::ActionMgr::handleAoEPlayerAction( Entity::Player& player, uint8_t type,
                                                       uint32_t actionId, Data::ActionPtr actionData,
                                                       Common::FFXIVARR_POSITION3 pos )
{
  player.sendDebug( "got aoe act: {0}", actionData->name );

  auto action = Action::make_Action( player.getAsPlayer(), actionId, actionData, framework() );
  action->setType( static_cast< Common::HandleActionType >( type ) );
}

void World::Manager::ActionMgr::handleTargetedPlayerAction( Entity::Player& player, uint8_t type,
                                                            uint32_t actionId, Data::ActionPtr actionData, uint64_t targetId )
{
  player.sendDebug( "got act: {0}", actionData->name );

  auto action = Action::make_Action( player.getAsPlayer(), actionId, actionData, framework() );
  action->setType( static_cast< Common::HandleActionType >( type ) );

  bootstrapAction( player, action, *actionData );
}

void World::Manager::ActionMgr::bootstrapAction( Entity::Player& player,
                                                 Action::ActionPtr currentAction,
                                                 Data::Action& actionData )
{
  if( !canPlayerUseAction( player, *currentAction, actionData ) )
    return;

  // instantly cast and finish actions that have no cast time
  // not worth adding it to the player
  // todo: what do in cases of swiftcast/etc? script callback?
  if( !currentAction->isCastedAction() )
  {
    currentAction->start();
    currentAction->onFinish();

    return;
  }

  // otherwise, set the action on the player and start it
  player.setCurrentAction( currentAction );
  currentAction->start();
}

bool World::Manager::ActionMgr::canPlayerUseAction( Entity::Player& player,
                                                    Action::Action& currentAction,
                                                    Data::Action& actionData )
{
  // lol
  if( !player.isAlive() )
    return false;

  // npc actions/non player actions
  if( actionData.classJob == -1 )
    return false;

  if( player.getLevel() < actionData.classJobLevel )
    return false;

  if( player.getClass() != static_cast< Common::ClassJob >( actionData.classJob ) )
  {
    // check if not a base class action
    auto exdData = framework()->get< Data::ExdDataGenerated >();
    assert( exdData );

    auto classJob = exdData->get< Data::ClassJob >( static_cast< uint8_t >( player.getClass() ) );
    if( !classJob )
      return false;

    if( classJob->classJobParent != actionData.classJob )
      return false;
  }

  // todo: min tp
  // todo: min mp

  // todo: script callback for action conditionals?

  return true;
}