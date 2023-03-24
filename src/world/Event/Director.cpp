#include "Director.h"

#include <Territory/InstanceContent.h>

#include <Network/PacketWrappers/EventLogMessagePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/CommonActorControl.h>
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"
#include "Network/GameConnection.h"
#include "Network/Util/PacketUtil.h"

#include "Actor/Player.h"

#include <Logging/Logger.h>

#include <Service.h>
#include "WorldServer.h"
#include "Session.h"


using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;

Sapphire::Event::Director::Director( Sapphire::Event::Director::DirectorType type, uint16_t contentId ) :
  m_contextId( contentId ),
  m_type( type ),
  m_directorId( ( static_cast< uint32_t >( type ) << 16 ) | contentId ),
  m_sequence( 1 ),
  m_flags( 0 )
{
  memset( m_vars, 0, sizeof( m_vars ) );
}

uint32_t Sapphire::Event::Director::getDirectorId() const
{
  return m_directorId;
}

uint16_t Sapphire::Event::Director::getContextId() const
{
  return m_contextId;
}

uint8_t Sapphire::Event::Director::getSequence() const
{
  return m_sequence;
}

void Sapphire::Event::Director::sendEventLogMessage( Sapphire::Entity::Player& player, Sapphire::InstanceContent& instance, uint32_t msgId, std::initializer_list< uint32_t > args ) const
{
  FFXIVPacketBasePtr packet = nullptr;

  assert( args.size() <= 32 );

  if( args.size() == 0 )
  {
    packet = std::move( std::make_shared< class EventLogMessageHeader >( player, instance.getDirectorId(), msgId ) );
  }
  else if( args.size() <= 2 )
  {
    packet = std::move( std::make_shared< class EventLogMessage2 >( player, instance.getDirectorId(), msgId, args ) );
  }
  else if( args.size() <= 4 )
  {
    packet = std::move( std::make_shared< class EventLogMessage4 >( player, instance.getDirectorId(), msgId, args ) );
  }
  else if( args.size() <= 8 )
  {
    packet = std::move( std::make_shared< class EventLogMessage8 >( player, instance.getDirectorId(), msgId, args ) );
  }
  else if( args.size() <= 16 )
  {
    packet = std::move( std::make_shared< class EventLogMessage16 >( player, instance.getDirectorId(), msgId, args ) );
  }
  else if( args.size() <= 32 )
  {
    packet = std::move( std::make_shared< class EventLogMessage32 >( player, instance.getDirectorId(), msgId, args ) );
  }

  instance.queuePacketForZone( player, packet, true );
}

void Sapphire::Event::Director::sendDirectorClear( Sapphire::Entity::Player& player ) const
{
  Network::Util::Packet::sendActorControlSelf( player, player.getId(), DirectorClear, m_directorId );
}

void Sapphire::Event::Director::sendDirectorVars( Sapphire::Entity::Player& player ) const
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto varPacket = makeZonePacket< FFXIVIpcDirectorVars >( player.getId() );
  varPacket->data().directorId = getDirectorId();
  varPacket->data().sequence = getSequence();
  varPacket->data().flags = getFlags();
  memcpy( varPacket->data().vars, m_vars, sizeof( m_vars ) );
  server.queueForPlayer( player.getCharacterId(), varPacket );
}

void Sapphire::Event::Director::sendDirectorInit( Sapphire::Entity::Player& player ) const
{
  Logger::debug( "[{}] directorInit: directorId#{}, contextId#{}", player.getId(), m_directorId, m_contextId );
  Network::Util::Packet::sendActorControlSelf( player, player.getId(), DirectorInit, m_directorId, m_contextId );
}

Sapphire::Event::Director::DirectorType Sapphire::Event::Director::getType() const
{
  return m_type;
}

uint8_t Sapphire::Event::Director::getFlags() const
{
  return m_flags;
}

void Sapphire::Event::Director::setDirectorFlags( uint8_t value )
{
  m_flags = value;
}

void Sapphire::Event::Director::setDirectorSequence( uint8_t value )
{
  m_sequence = value;
}

void Sapphire::Event::Director::setDirectorVar( uint8_t index, uint8_t value )
{
  if( index < sizeof( m_vars ) )
  {
    m_vars[ index ] = value;
  }
  else
    Logger::warn( "[{0}] Director::setDirectorVar - out of range index {1} value {2}", m_directorId, index, value );
}

uint8_t Sapphire::Event::Director::getDirectorVar( uint8_t index )
{
  if( index < sizeof( m_vars ) )
  {
    return m_vars[ index ];
  }
  else
    Logger::warn( "[{0}] Director::getDirectorVar - out of range index {1}", m_directorId, index );

  return 0;
}

void Sapphire::Event::Director::setDirectorVar( uint8_t index, uint8_t valueLeft, uint8_t valueRight )
{
  setDirectorVar( index, ( valueRight & 0x0F ) + ( valueLeft << 4 ) );
}

uint8_t Sapphire::Event::Director::getDirectorVar( uint8_t index, bool shiftLeft )
{
  return getDirectorVar( index ) & ( shiftLeft ? 0xF0 : 0x0F );
}

void Sapphire::Event::Director::setCustomVar( uint32_t index, uint64_t value )
{
  m_customVarMap[ index ] = value;
}

uint64_t Sapphire::Event::Director::getCustomVar( uint32_t index )
{
  auto it = m_customVarMap.find( index );
  if( it != m_customVarMap.end() )
    return it->second;
  return 0;
}
