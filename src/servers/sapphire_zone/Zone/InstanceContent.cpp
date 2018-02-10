#include "InstanceContent.h"

#include <common/Common.h>
#include <common/Logging/Logger.h>
#include <common/Util/Util.h>
#include <common/Util/UtilMath.h>

#include "Event/Director.h"
#include "Script/ScriptManager.h"

#include "Actor/Player.h"

#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"

extern Core::Logger g_log;
extern Core::Scripting::ScriptManager g_scriptMgr;

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
     m_state( Created )
{
   g_scriptMgr.onInstanceInit( *this );
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

void Core::InstanceContent::onEnterTerritory( Entity::Player& player )
{
   g_log.debug( "InstanceContent::onEnterTerritory: Zone#" + std::to_string( getGuId() ) + "|"
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
   g_log.debug( "InstanceContent::onLeaveTerritory: Zone#" + std::to_string( getGuId() ) + "|"
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

         for( const auto &playerIt : m_playerMap )
         {
            if( !playerIt.second->isLoadingComplete() || !playerIt.second->isDirectorInitialized() )
               return;
         }

         for( const auto &playerIt : m_playerMap )
         {
            auto pPlayer = playerIt.second;
            pPlayer->queuePacket(
                    ActorControlPacket143( pPlayer->getId(), DirectorUpdate,
                                           getDirectorId(), 0x40000001, m_instanceContentInfo->timeLimitmin * 60u ) );
         }

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

   g_scriptMgr.onInstanceUpdate( *this, currTime );
}

void Core::InstanceContent::onFinishLoading( Entity::Player& player )
{
   if( m_state != Created )
      sendDirectorInit( player );
}

void Core::InstanceContent::onInitDirector( Entity::Player& player )
{
   sendDirectorVars( player );
   player.setDirectorInitialized( true );
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

   for( const auto &playerIt : m_playerMap )
   {
      sendDirectorVars( *playerIt.second );
   }
}