#include "ActionMgr.h"

#include "Action/Action.h"
#include "Action/ItemAction.h"
#include "Action/EventItemAction.h"
#include "Action/MountAction.h"
#include "Script/ScriptMgr.h"
#include "Actor/Player.h"
#include "Service.h"
#include "StatusEffect/StatusEffect.h"

#include <Exd/ExdDataGenerated.h>

#include <Network/PacketWrappers/EffectPacket.h>

using namespace Sapphire;

void World::Manager::ActionMgr::handlePlacedAction( Entity::Chara& chara, uint32_t actionId,
                                                          Data::ActionPtr actionData, Common::FFXIVARR_POSITION3 pos,
                                                          uint16_t sequence )
{
  if( auto player = chara.getAsPlayer() )
    player->sendDebug( "got aoe act: {0}", actionData->name );

  if( !actionData )
  {
    actionData = Common::Service< Data::ExdDataGenerated >::ref().get< Data::Action >( actionId );
  }

  auto action = Action::make_Action( chara.getAsChara(), actionId, sequence, actionData );

  action->setPos( pos );

  if( !action->init() )
    return;

  if( !actionData->targetArea )
  {
    // not an action that has an aoe, cancel it
    action->interrupt();
    return;
  }

  bootstrapAction( chara, action, *actionData );
}

void World::Manager::ActionMgr::handleTargetedAction( Entity::Chara& chara, uint32_t actionId,
                                                            Data::ActionPtr actionData, uint64_t targetId,
                                                            uint16_t sequence )
{
  if( !actionData )
  {
    actionData = Common::Service< Data::ExdDataGenerated >::ref().get< Data::Action >( actionId );
  }

  if( !actionData )
  {
    if( auto player = chara.getAsPlayer() )
      player->sendUrgent( "Cannot find action {}.", actionId );
    return;
  }

  auto action = Action::make_Action( chara.getAsChara(), actionId, sequence, actionData );

  action->setTargetId( targetId );

  action->setPos( chara.getPos() );

  if( !action->init() )
    return;

  // cancel any aoe actions casted with this packet
  if( actionData->targetArea )
  {
    action->interrupt();
    return;
  }

  bootstrapAction( chara, action, *actionData );
}

void World::Manager::ActionMgr::handleItemAction( Sapphire::Entity::Player& player, uint32_t itemId,
                                                  Data::ItemActionPtr itemActionData,
                                                  uint16_t itemSourceSlot, uint16_t itemSourceContainer )
{
  player.sendDebug( "got item act: {0}, slot: {1}, container: {2}", itemId, itemSourceSlot, itemSourceContainer );

  auto action = Action::make_ItemAction( player.getAsChara(), itemId, itemActionData,
                                         itemSourceSlot, itemSourceContainer );

  // todo: item actions don't have cast times? if so we can just start it and we're good
  action->start();
}

void World::Manager::ActionMgr::handleEventItemAction( Sapphire::Entity::Player& player, uint32_t itemId, Data::EventItemPtr itemActionData, uint32_t sequence, uint64_t targetId )
{
  auto action = Action::make_EventItemAction( player.getAsChara(), itemId, itemActionData, sequence, targetId );
  if( !action->init() )
    return;
  if( itemActionData->castTime )
  {
    player.setCurrentAction( action );
  }

  action->start();
}


void World::Manager::ActionMgr::handleMountAction( Entity::Player& player, uint16_t mountId,
                                                   Data::ActionPtr actionData, uint64_t targetId,
                                                   uint16_t sequence )
{
  player.sendDebug( "mount: {0}", mountId );

  auto action = Action::make_MountAction( player.getAsPlayer(), mountId, sequence, actionData );

  action->setTargetId( targetId );

  if( !action->init() )
    return;

  bootstrapAction( player, action, *actionData );
}

void World::Manager::ActionMgr::bootstrapAction( Entity::Chara& chara,
                                                 Action::ActionPtr currentAction,
                                                 Data::Action& actionData )
{
  for( const auto& statusIt : chara.getStatusEffectMap() )
  {
    statusIt.second->onBeforeActionStart( currentAction.get() );
  }

  if( currentAction->isInterrupted() )
    return;
  
  if( !currentAction->preCheck() )
  {
    // forcefully interrupt the action and reset the cooldown
    currentAction->interrupt();
    return;
  }

  if( chara.getCurrentAction() )
  {
    if( auto player = chara.getAsPlayer() )
    {
      player->sendDebug( "Skill queued: {0}", currentAction->getId() );
      player->setQueuedAction( currentAction );
    }
  }
  else
  {
    // if we have a cast time we want to associate the action with the player so update is called
    if( currentAction->hasCastTime() )
    {
      chara.setCurrentAction( currentAction );
    }

    // todo: what do in cases of swiftcast/etc? script callback?
    currentAction->start();
  }
}