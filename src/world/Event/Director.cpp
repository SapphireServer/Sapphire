#include "Director.h"

#include <Network/PacketDef/Ipcs.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/CommonActorControl.h>

#include "Actor/Player.h"

#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include <Logging/Logger.h>


using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;

Sapphire::Event::Director::Director( Sapphire::Event::Director::DirectorType type, uint16_t contentId ) :
  m_contentId( contentId ),
  m_type( type ),
  m_directorId( ( static_cast< uint32_t >( type ) << 16 ) | contentId ),
  m_sequence( 1 ),
  m_branch( 0 ),
  m_elapsedTime( 0 )
{
  memset( m_unionData.arrData, 0, sizeof( m_unionData ) );
}

uint32_t Sapphire::Event::Director::getDirectorId() const
{
  return m_directorId;
}

uint16_t Sapphire::Event::Director::getContentId() const
{
  return m_contentId;
}

uint8_t Sapphire::Event::Director::getSequence() const
{
  return m_sequence;
}

void Sapphire::Event::Director::sendDirectorClear( Sapphire::Entity::Player& player ) const
{
  player.queuePacket( makeActorControl143( player.getId(), DirectorClear, m_directorId ) );
}

void Sapphire::Event::Director::sendDirectorVars( Sapphire::Entity::Player& player ) const
{
  auto varPacket = makeZonePacket< FFXIVIpcDirectorVars >( player.getId() );
  varPacket->data().m_directorId = getDirectorId();
  varPacket->data().m_sequence = getSequence();
  varPacket->data().m_branch = 0;
  memcpy( varPacket->data().m_unionData, m_unionData.arrData, sizeof( varPacket->data().m_unionData ) );
  player.queuePacket( varPacket );
}

void Sapphire::Event::Director::sendDirectorInit( Sapphire::Entity::Player& player ) const
{
  Logger::debug( "DirectorID#{}, QuestBattleID#{}", m_directorId, m_contentId );
  player.queuePacket( makeActorControl143( player.getId(), DirectorInit, m_directorId, m_contentId ) );
}

Sapphire::Event::Director::DirectorType Sapphire::Event::Director::getType() const
{
  return m_type;
}

uint8_t Sapphire::Event::Director::getBranch() const
{
  return m_branch;
}

void Sapphire::Event::Director::setDirectorUI8AL( uint8_t value )
{
  m_unionData.ui8lh.UI8AL = value;
}

void Sapphire::Event::Director::setDirectorUI8AH( uint8_t value )
{
  m_unionData.ui8lh.UI8AH = value;
}

void Sapphire::Event::Director::setDirectorUI8BL( uint8_t value )
{
  m_unionData.ui8lh.UI8BL = value;
}

void Sapphire::Event::Director::setDirectorUI8BH( uint8_t value )
{
  m_unionData.ui8lh.UI8BH = value;
}

void Sapphire::Event::Director::setDirectorUI8CL( uint8_t value )
{
  m_unionData.ui8lh.UI8CL = value;
}

void Sapphire::Event::Director::setDirectorUI8CH( uint8_t value )
{
  m_unionData.ui8lh.UI8CH = value;
}

void Sapphire::Event::Director::setDirectorUI8DL( uint8_t value )
{
  m_unionData.ui8lh.UI8DL = value;
}

void Sapphire::Event::Director::setDirectorUI8DH( uint8_t value )
{
  m_unionData.ui8lh.UI8DH = value;
}

void Sapphire::Event::Director::setDirectorUI8EL( uint8_t value )
{
  m_unionData.ui8lh.UI8EL = value;
}

void Sapphire::Event::Director::setDirectorUI8EH( uint8_t value )
{
  m_unionData.ui8lh.UI8EH = value;
}

void Sapphire::Event::Director::setDirectorUI8FL( uint8_t value )
{
  m_unionData.ui8lh.UI8FL = value;
}

void Sapphire::Event::Director::setDirectorUI8FH( uint8_t value )
{
  m_unionData.ui8lh.UI8FH = value;
}

void Sapphire::Event::Director::setDirectorUI8GL( uint8_t value )
{
  m_unionData.ui8lh.UI8GL = value;
}

void Sapphire::Event::Director::setDirectorUI8GH( uint8_t value )
{
  m_unionData.ui8lh.UI8GH = value;
}

void Sapphire::Event::Director::setDirectorUI8HL( uint8_t value )
{
  m_unionData.ui8lh.UI8HL = value;
}

void Sapphire::Event::Director::setDirectorUI8HH( uint8_t value )
{
  m_unionData.ui8lh.UI8HH = value;
}

void Sapphire::Event::Director::setDirectorUI8IL( uint8_t value )
{
  m_unionData.ui8lh.UI8IL = value;
}

void Sapphire::Event::Director::setDirectorUI8IH( uint8_t value )
{
  m_unionData.ui8lh.UI8IH = value;
}

void Sapphire::Event::Director::setDirectorUI8JL( uint8_t value )
{
  m_unionData.ui8lh.UI8JL = value;
}

void Sapphire::Event::Director::setDirectorUI8JH( uint8_t value )
{
  m_unionData.ui8lh.UI8JH = value;
}

void Sapphire::Event::Director::setDirectorBranch( uint8_t value )
{
  m_branch = value;
}

void Sapphire::Event::Director::setDirectorSequence( uint8_t value )
{
  m_sequence = value;
}

void Sapphire::Event::Director::setCustomVar( uint32_t varId, uint32_t value )
{
  m_customVarMap[ varId ] = value;
}

uint32_t Sapphire::Event::Director::getCustomVar( uint32_t varId )
{
  auto it = m_customVarMap.find( varId );
  if( it != m_customVarMap.end() )
    return it->second;
  return 0;
}