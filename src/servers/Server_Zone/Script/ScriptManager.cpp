#include <Server_Common/Logging/Logger.h>
#include <Server_Common/Exd/ExdData.h>
#include <chaiscript/chaiscript.hpp>

#include <Server_Common/Script/ChaiscriptStdLib.h>

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

extern Core::Logger g_log;
extern Core::Data::ExdData g_exdData;
extern Core::ServerZone g_serverZone;

Core::Scripting::ScriptManager::ScriptManager()
{
   m_pChaiHandler = create_chaiscript();
}

Core::Scripting::ScriptManager::~ScriptManager()
{

}

void Core::Scripting::ScriptManager::loadDir( std::string dirname, std::set<std::string>& chaiFiles )
{

   g_log.info( "ScriptEngine: loading scripts from " + dirname );

   boost::filesystem::path targetDir( dirname );

   boost::filesystem::recursive_directory_iterator iter( targetDir ), eod;

   BOOST_FOREACH( boost::filesystem::path const& i, make_pair( iter, eod ) )
   {

      if( is_regular_file( i ) && boost::filesystem::extension( i.string() ) == ".chai" ||
          boost::filesystem::extension( i.string() ) == ".inc" )
      {
         chaiFiles.insert( i.string() );
      }
   }

}

void Core::Scripting::ScriptManager::onPlayerFirstEnterWorld( Entity::Player& player )
{
   try
   {
      std::string test = m_onFirstEnterWorld( player );
   }
   catch( const std::exception &e )
   {
      std::string what = e.what();
      g_log.Log( LoggingSeverity::error, what );
   }
}

bool Core::Scripting::ScriptManager::registerBnpcTemplate( std::string templateName, uint32_t bnpcBaseId,
                                                           uint32_t bnpcNameId, uint32_t modelId, std::string aiName )
{
   return g_serverZone.registerBnpcTemplate( templateName, bnpcBaseId, bnpcNameId, modelId, aiName );
}

void Core::Scripting::ScriptManager::reload()
{
   auto handler = create_chaiscript();
   m_pChaiHandler.swap( handler );
   init();
}

