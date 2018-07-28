#include <Actor/Player.h>
#include <Exd/ExdDataGenerated.h>
#include <Script/ScriptMgr.h>

#include "ActionMgr.h"
#include "Action/Action.h"
#include "Action/ActionCast.h"

#include "Framework.h"

extern Core::Framework g_fw;

Core::Action::ActionMgr::ActionMgr()
{
}

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



         break;
      }

      default:
         break;
   }

}

void Core::Action::ActionMgr::handleAction( Core::Entity::Player& player, uint32_t actionId, uint32_t useCount, uint64_t targetId )
{
   auto pExdData = g_fw.get< Data::ExdDataGenerated >();
   auto pAction = pExdData->get< Core::Data::Action >( actionId );

   if( !pAction )
      return;

   // teleport
   // todo: is there a better way of handling this?
   // we construct the cast from the actorcontrol event, is there a better way to deal with this?
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
      player.sendDebug( "Invalid target. " );
      return;
   }

   // todo: check target validity: can target self, party member, enemy, etc
   // todo: check cooldowns, can't cast if its on cooldown

   ActionPtr action;

   if( pAction->cast100ms == 0 )
      action = make_Action( player.getAsPlayer(), targetActor->getAsChara(), actionId );
   else
      action = make_ActionCast( player.getAsPlayer(), targetActor->getAsChara(), actionId );

   player.setCurrentAction( action );
   action->start();
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

}