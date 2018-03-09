
#include <Common.h>
#include <Logging/Logger.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Exd/ExdDataGenerated.h>

#include "Event/Director.h"
#include "Script/ScriptMgr.h"

#include "Actor/Player.h"
#include "Actor/EventObject.h"

#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"


#include "Event/EventHandler.h"

#include "InstanceContent.h"
#include "Framework.h"

extern Core::Framework g_fw;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

Core::InstanceContent::InstanceContent( boost::shared_ptr< Core::Data::InstanceContent > pInstanceContent,
                                        uint32_t guId,
                                        const std::string& internalName,
                                        const std::string& contentName,
                                        uint32_t instanceContentId )
   : Zone( static_cast< uint16_t >( pInstanceContent->territoryType ), guId, internalName, contentName ),
     Director( Event::Director::InstanceContent, instanceContentId ),
     m_instanceContentInfo( pInstanceContent ),
     m_instanceContentId( instanceContentId ),
     m_state( Created ),
     m_pEntranceEObj( nullptr ),
     m_instanceCommenceTime( 0 )
{

}

bool Core::InstanceContent::init()
{
   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();
   pScriptMgr->onInstanceInit( getAsInstanceContent() );

   return true;
}


Core::InstanceContent::~InstanceContent()
{

}

uint32_t Core::InstanceContent::getInstanceContentId() const
{
   return m_instanceContentId;
}

Core::Data::ExdDataGenerated::InstanceContentPtr Core::InstanceContent::getInstanceContentInfo() const
{
   return m_instanceContentInfo;
}

void Core::InstanceContent::onPlayerZoneIn( Entity::Player& player )
{
   auto pLog = g_fw.get< Logger >();
   pLog->debug( "InstanceContent::onEnterTerritory: Zone#" + std::to_string( getGuId() ) + "|"
                                                           + std::to_string( getInstanceContentId() ) +
                                                           + ", Entity#" + std::to_string( player.getId() ) );

   // mark player as "bound by duty"
   player.setStateFlag( PlayerStateFlag::BoundByDuty );

   // if the instance was not started yet, director init is sent on enter event.
   // else it will be sent on finish loading.
   if( m_state == Created )
      sendDirectorInit( player );

}

void Core::InstanceContent::onLeaveTerritory( Entity::Player& player )
{
   auto pLog = g_fw.get< Logger >();
   pLog->debug( "InstanceContent::onLeaveTerritory: Zone#" + std::to_string( getGuId() ) + "|"
                                                           + std::to_string( getInstanceContentId() ) +
                                                           + ", Entity#" + std::to_string( player.getId() ) );
   sendDirectorClear( player );

   player.setDirectorInitialized( false );
   // remove "bound by duty" state
   player.unsetStateFlag( PlayerStateFlag::BoundByDuty );
}

void Core::InstanceContent::onUpdate( uint32_t currTime )
{

   switch( m_state )
   {
      case Created:
      {
         // temporary handling for instance state progression
         if( m_playerMap.size() < 1 )
            return;

         for( const auto& playerIt : m_playerMap )
         {
            if( !playerIt.second->isLoadingComplete() ||
                !playerIt.second->isDirectorInitialized() ||
                !playerIt.second->isOnEnterEventDone() ||
                playerIt.second->hasStateFlag( PlayerStateFlag::WatchingCutscene ) )
               return;
         }

         if( m_instanceCommenceTime == 0 )
         {
            m_instanceCommenceTime = Util::getTimeMs() + instanceStartDelay;
            return;
         }
         else if( Util::getTimeMs() < m_instanceCommenceTime )
            return;

         for( const auto& playerIt : m_playerMap )
         {
            auto pPlayer = playerIt.second;
            pPlayer->queuePacket(
                    ActorControlPacket143( pPlayer->getId(), DirectorUpdate,
                                           getDirectorId(), 0x40000001, m_instanceContentInfo->timeLimitmin * 60u ) );
         }

         if( m_pEntranceEObj )
            m_pEntranceEObj->setState( 7 );
         m_state = DutyInProgress;
         m_instanceExpireTime = Util::getTimeSeconds() + ( m_instanceContentInfo->timeLimitmin * 60u );
         break;
      }


      case DutyReset:
         break;

      case DutyInProgress:
      {
         break;
      }


      case DutyFinished:
         break;
   }
   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();
   pScriptMgr->onInstanceUpdate( getAsInstanceContent(), currTime );

}

void Core::InstanceContent::onFinishLoading( Entity::Player& player )
{
   sendDirectorInit( player );
}

void Core::InstanceContent::onInitDirector( Entity::Player& player )
{
   sendDirectorVars( player );
   player.setDirectorInitialized( true );
}

