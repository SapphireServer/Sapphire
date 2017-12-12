#include <Server_Common/Logging/Logger.h>
#include <Server_Common/Exd/ExdData.h>

#include "NativeScript.h"

#include "Zone/Zone.h"
#include "Actor/Player.h"
#include "Actor/BattleNpc.h"
#include "ServerZone.h"
#include "Event/Event.h"
#include "Event/EventHelper.h"
#include "StatusEffect/StatusEffect.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Script/ScriptManager.h"

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>

#include <Server_Common/Config/XMLConfig.h>

extern Core::Logger g_log;
extern Core::Data::ExdData g_exdData;
extern Core::ServerZone g_serverZone;

Core::Scripting::ScriptManager::ScriptManager()
{
   m_nativeScriptHandler = create_script_engine();
}

Core::Scripting::ScriptManager::~ScriptManager()
{

}

bool Core::Scripting::ScriptManager::init()
{
   std::set< std::string > files;

   loadDir( g_serverZone.getConfig()->getValue< std::string >( "Settings.General.ScriptPath", "./compiledscripts/" ),
            files, m_nativeScriptHandler->getModuleExtension() );

   for( auto itr = files.begin(); itr != files.end(); ++itr )
   {
      auto& path = *itr;

      g_log.debug( "got module: " + path );

      m_nativeScriptHandler->loadScript( path );
   }

   return true;
}

void Core::Scripting::ScriptManager::loadDir( std::string dirname, std::set<std::string>& files, std::string ext )
{

   g_log.info( "ScriptEngine: loading scripts from " + dirname );

   boost::filesystem::path targetDir( dirname );

   boost::filesystem::recursive_directory_iterator iter( targetDir ), eod;

   BOOST_FOREACH( boost::filesystem::path const& i, make_pair( iter, eod ) )
   {
      if( is_regular_file( i ) && boost::filesystem::extension( i.string() ) == ext )
      {
         files.insert( i.string() );
      }
   }

}

void Core::Scripting::ScriptManager::onPlayerFirstEnterWorld( Entity::Player& player )
{
//   try
//   {
//      std::string test = m_onFirstEnterWorld( player );
//   }
//   catch( const std::exception &e )
//   {
//      std::string what = e.what();
//      g_log.Log( LoggingSeverity::error, what );
//   }
}

bool Core::Scripting::ScriptManager::registerBnpcTemplate( std::string templateName, uint32_t bnpcBaseId,
                                                           uint32_t bnpcNameId, uint32_t modelId, std::string aiName )
{
   return g_serverZone.registerBnpcTemplate( templateName, bnpcBaseId, bnpcNameId, modelId, aiName );
}

void Core::Scripting::ScriptManager::reload()
{
//   auto handler = create_chaiscript();
//   m_pChaiHandler.swap( handler );
//   init();
}

bool Core::Scripting::ScriptManager::onTalk( Entity::Player& player, uint64_t actorId, uint32_t eventId )
{
   std::string eventName = "onTalk";
   std::string objName = Event::getEventName( eventId );

   player.sendDebug( "Actor: " +
                     std::to_string( actorId ) + " -> " +
                     std::to_string( Event::mapEventActorToRealActor( static_cast< uint32_t >( actorId ) ) ) +
                     " \neventId: " +
                     std::to_string( eventId ) +
                     " (0x" + boost::str( boost::format( "%|08X|" )
                                          % static_cast< uint64_t >( eventId & 0xFFFFFFF ) ) + ")" );

   uint16_t eventType = eventId >> 16;
   uint32_t scriptId = eventId;

   // aethernet/aetherytes need to be handled separately
   if( eventType == Common::EventType::Aetheryte )
   {
      auto aetherInfo = g_exdData.getAetheryteInfo( eventId & 0xFFFF );
      scriptId = 0x50000;
      if( !aetherInfo->isAetheryte )
         scriptId = 0x50001;
   }

   auto script = m_nativeScriptHandler->getQuestScript( scriptId );
   if( script )
   {
      player.sendDebug( "Calling: " + objName + "." + eventName );

      player.eventStart( actorId, eventId, Event::Event::Talk, 0, 0 );

      script->onTalk( eventId, player, actorId );

      player.checkEvent( eventId );
   }
   else
   {
      if ( eventType == Common::EventType::Quest )
      {
         auto questInfo = g_exdData.getQuestInfo( eventId );
         if ( questInfo )
         {
            player.sendUrgent( "Quest not implemented: " + questInfo->name );

         }
      }

      return false;
   }

   return true;
}

