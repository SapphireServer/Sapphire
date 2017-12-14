#include <Server_Common/Logging/Logger.h>
#include <Server_Common/Exd/ExdData.h>

#include "NativeScriptManager.h"

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

// enable the ambiguity fix for every platform to avoid #define nonsense
#define WIN_AMBIGUITY_FIX
#include <libraries/external/watchdog/Watchdog.h>

extern Core::Logger g_log;
extern Core::Data::ExdData g_exdData;
extern Core::ServerZone g_serverZone;

Core::Scripting::ScriptManager::ScriptManager() :
   m_firstScriptChangeNotificiation( false )
{
   m_nativeScriptManager = createNativeScriptMgr();
}

Core::Scripting::ScriptManager::~ScriptManager()
{
   Watchdog::unwatchAll();
}

void Core::Scripting::ScriptManager::update()
{
   m_nativeScriptManager->processLoadQueue();
}

bool Core::Scripting::ScriptManager::init()
{
   std::set< std::string > files;

   loadDir( g_serverZone.getConfig()->getValue< std::string >( "Settings.General.Scripts.Path", "./compiledscripts/" ),
            files, m_nativeScriptManager->getModuleExtension() );

   uint32_t scriptsFound = 0;
   uint32_t scriptsLoaded = 0;

   for( auto itr = files.begin(); itr != files.end(); ++itr )
   {
      auto& path = *itr;

      scriptsFound++;

      if( m_nativeScriptManager->loadScript( path ) )
         scriptsLoaded++;
   }

   g_log.info( "ScriptManager: Loaded " + std::to_string( scriptsLoaded ) + "/" + std::to_string( scriptsFound ) + " scripts successfully" );

   watchDirectories();

   return true;
}

void Core::Scripting::ScriptManager::watchDirectories()
{
   Watchdog::watchMany( g_serverZone.getConfig()->getValue< std::string >( "Settings.General.Scripts.Path", "./compiledscripts/" ) + "*" + m_nativeScriptManager->getModuleExtension(),
   [ this ]( const std::vector< ci::fs::path >& paths )
   {
      if( !m_firstScriptChangeNotificiation )
      {
         // for whatever reason, the first time this runs, it detects every file as changed
         // so we're always going to ignore the first notification
         m_firstScriptChangeNotificiation = true;
         return;
      }

      for( auto path : paths )
      {
         if( m_nativeScriptManager->isModuleLoaded( path.stem().string() ) )
         {
            g_log.debug( "Reloading changed script: " + path.stem().string() );

            m_nativeScriptManager->queueScriptReload( path.stem( ).string( ));
         }
         else
         {
            g_log.debug( "Loading new script: " + path.stem().string() );

            m_nativeScriptManager->loadScript( path.string() );
         }
      }
   });
}

void Core::Scripting::ScriptManager::loadDir( const std::string& dirname, std::set<std::string> &files, const std::string& ext )
{

   g_log.info( "ScriptEngine: loading scripts from " + dirname );

   boost::filesystem::path targetDir( dirname );

   boost::filesystem::directory_iterator iter( targetDir );
   boost::filesystem::directory_iterator eod;

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
      scriptId = EVENTSCRIPT_AETHERYTE_ID;
      if( !aetherInfo->isAetheryte )
         scriptId = EVENTSCRIPT_AETHERNET_ID;
   }

   auto script = m_nativeScriptManager->getEventScript( scriptId );
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

   player.sendDebug( "Calling: " + objName + "." + eventName + " - " + std::to_string( eventId ) );

   auto script = m_nativeScriptManager->getEventScript( eventId );
   if( script )
   {
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

   std::string eventName = "onWithinRange";
   std::string objName = Event::getEventName( eventId );
   player.sendDebug( "Calling: " + objName + "." + eventName + " - " + std::to_string( eventId ) + " p1: " + std::to_string( param1 ) );

   auto script = m_nativeScriptManager->getEventScript( eventId );
   if( script )
   {
      player.eventStart( player.getId(), eventId, Event::Event::WithinRange, 1, param1 );

      script->onWithinRange( player, eventId, param1, x, y, z );

      player.checkEvent( eventId );

      return true;
   }

   return false;
}

bool Core::Scripting::ScriptManager::onOutsideRange( Entity::Player& player, uint32_t eventId, uint32_t param1,
                                                     float x, float y, float z )
{
   std::string eventName = "onOutsideRange";
   std::string objName = Event::getEventName( eventId );
   player.sendDebug( "Calling: " + objName + "." + eventName + " - " + std::to_string( eventId ) );

   auto script = m_nativeScriptManager->getEventScript( eventId );
   if( script )
   {
      player.eventStart( player.getId(), eventId, Event::Event::WithinRange, 1, param1 );

      script->onOutsideRange( player, eventId, param1, x, y, z );

      player.checkEvent( eventId );

      return true;
   }

   return false;
}

bool Core::Scripting::ScriptManager::onEmote( Entity::Player& player, uint64_t actorId,
                                              uint32_t eventId, uint8_t emoteId )
{
   std::string eventName = "onEmote";
   std::string objName = Event::getEventName( eventId );

   auto script = m_nativeScriptManager->getEventScript( eventId );
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
   auto script = m_nativeScriptManager->getEventScript( eventId );
   if( script )
   {
      script->onEventHandlerTradeReturn( player, eventId, subEvent, param, catalogId );

      return true;
   }

   return false;
}

bool Core::Scripting::ScriptManager::onEventItem( Entity::Player& player, uint32_t eventItemId,
                                                  uint32_t eventId, uint32_t castTime, uint64_t targetId )
{
   std::string eventName = "onEventItem";
   std::string objName = Event::getEventName( eventId );
   player.sendDebug( "Calling: " + objName + "." + eventName + " - " + std::to_string( eventId ) );

   auto script = m_nativeScriptManager->getEventScript( eventId );
   if( script )
   {
      player.eventStart( targetId, eventId, Event::Event::Item, 0, 0 );

      script->onEventItem( player, eventItemId, eventId, castTime, targetId );

      return true;
   }

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

      auto script = m_nativeScriptManager->getEventScript( questId );
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
   auto script = m_nativeScriptManager->getActionScript( actionId );

   if( script )
      script->onCastFinish( player, *pTarget );

   return true;
}

bool Core::Scripting::ScriptManager::onStatusReceive( Entity::ActorPtr pActor, uint32_t effectId )
{
   auto script = m_nativeScriptManager->getStatusEffectScript( effectId );
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
   auto script = m_nativeScriptManager->getStatusEffectScript( effect.getId() );
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
   auto script = m_nativeScriptManager->getStatusEffectScript( effectId );
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
   auto script = m_nativeScriptManager->getZoneScript( pZone->getId() );
   if( script )
   {
      script->onZoneInit();

      return true;
   }

   return false;
}

Scripting::NativeScriptManager& Core::Scripting::ScriptManager::getNativeScriptHandler()
{
   return *m_nativeScriptManager;
}
