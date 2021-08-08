#include <Common.h>
#include <Logging/Logger.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/CommonActorControl.h>
#include <Service.h>

#include "Actor/Player.h"
#include "Actor/EventObject.h"
#include "Event/Director.h"
#include "Event/EventDefs.h"
#include "Event/EventHandler.h"
#include "Script/ScriptMgr.h"

#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"

#include "PublicContent.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;

Sapphire::PublicContent::PublicContent( std::shared_ptr< Sapphire::Data::PublicContent > pConfiguration,
                                            uint16_t territoryType,
                                            uint32_t guId,
                                            const std::string& internalName,
                                            const std::string& contentName,
                                            uint32_t contentId ) :
  Territory( static_cast< uint16_t >( territoryType ), guId, internalName, contentName ),
  Director( Event::Director::PublicContent, contentId ),
  m_Configuration( pConfiguration ),
  m_ContentId( contentId )
{

}

bool Sapphire::PublicContent::init()
{
  if( !Territory::init() )
    return false;

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onPublicContentInit( getAsPublicContent() );

  return true;
}


Sapphire::PublicContent::~PublicContent()
{

}

uint32_t Sapphire::PublicContent::getContentId() const
{
  return m_ContentId;
}

Sapphire::Data::ExdDataGenerated::PublicContentPtr Sapphire::PublicContent::getConfiguration() const
{
  return m_Configuration;
}

void Sapphire::PublicContent::onPlayerZoneIn( Entity::Player& player )
{
  Logger::debug( "PublicContent::onPlayerZoneIn: Territory#{0}|{1}, Entity#{2}", getGuId(), getTerritoryTypeId(), player.getId() );
  sendDirectorInit( player );

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onPublicContentPlayerZoneIn( getAsPublicContent(), player );
}

void Sapphire::PublicContent::onLeaveTerritory( Entity::Player& player )
{
  Logger::debug( "PublicContent::onLeaveTerritory: Territory#{0}|{1}, Entity#{2}", getGuId(), getTerritoryTypeId(), player.getId() );
  clearDirector( player );

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onPublicContentLeaveTerritory( getAsPublicContent(), player );
}

void Sapphire::PublicContent::onUpdate( uint64_t tickCount )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onPublicContentUpdate( getAsPublicContent(), tickCount );
}

void Sapphire::PublicContent::onFinishLoading( Entity::Player& player )
{
  sendDirectorInit( player );
}

void Sapphire::PublicContent::onInitDirector( Entity::Player& player )
{
  sendDirectorVars( player );
  player.setDirectorInitialized( true );
}

void Sapphire::PublicContent::onDirectorSync( Entity::Player& player )
{
  player.queuePacket( makeActorControlSelf( player.getId(), DirectorUpdate, 0x00110001, 0x80000000, 1 ) );
}

void Sapphire::PublicContent::onBeforePlayerZoneIn( Sapphire::Entity::Player& player )
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
  player.resetObjSpawnIndex();
}

void Sapphire::PublicContent::onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onPublicContentEnterTerritory( getAsPublicContent(), player, eventId, param1, param2 );
}

void Sapphire::PublicContent::onRegisterEObj( Entity::EventObjectPtr object )
{
  if( object->getName() != "none" )
    m_eventObjectMap[ object->getName() ] = object;
  if( object->getObjectId() == 2000182 ) // start
    m_pEntranceEObj = object;
  if( object->getName() == "Entrance" )
    m_pEntranceEObj = object;

  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto objData = exdData.get< Sapphire::Data::EObj >( object->getObjectId() );
  if( objData )
    m_eventIdToObjectMap[ objData->data ] = object;
  else
    Logger::error( "PublicContent::onRegisterEObj Territory " +
      m_internalName + ": No EObj data found for EObj with ID: " +
      std::to_string( object->getObjectId() ) );
}

void Sapphire::PublicContent::clearDirector( Entity::Player& player )
{
  sendDirectorClear( player );
  player.setDirectorInitialized( false );
}

void Sapphire::PublicContent::onTalk( Sapphire::Entity::Player& player, uint32_t eventId, uint64_t actorId )
{
  auto it = m_eventIdToObjectMap.find( eventId );
  if( it == m_eventIdToObjectMap.end() )
    return;

  if( auto onTalk = it->second->getOnTalkHandler() )
    onTalk( player, it->second, getAsPublicContent(), actorId );
  else
    player.sendDebug( "No onTalk handler found for interactable eobj with EObjID#{0}, eventId#{1}  ",
      it->second->getObjectId(), eventId );
}

void Sapphire::PublicContent::setVar( uint8_t index, uint8_t value )
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

void Sapphire::PublicContent::setSequence( uint8_t value )
{
  setDirectorSequence( value );

  for( const auto& playerIt : m_playerMap )
  {
    sendDirectorVars( *playerIt.second );
  }
}

void Sapphire::PublicContent::setBranch( uint8_t value )
{
  setDirectorBranch( value );

  for( const auto& playerIt : m_playerMap )
  {
    sendDirectorVars( *playerIt.second );
  }
}