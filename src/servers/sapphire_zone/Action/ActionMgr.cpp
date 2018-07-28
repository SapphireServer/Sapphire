#include <Actor/Player.h>
#include <Exd/ExdDataGenerated.h>
#include <Script/ScriptMgr.h>
#include <Common.h>

#include "ActionMgr.h"
#include "Action/Action.h"
#include "Action/ActionCast.h"
#include "Action/ActionMount.h"

#include "Framework.h"

extern Core::Framework g_fw;

void Core::Action::ActionMgr::actionRouter( Core::Entity::Player& player, uint8_t type,
                                            uint32_t actionId, uint32_t useCount, uint64_t targetId )
{
   switch( type )
   {
      case Common::SkillType::Normal:
      {
         if( actionId < 1000000 )
            handleAction( player, actionId, useCount, targetId );
         else if( actionId < 2000000 )
            handleCraftAction( player, actionId, useCount, targetId );
         else if( actionId < 3000000 )
            handleItemAction( player, actionId, useCount, targetId );

         break;
      }

      case Common::SkillType::MountSkill:
      {
         handleMount( player, actionId );

         break;
      }

      default:
         break;
   }

}

void Core::Action::ActionMgr::handleAction( Core::Entity::Player& player, uint32_t actionId, uint32_t useCount, uint64_t targetId )
{
   auto pExdData = g_fw.get< Data::ExdDataGenerated >();
   auto pActionData = pExdData->get< Core::Data::Action >( actionId );

   if( !pActionData )
      return;

   // teleport
   // todo: we construct the cast from the actorcontrol event, that's pretty shit
   if( actionId == 5 )
   {
      auto action = player.getCurrentAction();

      if( action )
         action->onStart();

      return;
   }

   // check target
   Core::Entity::ActorPtr targetActor = player.getAsPlayer();
   if( targetActor->getId() != player.getId() )
   {
      targetActor = player.lookupTargetById( targetId );
   }

   if( !targetActor )
   {
      player.sendDebug( "Invalid target." );
      return;
   }

   // todo: check target validity: can target self, party member, enemy, etc
   // todo: check cooldowns, can't cast if its on cooldown
   // todo: restrict pvp actions to pvp areas and etc

   ActionPtr action;

   if( pActionData->cast100ms == 0 )
      action = make_Action( player.getAsPlayer(), targetActor->getAsChara(), actionId );
   else
   {
      action = make_ActionCast( player.getAsPlayer(), targetActor->getAsChara(), actionId );

      // only set the current action when there's a cast time, useless otherwise
      player.setCurrentAction( action );
   }

   action->startAction();
}

void Core::Action::ActionMgr::handleCraftAction( Core::Entity::Player& player, uint32_t actionId, uint32_t useCount, uint64_t targetId )
{
   auto pExdData = g_fw.get< Data::ExdDataGenerated >();
   auto action = pExdData->get< Core::Data::CraftAction >( actionId );

   if( !action )
      return;
}

void Core::Action::ActionMgr::handleItemAction( Core::Entity::Player& player, uint32_t actionId, uint32_t useCount, uint64_t targetId )
{
////     auto info = pExdData->get< Core::Data::EventItem >( action );
////     if( info )
////     {
////         pScriptMgr->onEventItem( player, action, info->quest, info->castTime, targetId );
////     }
}

void Core::Action::ActionMgr::handleMount( Core::Entity::Player& player, uint32_t mountId )
{
   if( player.hasStateFlag( Common::PlayerStateFlag::Casting ) )
      return;

   auto action = make_ActionMount( player.getAsChara(), mountId );

   player.setCurrentAction( action );
   action->startAction();
}