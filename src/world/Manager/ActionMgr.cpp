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
  action->setPos( pos );

  bootstrapAction( player, action, *actionData );
}

void World::Manager::ActionMgr::handleTargetedPlayerAction( Entity::Player& player, uint32_t actionId,
                                                            Data::ActionPtr actionData, uint64_t targetId )
{
  player.sendDebug( "got act: {0}", actionData->name );

  auto action = Action::make_Action( player.getAsPlayer(), actionId, actionData, framework() );

  if( targetId != player.getId() )
  {
    auto target = player.lookupTargetById( targetId );
    if( auto chara = target->getAsChara() )
      action->setTargetChara( chara );
  }
  else
  {
    // maybe an eobj? wat do?
  }

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

  auto& actionCost = currentAction.getCostArray();
  for( uint8_t i = 0; i < actionCost.size(); ++i )
  {
    // todo: validate costs/conditionals here
  }

  return true;
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