const boost::shared_ptr< chaiscript::ChaiScript >& Core::Scripting::ScriptManager::getHandler() const
{
   return m_pChaiHandler;
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

   try
   {
      // Get object from engine
      auto obj = m_pChaiHandler->eval( objName );
      player.sendDebug( "Calling: " + objName + "." + eventName );

      player.eventStart( actorId, eventId, Event::Event::Talk, 0, 0 );

      auto fn = m_pChaiHandler->eval< std::function< void( chaiscript::Boxed_Value &,
                                                           uint32_t, Entity::Player&, uint64_t ) > >( eventName );
      fn( obj, eventId, player, actorId );

      player.checkEvent( eventId );
   }
   catch( std::exception& e )
   {
      player.sendDebug( e.what( ) );

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

bool Core::Scripting::ScriptManager::onEnterTerritory( Entity::Player& player, uint32_t eventId,
                                                       uint16_t param1, uint16_t param2 )
{
   std::string eventName = "onEnterTerritory";
   std::string objName = Event::getEventName( eventId );

   try
   {
      // Get object from engine
      auto obj = m_pChaiHandler->eval( objName );

      player.sendDebug( "Calling: " + objName + "." + eventName );

      player.eventStart( player.getId(), eventId, Event::Event::EnterTerritory, 0, player.getZoneId() );

      auto fn = m_pChaiHandler->eval< std::function< void( chaiscript::Boxed_Value &, uint32_t,
                                                           Entity::Player&, uint16_t, uint16_t ) > >( eventName );
      fn( obj, eventId, player, param1, param2 );

      player.checkEvent( eventId );
   }
   catch( std::exception& e )
   {
      player.sendDebug( e.what() );
      return false;
   }
   return true;
}

bool Core::Scripting::ScriptManager::onWithinRange( Entity::Player& player, uint32_t eventId, uint32_t param1,
                                                    float x, float y, float z )
{
   std::string eventName = "onWithinRange";
   std::string objName = Event::getEventName( eventId );

   try
   {
      // Get object from engine
      auto obj = m_pChaiHandler->eval( Event::getEventName( eventId )  );

      player.sendDebug( "Calling: " + objName + "." + eventName );

      player.eventStart( player.getId(), eventId, Event::Event::WithinRange, 1, param1 );

      auto fn = m_pChaiHandler->eval< std::function< void( chaiscript::Boxed_Value &, uint32_t, Entity::Player&, uint32_t,
                                                           float, float, float ) > >( eventName );
      fn( obj, eventId, player, param1, x, y, z );

      player.checkEvent( eventId );
   }
   catch( std::exception& e )
   {
      player.sendDebug( e.what() );
      return false;
   }
   return true;
}

bool Core::Scripting::ScriptManager::onOutsideRange( Entity::Player& player, uint32_t eventId, uint32_t param1,
                                                     float x, float y, float z )
{
   std::string eventName = "onOutsideRange";
   std::string objName = Event::getEventName( eventId );

   try
   {
      // Get object from engine
      auto obj = m_pChaiHandler->eval( Event::getEventName( eventId ) );

      player.sendDebug( "Calling: " + objName + "." + eventName );

      player.eventStart( player.getId(), eventId, Event::Event::OutsideRange, 1, param1 );

      auto fn = m_pChaiHandler->eval< std::function< void( chaiscript::Boxed_Value &, uint32_t, Entity::Player&, uint32_t,
                                                           float, float, float ) > >( eventName );
      fn( obj, eventId, player, param1, x, y, z );

      player.checkEvent( eventId );
   }
   catch( std::exception& e )
   {
      player.sendDebug( e.what() );
      return false;
   }
   return true;
}

bool Core::Scripting::ScriptManager::onEmote( Entity::Player& player, uint64_t actorId,
                                              uint32_t eventId, uint8_t emoteId )
{
   std::string eventName = "onEmote";
   std::string objName = Event::getEventName( eventId );

   try
   {
      auto obj = m_pChaiHandler->eval( Event::getEventName( eventId ) );

      player.sendDebug( "Calling: " + objName + "." + eventName );

      player.eventStart( actorId, eventId, Event::Event::Emote, 0, emoteId );

      auto fn = m_pChaiHandler->eval< std::function< void( chaiscript::Boxed_Value &, uint32_t, Entity::Player&,
                                                           uint64_t, uint8_t ) > >( eventName );
      fn( obj, eventId, player, actorId, emoteId );

      player.checkEvent( eventId );
   }
   catch( std::exception& e )
   {
      uint16_t eventType = eventId >> 16;

      if( eventType == Common::EventType::Quest )
      {
         auto questInfo = g_exdData.getQuestInfo( eventId );
         if( questInfo )
         {
            player.sendDebug( "Quest not implemented: " + questInfo->name + "\n" + e.what() );
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
   std::string eventName = Event::getEventName( eventId ) + "_TRADE";

   try
   {
      auto fn = m_pChaiHandler->eval< std::function< void( Entity::Player&, uint32_t,
                                                           uint16_t, uint16_t, uint32_t ) > >( eventName );
      fn( player, eventId, subEvent, param, catalogId );
   }
   catch( ... )
   {
      return false;
   }

   return true;
}

bool Core::Scripting::ScriptManager::onEventItem( Entity::Player& player, uint32_t eventItemId,
                                                  uint32_t eventId, uint32_t castTime, uint64_t targetId )
{
   std::string eventName = "onEventItem";
   std::string objName = Event::getEventName( eventId );

   try
   {
      auto obj = m_pChaiHandler->eval( Event::getEventName( eventId ) );

      player.sendDebug( "Calling: " + objName + "." + eventName );

      player.eventStart( targetId, eventId, Event::Event::Item, 0, 0 );
      
      auto fn = m_pChaiHandler->eval< std::function< void( chaiscript::Boxed_Value &, uint32_t, Entity::Player&,
                                                           uint32_t, uint32_t, uint64_t ) > >( eventName );
      fn( obj, eventId, player, eventItemId, castTime, targetId );
   }
   catch( std::exception& e )
   {
      player.sendNotice( e.what() );
      return false;
   }

   return true;

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
      if( questId != 0 )
      {
         auto obj = m_pChaiHandler->eval( Event::getEventName( 0x00010000 | questId ) );
         std::string objName = Event::getEventName( 0x00010000 | questId );

         player.sendDebug("Calling: " + objName + "." + eventName);

         try
         {
            auto fn = m_pChaiHandler->eval< std::function< void( chaiscript::Boxed_Value &, Entity::Player& ) > >(eventName);
            fn( obj, player );
         }
         catch( std::exception& e )
         {
            g_log.info( e.what() );
         }

      }
   }

   return true;
}

bool Core::Scripting::ScriptManager::onCastFinish( Entity::Player& player, Entity::ActorPtr pTarget, uint32_t actionId )
{
    std::string eventName = "onFinish";

    try 
    {
        auto obj = m_pChaiHandler->eval( "skillDef_" + std::to_string( actionId ) );
        std::string objName = "skillDef_" + std::to_string( actionId );

        player.sendDebug( "Calling: " + objName + "." + eventName );
        auto fn = m_pChaiHandler->eval< std::function< void( chaiscript::Boxed_Value &, Entity::Player&,
                                                             Entity::Actor& ) > >( eventName );
        fn( obj, player, *pTarget );
    }
    catch( std::exception& e )
    {
        player.sendUrgent( e.what() );
    }

    return true;
}

bool Core::Scripting::ScriptManager::onStatusReceive( Entity::ActorPtr pActor, uint32_t effectId )
{
   std::string eventName = "onReceive";

   try
   {
      auto obj = m_pChaiHandler->eval( "statusDef_" + std::to_string( effectId ) );
      std::string objName = "statusDef_" + std::to_string( effectId );

      if( pActor->isPlayer() )
         pActor->getAsPlayer()->sendDebug( "Calling: " + objName + "." + eventName );

      auto fn = m_pChaiHandler->eval< std::function< void( chaiscript::Boxed_Value &, Entity::Actor&) > >( eventName );
      fn( obj, *pActor );
   }
   catch( std::exception& e )
   {
      if( pActor->isPlayer() )
         pActor->getAsPlayer()->sendUrgent( e.what() );
   }

   return true;
}

bool Core::Scripting::ScriptManager::onStatusTick( Entity::ActorPtr pActor, Core::StatusEffect::StatusEffect& effect )
{
   std::string eventName = "onTick";

   try
   {
      auto obj = m_pChaiHandler->eval( "statusDef_" + std::to_string( effect.getId() ) );
      std::string objName = "statusDef_" + std::to_string( effect.getId() );

      if( pActor->isPlayer() )
         pActor->getAsPlayer()->sendDebug( "Calling: " + objName + "." + eventName );

      auto fn = m_pChaiHandler->eval< std::function< void( chaiscript::Boxed_Value &, Entity::Actor&,
                                                           StatusEffect::StatusEffect& ) > >( eventName );
      fn( obj, *pActor, effect );
   }
   catch( std::exception& e )
   {
      if( pActor->isPlayer() )
         pActor->getAsPlayer()->sendUrgent( e.what() );
   }

   return true;
}

bool Core::Scripting::ScriptManager::onStatusTimeOut( Entity::ActorPtr pActor, uint32_t effectId )
{
   std::string eventName = "onTimeOut";

   try
   {
      auto obj = m_pChaiHandler->eval( "statusDef_" + std::to_string( effectId ) );
      std::string objName = "statusDef_" + std::to_string( effectId );

      if( pActor->isPlayer() )
         pActor->getAsPlayer()->sendDebug( "Calling: " + objName + "." + eventName );

      auto fn = m_pChaiHandler->eval< std::function< void( chaiscript::Boxed_Value &, Entity::Actor& ) > >( eventName );
      fn( obj, *pActor );
   }
   catch( std::exception& e )
   {
      if( pActor->isPlayer() )
         pActor->getAsPlayer()->sendUrgent( e.what() );
   }

   return true;
}

bool Core::Scripting::ScriptManager::onZoneInit( ZonePtr pZone )
{
   std::string eventName = "onZoneInit_" + pZone->getInternalName();

   try
   {
      auto fn = m_pChaiHandler->eval< std::function< void( Zone& ) > >( eventName );
      fn( *pZone );
   }
   catch( std::exception& e )
   {
      g_log.info( e.what() );
      return false;
   }

   return true;

}