bool Core::Scripting::ScriptManager::onEnterTerritory( Entity::Player& player, uint32_t eventId,
                                                       uint16_t param1, uint16_t param2 )
{
   std::string eventName = "onEnterTerritory";
   std::string objName = Event::getEventName( eventId );

   auto script = m_nativeScriptHandler->getZoneScript( player.getZoneId() );
   if( script )
   {
      player.sendDebug( "Calling: " + objName + "." + eventName );

      player.eventStart( player.getId(), eventId, Event::Event::EnterTerritory, 0, player.getZoneId() );

      script->onEnterZone( player, eventId, param1, param2 );

      player.checkEvent( eventId );

      return true;
   }

   return false;
}

bool Core::Scripting::ScriptManager::onWithinRange( Entity::Player& player, uint32_t eventId, uint32_t param1,
                                                    float x, float y, float z )
{
//   std::string eventName = "onWithinRange";
//   std::string objName = Event::getEventName( eventId );
//
//   try
//   {
//      // Get object from engine
//      auto obj = m_pChaiHandler->eval( Event::getEventName( eventId )  );
//
//      player.sendDebug( "Calling: " + objName + "." + eventName );
//
//      player.eventStart( player.getId(), eventId, Event::Event::WithinRange, 1, param1 );
//
//      auto fn = m_pChaiHandler->eval< std::function< void( chaiscript::Boxed_Value &, uint32_t, Entity::Player&, uint32_t,
//                                                           float, float, float ) > >( eventName );
//      fn( obj, eventId, player, param1, x, y, z );
//
//      player.checkEvent( eventId );
//   }
//   catch( std::exception& e )
//   {
//      player.sendDebug( e.what() );
//      return false;
//   }
//   return true;

   return false;
}

bool Core::Scripting::ScriptManager::onOutsideRange( Entity::Player& player, uint32_t eventId, uint32_t param1,
                                                     float x, float y, float z )
{
//   std::string eventName = "onOutsideRange";
//   std::string objName = Event::getEventName( eventId );
//
//   try
//   {
//      // Get object from engine
//      auto obj = m_pChaiHandler->eval( Event::getEventName( eventId ) );
//
//      player.sendDebug( "Calling: " + objName + "." + eventName );
//
//      player.eventStart( player.getId(), eventId, Event::Event::OutsideRange, 1, param1 );
//
//      auto fn = m_pChaiHandler->eval< std::function< void( chaiscript::Boxed_Value &, uint32_t, Entity::Player&, uint32_t,
//                                                           float, float, float ) > >( eventName );
//      fn( obj, eventId, player, param1, x, y, z );
//
//      player.checkEvent( eventId );
//   }
//   catch( std::exception& e )
//   {
//      player.sendDebug( e.what() );
//      return false;
//   }
//   return true;

   return false;
}

bool Core::Scripting::ScriptManager::onEmote( Entity::Player& player, uint64_t actorId,
                                              uint32_t eventId, uint8_t emoteId )
{
   std::string eventName = "onEmote";
   std::string objName = Event::getEventName( eventId );

   auto script = m_nativeScriptHandler->getQuestScript( eventId );
   if( script )
   {
      player.sendDebug( "Calling: " + objName + "." + eventName );

      player.eventStart( actorId, eventId, Event::Event::Emote, 0, emoteId );

      script->onEmote( actorId, eventId, emoteId, player );

      player.checkEvent( eventId );
   }
   else
   {
      uint16_t eventType = eventId >> 16;

      if( eventType == Common::EventType::Quest )
      {
         auto questInfo = g_exdData.getQuestInfo( eventId );
         if( questInfo )
         {
            player.sendUrgent( "Quest not implemented: " + questInfo->name );
            return false;
         }
      }
      return false;
   }

   return true;
}

bool Core::Scripting::ScriptManager::onEventHandlerReturn( Entity::Player& player, uint32_t eventId,
                                                           uint16_t subEvent, uint16_t param1, uint16_t param2,
                                                           uint16_t param3 )
{

   player.sendDebug( "eventId: " +
                     std::to_string( eventId ) +
                     " ( 0x" + boost::str( boost::format( "%|08X|" ) % ( uint64_t ) ( eventId & 0xFFFFFFF ) ) + " ) " +
                     " scene: " + std::to_string( subEvent ) +
                     " p1: " + std::to_string( param1 ) +
                     " p2: " + std::to_string( param2 ) +
                     " p3: " + std::to_string( param3 ) );

   try
   {
      auto pEvent = player.getEvent( eventId );
      if( pEvent )
      {
         pEvent->setPlayedScene( false );
         // try to retrieve a stored callback
         auto eventCallback = pEvent->getEventReturnCallback();
         // if there is one, proceed to call it
         if( eventCallback )
         {
            eventCallback( player, eventId, param1, param2, param3 );
            if( !pEvent->hasPlayedScene() )
               player.eventFinish( eventId, 1 );
            else
               pEvent->setPlayedScene( false );
         }
            // else, finish the event.
         else
            player.eventFinish( eventId, 1 );
      }
   }
   catch( std::exception& e )
   {
      player.sendNotice( e.what() );
      return false;
   }

   return true;
}

