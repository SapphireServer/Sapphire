#include "ActionMgr.h"

#include "Action/Action.h"
#include "Script/ScriptMgr.h"
#include "Actor/Player.h"

#include <Exd/ExdDataGenerated.h>
#include "Framework.h"

#include <Network/PacketWrappers/EffectPacket.h>

using namespace Sapphire;

World::Manager::ActionMgr::ActionMgr( Sapphire::FrameworkPtr pFw ) :
  BaseManager( pFw )
{

}

void World::Manager::ActionMgr::handleAoEPlayerAction( Entity::Player& player, uint32_t actionId,
                                                       Data::ActionPtr actionData, Common::FFXIVARR_POSITION3 pos )
{
  player.sendDebug( "got aoe act: {0}", actionData->name );


  auto action = Action::make_Action( player.getAsPlayer(), actionId, actionData, framework() );

  if( !action->init() )
    return;

  if( !actionData->targetArea )
  {
    // not an action that has an aoe, cancel it
    action->interrupt();
    return;
  }

  action->setPos( pos );

  bootstrapAction( player, action, *actionData );
}

void World::Manager::ActionMgr::handleTargetedPlayerAction( Entity::Player& player, uint32_t actionId,
                                                            Data::ActionPtr actionData, uint64_t targetId )
{
  auto action = Action::make_Action( player.getAsPlayer(), actionId, actionData, framework() );

  if( !action->init() )
    return;

  // cancel any aoe actions casted with this packet
  if( actionData->targetArea )
  {
    action->interrupt();
    return;
  }

  action->setTargetId( targetId );

  bootstrapAction( player, action, *actionData );
}

void World::Manager::ActionMgr::handleItemAction( Sapphire::Entity::Player& player, uint32_t itemId,
                                                  Data::ItemActionPtr itemActionData,
                                                  uint16_t itemSourceSlot, uint16_t itemSourceContainer )
{
  player.sendDebug( "got item act: {0}, slot: {1}, container: {2}", itemId, itemSourceSlot, itemSourceContainer );

  // todo: check we have item & remove item from inventory

  switch( itemActionData->type )
  {
    default:
    {
      player.sendDebug( "ItemAction type {0} not supported.", itemActionData->type );
      break;
    }

    case Common::ItemActionType::ItemActionVFX:
    case Common::ItemActionType::ItemActionVFX2:
    {
      handleItemActionVFX( player, itemId, itemActionData->data[ 0 ] );

      break;
    }
  }
}

void World::Manager::ActionMgr::bootstrapAction( Entity::Player& player,
                                                 Action::ActionPtr currentAction,
                                                 Data::Action& actionData )
{
  if( !currentAction->precheck() )
  {
    // forcefully interrupt the action and reset the cooldown
    currentAction->interrupt();
    return;
  }

  // if we have a cast time we want to associate the action with the player so update is called
  if( currentAction->hasCastTime() )
  {
    player.setCurrentAction( currentAction );
  }

  // todo: what do in cases of swiftcast/etc? script callback?
  currentAction->start();
}

void World::Manager::ActionMgr::handleItemActionVFX( Sapphire::Entity::Player& player, uint32_t itemId, uint16_t vfxId )
{
  Common::EffectEntry effect{};
  effect.effectType = Common::ActionEffectType::VFX;
  effect.value = vfxId;

  auto effectPacket = std::make_shared< Network::Packets::Server::EffectPacket >( player.getId(), player.getId(), itemId );
  effectPacket->setTargetActor( player.getId() );
  effectPacket->setAnimationId( Common::ItemActionType::ItemActionVFX );
  effectPacket->setDisplayType( Common::ActionEffectDisplayType::ShowItemName );
  effectPacket->addEffect( effect );

  player.sendToInRangeSet( effectPacket, true );
}