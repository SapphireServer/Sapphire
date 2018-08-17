#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>

#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include <Config/XMLConfig.h>

#include "watchdog/Watchdog.h"

#include "Zone/Zone.h"
#include "Zone/InstanceContent.h"
#include "Actor/Player.h"
#include "ServerZone.h"
#include "Event/EventHandler.h"
#include "Event/EventHelper.h"

#include "StatusEffect/StatusEffect.h"

#include "Network/PacketWrappers/ServerNoticePacket.h"

#include "Script/ScriptMgr.h"

#include "NativeScriptMgr.h"
#include "ServerZone.h"
#include "Framework.h"

// enable the ambiguity fix for every platform to avoid #define nonsense
#define WIN_AMBIGUITY_FIX

extern Core::Framework g_fw;

Core::Scripting::ScriptMgr::ScriptMgr() :
   m_firstScriptChangeNotificiation( false )
{
   m_nativeScriptMgr = createNativeScriptMgr();
}

Core::Scripting::ScriptMgr::~ScriptMgr()
{
   Watchdog::unwatchAll();
}

void Core::Scripting::ScriptMgr::update()
{
   m_nativeScriptMgr->processLoadQueue();
}

bool Core::Scripting::ScriptMgr::init()
{
   std::set< std::string > files;
   auto pConfig = g_fw.get< XMLConfig >();
   auto pLog = g_fw.get< Logger >();

   auto status = loadDir( pConfig->getValue< std::string >( "Settings.General.Scripts.Path", "./compiledscripts/" ),
            files, m_nativeScriptMgr->getModuleExtension() );

   if( !status )
   {
      pLog->error( std::string( __func__ ) + ": failed to load scripts, the server will not function correctly without scripts loaded." );
      return false;
   }

   uint32_t scriptsFound = 0;
   uint32_t scriptsLoaded = 0;

   for( auto itr = files.begin(); itr != files.end(); ++itr )
   {
      auto& path = *itr;

      scriptsFound++;

      if( m_nativeScriptMgr->loadScript( path ) )
         scriptsLoaded++;
   }

   pLog->info( "ScriptMgr: Loaded " + std::to_string( scriptsLoaded ) + "/" + std::to_string( scriptsFound ) + " scripts successfully" );

   watchDirectories();

   return true;
}

void Core::Scripting::ScriptMgr::watchDirectories()
{
   auto pConfig = g_fw.get< XMLConfig >();
   auto shouldWatch = pConfig->getValue< bool >( "Settings.General.Scripts.HotSwap.Enabled", true );
   if( !shouldWatch )
      return;

   Watchdog::watchMany( pConfig->getValue< std::string >( "Settings.General.Scripts.Path", "./compiledscripts/" ) + "*" + m_nativeScriptMgr->getModuleExtension(),
   [ this ]( const std::vector< ci::fs::path >& paths )
   {
      if( !m_firstScriptChangeNotificiation )
      {
         // for whatever reason, the first time this runs, it detects every file as changed
         // so we're always going to ignore the first notification
         m_firstScriptChangeNotificiation = true;
         return;
      }
      auto pLog = g_fw.get< Logger >();

      for( auto path : paths )
      {
         if( m_nativeScriptMgr->isModuleLoaded( path.stem().string() ) )
         {
            pLog->debug( "Reloading changed script: " + path.stem().string() );

            m_nativeScriptMgr->queueScriptReload( path.stem( ).string( ));
         }
         else
         {
            pLog->debug( "Loading new script: " + path.stem().string() );

            m_nativeScriptMgr->loadScript( path.string() );
         }
      }
   });
}

bool Core::Scripting::ScriptMgr::loadDir( const std::string& dirname, std::set<std::string>& files, const std::string& ext )
{

   auto pLog = g_fw.get< Logger >();
   pLog->info( "ScriptMgr: loading scripts from " + dirname );

   if( !boost::filesystem::exists( dirname ) )
   {
      pLog->error( "ScriptMgr: scripts directory doesn't exist" );
      return false;
   }

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

   if( files.size() )
      return true;
   else
   {
      pLog->error( "ScriptMgr: couldn't find any script modules" );
      return false;
   }
}

