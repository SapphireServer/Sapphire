#include "Director.h"

#include <Network/PacketDef/Ipcs.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

#include "Actor/Player.h"

#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"


using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

Core::Event::Director::Director( Core::Event::Director::DirectorType type, uint16_t contentId ) :
   m_contentId( contentId ),
   m_type( type ),
   m_directorId( ( static_cast< uint32_t >( type ) << 16 ) | contentId ),
   m_sequence( 1 ),
   m_branch( 0 ),
   m_elapsedTime( 0 )
{
   memset( m_unionData.arrData, 0, sizeof( m_unionData ) );
}

uint32_t Core::Event::Director::getDirectorId() const
{
   return m_directorId;
}

uint16_t Core::Event::Director::getContentId() const
{
   return m_contentId;
}

uint8_t Core::Event::Director::getSequence() const
{
   return m_sequence;
}

void Core::Event::Director::sendDirectorClear( Core::Entity::Player& player ) const
{
   player.queuePacket( ActorControlPacket143( player.getId(), DirectorClear, m_directorId ) );
}

void Core::Event::Director::sendDirectorVars( Core::Entity::Player& player ) const
{
   ZoneChannelPacket< FFXIVIpcDirectorVars > varPacket( player.getId() );
   varPacket.data().m_directorId = getDirectorId();
   varPacket.data().m_sequence = getSequence();
   varPacket.data().m_branch = 0;
   memcpy( varPacket.data().m_unionData, m_unionData.arrData, sizeof( varPacket.data().m_unionData ) );
   player.queuePacket( varPacket );
}

void Core::Event::Director::sendDirectorInit( Core::Entity::Player& player ) const
{
   player.queuePacket( ActorControlPacket143( player.getId(), DirectorInit, m_directorId, m_contentId ) );
}

Core::Event::Director::DirectorType Core::Event::Director::getType() const
{
   return m_type;
}

uint8_t Core::Event::Director::getBranch() const
{
   return m_branch;
}

void Core::Event::Director::setDirectorUI8AL( uint8_t value )
{
   m_unionData.ui8lh.UI8AL = value;
}

void Core::Event::Director::setDirectorUI8AH( uint8_t value )
{
   m_unionData.ui8lh.UI8AH = value;
}

void Core::Event::Director::setDirectorUI8BL( uint8_t value )
{
   m_unionData.ui8lh.UI8BL = value;
}

void Core::Event::Director::setDirectorUI8BH( uint8_t value )
{
   m_unionData.ui8lh.UI8BH = value;
}

void Core::Event::Director::setDirectorUI8CL( uint8_t value )
{
   m_unionData.ui8lh.UI8CL = value;
}

void Core::Event::Director::setDirectorUI8CH( uint8_t value )
{
   m_unionData.ui8lh.UI8CH = value;
}

void Core::Event::Director::setDirectorUI8DL( uint8_t value )
{
   m_unionData.ui8lh.UI8DL = value;
}

void Core::Event::Director::setDirectorUI8DH( uint8_t value )
{
   m_unionData.ui8lh.UI8DH = value;
}

void Core::Event::Director::setDirectorUI8EL( uint8_t value )
{
   m_unionData.ui8lh.UI8EL = value;
}

void Core::Event::Director::setDirectorUI8EH( uint8_t value )
{
   m_unionData.ui8lh.UI8EH = value;
}

void Core::Event::Director::setDirectorUI8FL( uint8_t value )
{
   m_unionData.ui8lh.UI8FL = value;
}

void Core::Event::Director::setDirectorUI8FH( uint8_t value )
{
   m_unionData.ui8lh.UI8FH = value;
}

void Core::Event::Director::setDirectorUI8GL( uint8_t value )
{
   m_unionData.ui8lh.UI8GL = value;
}

void Core::Event::Director::setDirectorUI8GH( uint8_t value )
{
   m_unionData.ui8lh.UI8GH = value;
}

void Core::Event::Director::setDirectorUI8HL( uint8_t value )
{
   m_unionData.ui8lh.UI8HL = value;
}

void Core::Event::Director::setDirectorUI8HH( uint8_t value )
{
   m_unionData.ui8lh.UI8HH = value;
}

void Core::Event::Director::setDirectorUI8IL( uint8_t value )
{
   m_unionData.ui8lh.UI8IL = value;
}

void Core::Event::Director::setDirectorUI8IH( uint8_t value )
{
   m_unionData.ui8lh.UI8IH = value;
}

void Core::Event::Director::setDirectorUI8JL( uint8_t value )
{
   m_unionData.ui8lh.UI8JL = value;
}

void Core::Event::Director::setDirectorUI8JH( uint8_t value )
{
   m_unionData.ui8lh.UI8JH = value;
}

void Core::Event::Director::setDirectorBranch( uint8_t value )
{
   m_branch = value;
}

void Core::Event::Director::setDirectorSequence( uint8_t value )
{
   m_sequence = value;
}