bool Core::Scripting::ScriptManager::onEventHandlerTradeReturn( Entity::Player& player, uint32_t eventId,
                                                                uint16_t subEvent, uint16_t param, uint32_t catalogId )
{
//   std::string eventName = Event::getEventName( eventId ) + "_TRADE";
//
//   try
//   {
//      auto fn = m_pChaiHandler->eval< std::function< void( Entity::Player&, uint32_t,
//                                                           uint16_t, uint16_t, uint32_t ) > >( eventName );
//      fn( player, eventId, subEvent, param, catalogId );
//   }
//   catch( ... )
//   {
//      return false;
//   }
//
//   return true;

   return false;
}

bool Core::Scripting::ScriptManager::onEventItem( Entity::Player& player, uint32_t eventItemId,
                                                  uint32_t eventId, uint32_t castTime, uint64_t targetId )
{
//   std::string eventName = "onEventItem";
//   std::string objName = Event::getEventName( eventId );
//
//   try
//   {
//      auto obj = m_pChaiHandler->eval( Event::getEventName( eventId ) );
//
//      player.sendDebug( "Calling: " + objName + "." + eventName );
//
//      player.eventStart( targetId, eventId, Event::Event::Item, 0, 0 );
//
//      auto fn = m_pChaiHandler->eval< std::function< void( chaiscript::Boxed_Value &, uint32_t, Entity::Player&,
//                                                           uint32_t, uint32_t, uint64_t ) > >( eventName );
//      fn( obj, eventId, player, eventItemId, castTime, targetId );
//   }
//   catch( std::exception& e )
//   {
//      player.sendNotice( e.what() );
//      return false;
//   }
//
//   return true;
   return false;
}

bool Core::Scripting::ScriptManager::onMobKill( Entity::Player& player, uint16_t nameId )
{
   std::string eventName = "onBnpcKill_" + std::to_string( nameId );


   // loop through all active quests and try to call available onMobKill callbacks
   for( size_t i = 0; i < 30; i++ )
   {
      auto activeQuests = player.getQuestActive( static_cast< uint16_t >( i ) );
      if( !activeQuests )
         continue;

      uint16_t questId = activeQuests->c.questId;

      auto script = m_nativeScriptHandler->getQuestScript( questId );
      if( script )
      {
         std::string objName = Event::getEventName( 0x00010000 | questId );

         player.sendDebug("Calling: " + objName + "." + eventName);

         script->onNpcKill( nameId, player );
      }
   }

   return true;
}

bool Core::Scripting::ScriptManager::onCastFinish( Entity::Player& player, Entity::ActorPtr pTarget, uint32_t actionId )
{
   auto script = m_nativeScriptHandler->getActionScript( actionId );

   if( script )
      script->onCastFinish( player, *pTarget );

   return true;
}

bool Core::Scripting::ScriptManager::onStatusReceive( Entity::ActorPtr pActor, uint32_t effectId )
{
   auto script = m_nativeScriptHandler->getStatusEffectScript( effectId );
   if( script )
   {
      if( pActor->isPlayer() )
         pActor->getAsPlayer()->sendDebug( "Calling status receive for statusid: " + std::to_string( effectId ) );

      script->onApply( *pActor );

      return true;
   }

   return false;
}

bool Core::Scripting::ScriptManager::onStatusTick( Entity::ActorPtr pActor, Core::StatusEffect::StatusEffect& effect )
{
   auto script = m_nativeScriptHandler->getStatusEffectScript( effect.getId() );
   if( script )
   {
      if( pActor->isPlayer() )
         pActor->getAsPlayer()->sendDebug( "Calling status tick for statusid: " + std::to_string( effect.getId() ) );

      script->onTick( *pActor );

      return true;
   }

   return false;
}

bool Core::Scripting::ScriptManager::onStatusTimeOut( Entity::ActorPtr pActor, uint32_t effectId )
{
   auto script = m_nativeScriptHandler->getStatusEffectScript( effectId );
   if( script )
   {
      if( pActor->isPlayer() )
         pActor->getAsPlayer()->sendDebug( "Calling status timeout for statusid: " + std::to_string( effectId ) );

      script->onExpire( *pActor );

      return true;
   }

   return false;
}

bool Core::Scripting::ScriptManager::onZoneInit( ZonePtr pZone )
{
   auto script = m_nativeScriptHandler->getZoneScript( pZone->getId() );
   if( script )
   {
      script->onZoneInit();

      return true;
   }

   return false;
}

Scripting::NativeScript& Core::Scripting::ScriptManager::getNativeScriptHandler()
{
   return *m_nativeScriptHandler;
}