void Core::Scripting::ScriptMgr::onPlayerFirstEnterWorld( Entity::Player& player )
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

bool Core::Scripting::ScriptMgr::onTalk( Entity::Player& player, uint64_t actorId, uint32_t eventId )
{

   auto pExdData = g_fw.get< Data::ExdDataGenerated >();
   uint16_t eventType = eventId >> 16;
   uint32_t scriptId = eventId;

   // aethernet/aetherytes need to be handled separately
   if( eventType == Event::EventHandler::EventHandlerType::Aetheryte )
   {
      auto aetherInfo = pExdData->get< Core::Data::Aetheryte >( eventId & 0xFFFF );
      scriptId = EVENTSCRIPT_AETHERYTE_ID;
      if( !aetherInfo->isAetheryte )
         scriptId = EVENTSCRIPT_AETHERNET_ID;
   }

   auto script = m_nativeScriptMgr->getScript< EventScript >( scriptId );
   if( !script )
      return false;
   script->onTalk( eventId, player, actorId );
   return true;
}

bool Core::Scripting::ScriptMgr::onEnterTerritory( Entity::Player& player, uint32_t eventId,
                                                       uint16_t param1, uint16_t param2 )
{
   auto script = m_nativeScriptMgr->getScript< EventScript >( eventId );
   if( !script )
      return false;
   script->onEnterTerritory( player, eventId, param1, param2 );
   return true;
}

bool Core::Scripting::ScriptMgr::onWithinRange( Entity::Player& player, uint32_t eventId, uint32_t param1,
                                                    float x, float y, float z )
{
   auto script = m_nativeScriptMgr->getScript< EventScript >( eventId );
   if( !script )
      return false;
   script->onWithinRange( player, eventId, param1, x, y, z );
   return true;
}

bool Core::Scripting::ScriptMgr::onOutsideRange( Entity::Player& player, uint32_t eventId, uint32_t param1,
                                                     float x, float y, float z )
{
   auto script = m_nativeScriptMgr->getScript< EventScript >( eventId );
   if( !script )
      return false;
   script->onOutsideRange( player, eventId, param1, x, y, z );
   return true;
}

bool Core::Scripting::ScriptMgr::onEmote( Entity::Player& player, uint64_t actorId,
                                              uint32_t eventId, uint8_t emoteId )
{
   auto script = m_nativeScriptMgr->getScript< EventScript >( eventId );
   if( !script )
      return false;
   script->onEmote( actorId, eventId, emoteId, player );
   return true;
}

bool Core::Scripting::ScriptMgr::onEventHandlerReturn( Entity::Player& player, uint32_t eventId,
                                                           uint16_t subEvent, uint16_t param1, uint16_t param2,
                                                           uint16_t param3 )
{

   return false;
}

bool Core::Scripting::ScriptMgr::onEventHandlerTradeReturn( Entity::Player& player, uint32_t eventId,
                                                                uint16_t subEvent, uint16_t param, uint32_t catalogId )
{
   auto script = m_nativeScriptMgr->getScript< EventScript >( eventId );
   if( script )
   {
      script->onEventHandlerTradeReturn( player, eventId, subEvent, param, catalogId );
      return true;
   }

   return false;
}

bool Core::Scripting::ScriptMgr::onEventItem( Entity::Player& player, uint32_t eventItemId,
                                                  uint32_t eventId, uint32_t castTime, uint64_t targetId )
{
   std::string eventName = "onEventItem";
   std::string objName = Event::getEventName( eventId );
   player.sendDebug( "Calling: " + objName + "." + eventName + " - " + std::to_string( eventId ) );

   auto script = m_nativeScriptMgr->getScript< EventScript >( eventId );
   if( script )
   {
      player.eventStart( targetId, eventId, Event::EventHandler::Item, 0, 0 );

      script->onEventItem( player, eventItemId, eventId, castTime, targetId );
      return true;
   }

   return false;
}

