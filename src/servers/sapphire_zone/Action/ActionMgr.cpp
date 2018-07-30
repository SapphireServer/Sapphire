#include <Actor/Player.h>
#include <Exd/ExdDataGenerated.h>
#include <Script/ScriptMgr.h>

#include "ActionMgr.h"
#include "Action/Action.h"

#include "Framework.h"

extern Core::Framework g_fw;

Core::Action::ActionMgr::ActionMgr()
{
   m_skillTypeToActionIdMap[ Common::SkillType::MountSkill ] = 4;
}

void Core::Action::ActionMgr::actionRouter( Core::Entity::Player& player, uint8_t type,
                                            uint32_t actionId, uint32_t useCount, uint64_t targetId )
{
   if( type == Common::SkillType::Normal )
   {
      if( actionId < 1000000 )
         handleAction( player, actionId, useCount, targetId, type );
      else if( actionId < 2000000 )
         handleCraftAction( player, actionId, useCount, targetId, type );
      else if( actionId < 3000000 )
         handleItemAction( player, actionId, useCount, targetId, type );

      return;
   }

   // check if we have a skilltype to actionid mapping
   // if we do, actionId becomes the action param and the map provides the new actionId
   auto mappedAction = m_skillTypeToActionIdMap.find( type );
   if( mappedAction == m_skillTypeToActionIdMap.end() )
      return;

   handleAction( player, mappedAction->second, useCount, targetId, type, actionId );
}

void Core::Action::ActionMgr::handleAction( Core::Entity::Player& player, uint32_t actionId, uint32_t useCount, uint64_t targetId, uint8_t skillType, uint32_t param )
{
   auto pExdData = g_fw.get< Data::ExdDataGenerated >();
   auto pActionRow = pExdData->get< Core::Data::Action >( actionId );

   if( !pActionRow )
      return;

   // not castable by a player, ever
   if( pActionRow->classJob == -1 )
      return;

   auto pClassJobRow = pExdData->get< Core::Data::ClassJob >( pActionRow->classJob );

   auto classJob = static_cast< int8_t >( player.getClass() );

   // check if can be casted by current job/class
   if( classJob != pActionRow->classJob &&
       classJob != pClassJobRow->classJobParent &&
      static_cast< uint8_t >( Common::ClassJob::Adventurer ) != pActionRow->classJob )
      return;

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

   auto action = make_Action( player.getAsPlayer(), targetActor->getAsChara(), actionId );

   // only set the action if it has a cast time, not much point otherwise
   if( action->getCastTime() != 0 )
      player.setCurrentAction( action );

   action->setParam( param );

   action->startAction();
}

void Core::Action::ActionMgr::handleCraftAction( Core::Entity::Player& player, uint32_t actionId, uint32_t useCount, uint64_t targetId, uint32_t param )
{
   auto pExdData = g_fw.get< Data::ExdDataGenerated >();
   auto action = pExdData->get< Core::Data::CraftAction >( actionId );

   if( !action )
      return;
}

void Core::Action::ActionMgr::handleItemAction( Core::Entity::Player& player, uint32_t actionId, uint32_t useCount, uint64_t targetId, uint32_t param )
{
   auto pExdData = g_fw.get< Data::ExdDataGenerated >();
   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();

   auto info = pExdData->get< Core::Data::EventItem >( actionId );
   if( info )
   {
       pScriptMgr->onEventItem( player, actionId, info->quest, info->castTime, targetId );
   }
}