void Core::InstanceContent::onSomeDirectorEvent( Entity::Player& player )
{
   player.queuePacket( ActorControlPacket143( player.getId(), DirectorUpdate, 0x00110001, 0x80000000, 1 ) );
}


void Core::InstanceContent::setVar( uint8_t index, uint8_t value )
{
   if( index > 19 )
      return;

   switch( index )
   {
      case 0:
         setDirectorUI8AL( value );
         break;
      case 1:
         setDirectorUI8AH( value );
         break;
      case 2:
         setDirectorUI8BL( value );
         break;
      case 3:
         setDirectorUI8BH( value );
         break;
      case 4:
         setDirectorUI8CL( value );
         break;
      case 5:
         setDirectorUI8CH( value );
         break;
      case 6:
         setDirectorUI8DL( value );
         break;
      case 7:
         setDirectorUI8DH( value );
         break;
      case 8:
         setDirectorUI8EL( value );
         break;
      case 9:
         setDirectorUI8EH( value );
         break;
      case 10:
         setDirectorUI8FL( value );
         break;
      case 11:
         setDirectorUI8FH( value );
         break;
      case 12:
         setDirectorUI8GL( value );
         break;
      case 13:
         setDirectorUI8GH( value );
         break;
      case 14:
         setDirectorUI8HL( value );
         break;
      case 15:
         setDirectorUI8HH( value );
         break;
      case 16:
         setDirectorUI8IL( value );
         break;
      case 17:
         setDirectorUI8IH( value );
         break;
      case 18:
         setDirectorUI8JL( value );
         break;
      case 19:
         setDirectorUI8JH( value );
         break;

   }

   // todo: genericise this?
   for( const auto& playerIt : m_playerMap )
   {
      sendDirectorVars( *playerIt.second );
   }
}

void Core::InstanceContent::setSequence( uint8_t value )
{
   setDirectorSequence( value );

   for( const auto& playerIt : m_playerMap )
   {
      sendDirectorVars( *playerIt.second );
   }
}

void Core::InstanceContent::setBranch( uint8_t value )
{
   setDirectorBranch( value );

   for( const auto& playerIt : m_playerMap )
   {
      sendDirectorVars( *playerIt.second );
   }
}

void Core::InstanceContent::onRegisterEObj( Entity::EventObjectPtr object )
{
   if( object->getName() != "none" )
      m_eventObjectMap[object->getName()] = object;
   if( object->getObjectId() == 2000182 ) // start
      m_pEntranceEObj = object;
   
   auto pLog = g_fw.get< Logger >();
   auto pExdData = g_fw.get< Data::ExdDataGenerated >();
   auto objData = pExdData->get< Core::Data::EObj >( object->getObjectId() );
   if( objData )
      // todo: data should be renamed to eventId
      m_eventIdToObjectMap[objData->data] = object;
   else
      pLog->error( "InstanceContent::onRegisterEObj Zone " +
                                     m_internalName + ": No EObj data found for EObj with ID: " +
                                     std::to_string( object->getObjectId() ) );
}

void Core::InstanceContent::onBeforePlayerZoneIn( Core::Entity::Player& player )
{
   // if a player has already spawned once inside this instance, don't move them if they happen to zone in again
   auto it = m_spawnedPlayers.find( player.getId() );
   if( it == m_spawnedPlayers.end() )
   {
      if( m_pEntranceEObj != nullptr )
      {
         player.setRot( PI );
         player.setPos( m_pEntranceEObj->getPos() );
      }
      else
      {
         player.setRot( PI );
         player.setPos( { 0.f, 0.f, 0.f } );
      }

      m_spawnedPlayers.insert( player.getId() );
   }

   player.resetObjSpawnIndex( );
}

Core::Entity::EventObjectPtr Core::InstanceContent::getEObjByName( const std::string& name )
{
   auto it = m_eventObjectMap.find( name );
   if( it == m_eventObjectMap.end() )
      return nullptr;

   return it->second;
}

void Core::InstanceContent::onTalk( Core::Entity::Player& player, uint32_t eventId, uint64_t actorId )
{
   // todo: handle exit (and maybe shortcut?) behaviour here

   auto it = m_eventIdToObjectMap.find( eventId );
   if( it == m_eventIdToObjectMap.end() )
      return;

   if( auto onTalk = it->second->getOnTalkHandler() )
      onTalk( player, it->second, getAsInstanceContent(), actorId );
   else
      player.sendDebug( "No onTalk handler found for interactable eobj with EObjID: " +
                        std::to_string( it->second->getObjectId() ) + ", eventId: " + std::to_string( eventId ) );
}

void Core::InstanceContent::onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 )
{
   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();
   pScriptMgr->onInstanceEnterTerritory( getAsInstanceContent(), player, eventId, param1, param2 );
}