bool Core::Scripting::ScriptMgr::onMobKill( Entity::Player& player, uint16_t nameId )
{
   std::string eventName = "onBnpcKill_" + std::to_string( nameId );


   // loop through all active quests and try to call available onMobKill callbacks
   for( size_t i = 0; i < 30; i++ )
   {
      auto activeQuests = player.getQuestActive( static_cast< uint16_t >( i ) );
      if( !activeQuests )
         continue;

      uint16_t questId = activeQuests->c.questId;

      auto script = m_nativeScriptMgr->getScript< EventScript >( questId );
      if( script )
      {
         std::string objName = Event::getEventName( 0x00010000 | questId );

         player.sendDebug("Calling: " + objName + "." + eventName);

         script->onNpcKill( nameId, player );
      }
   }

   return true;
}

bool Core::Scripting::ScriptMgr::onCastFinish( Entity::Player& player, Entity::CharaPtr pTarget, uint32_t actionId )
{
   auto script = m_nativeScriptMgr->getScript< ActionScript >( actionId );

   if( script )
      script->onCastFinish( player, *pTarget );
   return true;
}

bool Core::Scripting::ScriptMgr::onStatusReceive( Entity::CharaPtr pActor, uint32_t effectId )
{
   auto script = m_nativeScriptMgr->getScript< StatusEffectScript >( effectId );

   if( script )
   {
      if( pActor->isPlayer() )
         pActor->getAsPlayer()->sendDebug( "Calling status receive for statusid: " + std::to_string( effectId ) );

      script->onApply( *pActor );
      return true;
   }

   return false;
}

bool Core::Scripting::ScriptMgr::onStatusTick( Entity::CharaPtr pChara, Core::StatusEffect::StatusEffect& effect )
{
   auto script = m_nativeScriptMgr->getScript< StatusEffectScript >( effect.getId() );
   if( script )
   {
      if( pChara->isPlayer() )
         pChara->getAsPlayer()->sendDebug( "Calling status tick for statusid: " + std::to_string( effect.getId() ) );

      script->onTick( *pChara );
      return true;
   }

   return false;
}

bool Core::Scripting::ScriptMgr::onStatusTimeOut( Entity::CharaPtr pChara, uint32_t effectId )
{
   auto script = m_nativeScriptMgr->getScript< StatusEffectScript >( effectId );
   if( script )
   {
      if( pChara->isPlayer() )
         pChara->getAsPlayer()->sendDebug( "Calling status timeout for statusid: " + std::to_string( effectId ) );

      script->onExpire( *pChara );
      return true;
   }

   return false;
}

bool Core::Scripting::ScriptMgr::onZoneInit( ZonePtr pZone )
{
   auto script = m_nativeScriptMgr->getScript< ZoneScript >( pZone->getTerritoryId() );
   if( script )
   {
      script->onZoneInit();
      return true;
   }

   return false;
}

bool Core::Scripting::ScriptMgr::onInstanceInit( InstanceContentPtr instance )
{
   auto script = m_nativeScriptMgr->getScript< InstanceContentScript >( instance->getDirectorId() );
   if( script )
   {
      script->onInit( instance );
      return true;
   }

   return false;
}

bool Core::Scripting::ScriptMgr::onInstanceUpdate( InstanceContentPtr instance, uint32_t currTime )
{
   auto script = m_nativeScriptMgr->getScript< InstanceContentScript >( instance->getDirectorId() );

   if( script )
   {
      script->onUpdate( instance, currTime );
      return true;
   }

   return false;
}

bool Core::Scripting::ScriptMgr::onInstanceEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 )
{
   auto script = m_nativeScriptMgr->getScript< InstanceContentScript >( instance->getDirectorId() );
   if( script )
   {
      script->onEnterTerritory( instance, player, eventId, param1, param2 );
      return true;
   }

   return false;
}

Scripting::NativeScriptMgr& Core::Scripting::ScriptMgr::getNativeScriptHandler()
{
   return *m_nativeScriptMgr;
}
