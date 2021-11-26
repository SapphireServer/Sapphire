#include "ActionMgr.h"
#include "PlayerMgr.h"

#include "Action/Action.h"
#include "Action/ItemAction.h"
#include "Action/MountAction.h"
#include "Script/ScriptMgr.h"
#include "Actor/Player.h"

#include <Service.h>
#include <Exd/ExdData.h>

#include <Network/PacketWrappers/EffectPacket.h>

using namespace Sapphire;

void World::Manager::ActionMgr::handlePlacedPlayerAction( Entity::Player& player, uint32_t actionId,
                                                          std::shared_ptr< Component::Excel::ExcelStruct< Component::Excel::Action > > actionData, Common::FFXIVARR_POSITION3 pos,
                                                          uint16_t sequence )
{
  PlayerMgr::sendDebug( player, "got aoe act: {0}", actionData->getString( actionData->data().Text.Name ) );

  auto action = Action::make_Action( player.getAsPlayer(), actionId, sequence, actionData );

  action->setPos( pos );

  if( !action->init() )
    return;

  if( !actionData->data().EffectRange )
  {
    // not an action that has an aoe, cancel it
    action->interrupt();
    return;
  }

  bootstrapAction( player, action, actionData );
}

void World::Manager::ActionMgr::handleTargetedPlayerAction( Entity::Player& player, uint32_t actionId,
                                                            std::shared_ptr< Component::Excel::ExcelStruct< Component::Excel::Action > > actionData, uint64_t targetId,
                                                            uint16_t sequence )
{
  auto action = Action::make_Action( player.getAsPlayer(), actionId, sequence, actionData );

  action->setTargetId( targetId );

  action->setPos( player.getPos() );

  if( !action->init() )
    return;

  // cancel any aoe actions casted with this packet
  if( actionData->data().EffectRange )
  {
    action->interrupt();
    return;
  }

  bootstrapAction( player, action, actionData );
}

void World::Manager::ActionMgr::handleItemAction( Sapphire::Entity::Player& player, uint32_t itemId,
                                                  std::shared_ptr< Component::Excel::ExcelStruct< Component::Excel::ItemAction > > itemActionData,
                                                  uint16_t itemSourceSlot, uint16_t itemSourceContainer )
{
  PlayerMgr::sendDebug( player, "got item act: {0}, slot: {1}, container: {2}", itemId, itemSourceSlot, itemSourceContainer );

  auto action = Action::make_ItemAction( player.getAsChara(), itemId, itemActionData,
                                         itemSourceSlot, itemSourceContainer );

  // todo: item actions don't have cast times? if so we can just start it and we're good
  action->start();
}

void World::Manager::ActionMgr::handleMountAction( Entity::Player& player, uint16_t mountId,
                                                   std::shared_ptr< Component::Excel::ExcelStruct< Component::Excel::Action > > actionData, uint64_t targetId,
                                                   uint16_t sequence )
{
  PlayerMgr::sendDebug( player, "setMount: {0}", mountId );

  auto action = Action::make_MountAction( player.getAsPlayer(), mountId, sequence, actionData );

  action->setTargetId( targetId );

  if( !action->init() )
    return;

  bootstrapAction( player, action, actionData );
}

void World::Manager::ActionMgr::bootstrapAction( Entity::Player& player,
                                                 Action::ActionPtr currentAction,
                                                 std::shared_ptr< Component::Excel::ExcelStruct< Component::Excel::Action > > actionData )
{
  /*
  //TODO: need to be fixed
  if( !currentAction->preCheck() )
  {
    // forcefully interrupt the action and reset the cooldown
    currentAction->interrupt();
    return;
  }
  */

  if( player.getCurrentAction() )
  {
    PlayerMgr::sendDebug( player, "Skill queued: {0}", currentAction->getId() );
    player.setQueuedAction( currentAction );
  }
  else
  {
    // if we have a cast time we want to associate the action with the player so update is called
    if( currentAction->hasCastTime() )
    {
      player.setCurrentAction( currentAction );
    }

    // todo: what do in cases of swiftcast/etc? script callback?
    currentAction->start();
  }
}

bool World::Manager::ActionMgr::actionHasCastTime( uint32_t actionId ) //TODO: Add logic for special cases
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto actionInfoPtr = exdData.getRow< Component::Excel::Action >( actionId );

  if( actionInfoPtr->data().ComboContinue )
    return false;

  return actionInfoPtr->data().CastTime != 0;
}