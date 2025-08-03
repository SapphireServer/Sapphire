#include "ActionMgr.h"
#include "PlayerMgr.h"

#include "Action/ActionLutData.h"
#include "Action/Action.h"
#include "Action/ItemAction.h"
#include "Action/EventItemAction.h"
#include "Action/MountAction.h"
#include "Action/ItemManipulationAction.h"
#include "Script/ScriptMgr.h"
#include "Actor/Player.h"

#include <Service.h>
#include <Exd/ExdData.h>

#include <Network/PacketWrappers/EffectPacket.h>

using namespace Sapphire;
using namespace Sapphire::World::Manager;

bool ActionMgr::cacheActionLut()
{
  return Action::ActionLutData::cacheActions();
}

void ActionMgr::handlePlacedAction( Entity::Chara& chara, uint32_t actionId, Common::FFXIVARR_POSITION3 pos, uint16_t requestId )
{
  auto action = Action::make_Action( chara.getAsChara(), actionId, requestId );

  action->setPos( pos );

  if( !action->init() )
    return;

  auto actionData = action->getActionData();

  if( chara.isPlayer() )
    PlayerMgr::sendDebug( *chara.getAsPlayer(), "got aoe act: {0}", actionData->getString( actionData->data().Text.Name ) );

  if( !actionData->data().EffectRange )
  {
    // not an action that has an aoe, cancel it
    action->interrupt();
    return;
  }

  bootstrapAction( chara, action, actionData );
}

void ActionMgr::handleItemManipulationAction( Entity::Player& player, uint32_t actionId,  uint16_t sequence )
{
  auto action = Action::make_ItemManipulationAction( player.getAsPlayer(), actionId, sequence, nullptr, 2500 ); // todo: maybe the delay can be retrieved from data

  player.setCurrentAction( action );

  if( !action->init() )
    return;

  action->start();
}

void ActionMgr::handleTargetedAction( Entity::Chara& src, uint32_t actionId, uint64_t targetId, uint16_t requestId )
{
  auto action = Action::make_Action( src.getAsChara(), actionId, requestId );

  action->setTargetId( targetId );
  action->setPos( src.getPos() );

  if( !action->init() )
    return;

  auto actionData = action->getActionData();

  bootstrapAction( src, action, actionData );
}

void ActionMgr::handleItemAction( Sapphire::Entity::Player& player, uint32_t itemId,
                                  Excel::ExcelStructPtr< Excel::ItemAction > itemActionData,
                                  uint16_t itemSourceSlot, uint16_t itemSourceContainer )
{
  PlayerMgr::sendDebug( player, "got item act: {0}, slot: {1}, container: {2}", itemId, itemSourceSlot, itemSourceContainer );

  auto action = Action::make_ItemAction( player.getAsChara(), itemId, itemActionData,
                                         itemSourceSlot, itemSourceContainer );

  // todo: item actions don't have cast times? if so we can just start it and we're good
  action->start();
}

void ActionMgr::handleEventItemAction( Sapphire::Entity::Player& player, uint32_t itemId,
                                       Excel::ExcelStructPtr< Excel::EventItem > itemActionData,
                                       uint32_t sequence, uint64_t targetId )
{
  auto action = Action::make_EventItemAction( player.getAsChara(), itemId, itemActionData, sequence, targetId );
  action->init();

  if( itemActionData->data().CastTime )
  {
    player.setCurrentAction( action );
  }

  action->start();
}

void ActionMgr::handlePlacedEventItemAction( Sapphire::Entity::Player& player, uint32_t itemId,
                                             Excel::ExcelStructPtr< Excel::EventItem > itemActionData,
                                             uint32_t sequence, Common::FFXIVARR_POSITION3 targetPos )
{
  auto action = Action::make_EventItemAction( player.getAsChara(), itemId, itemActionData, sequence, targetPos, Common::CastType::Circle );
  action->init();

  if( itemActionData->data().CastTime )
  {
    player.setCurrentAction( action );
  }

  action->start();
}

void ActionMgr::handleMountAction( Entity::Player& player, uint16_t mountId,
                                   Excel::ExcelStructPtr< Excel::Action > actionData, uint64_t targetId,
                                   uint16_t sequence )
{
  PlayerMgr::sendDebug( player, "setMount: {0}", mountId );

  auto action = Action::make_MountAction( player.getAsPlayer(), mountId, sequence, actionData );

  action->setTargetId( targetId );

  if( !action->init() )
    return;

  bootstrapAction( player, action, actionData );
}

void ActionMgr::bootstrapAction( Entity::Chara& src, Action::ActionPtr currentAction,
                                 Excel::ExcelStructPtr< Excel::Action > actionData )
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

  if( src.getCurrentAction() )
  {
    if( src.isPlayer() )
    {
      auto& player = *src.getAsPlayer();
      PlayerMgr::sendDebug( player, "Skill queued: {0}", currentAction->getId() );
      player.setQueuedAction( currentAction );
    }

  }
  else
  {
    // if we have a cast time we want to associate the action with the player so update is called
    if( currentAction->hasCastTime() )
      src.setCurrentAction( currentAction );

    // todo: what do in cases of swiftcast/etc? script callback?
    currentAction->start();
    src.setLastAttack( Common::Util::getTimeMs() );
  }
}

bool ActionMgr::actionHasCastTime( uint32_t actionId ) //TODO: Add logic for special cases
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto actionInfoPtr = exdData.getRow< Excel::Action >( actionId );

  if( actionInfoPtr->data().ComboContinue )
    return false;

  return actionInfoPtr->data().CastTime != 0;
}
