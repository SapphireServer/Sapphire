#include "LobbyPacketContainer.h"
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Crypt/blowfish.h>
#include <Common.h>

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;

Sapphire::Network::Packets::LobbyPacketContainer::LobbyPacketContainer( uint8_t* encKey )
{
  memset( &m_header, 0, sizeof( Sapphire::Network::Packets::FFXIVARR_PACKET_HEADER ) );
  m_header.size = sizeof( Sapphire::Network::Packets::FFXIVARR_PACKET_HEADER );

  m_encKey = encKey;

  memset( m_dataBuf, 0, 0x1570 );
}

Sapphire::Network::Packets::LobbyPacketContainer::~LobbyPacketContainer()
{
  m_entryList.clear();
}

void Sapphire::Network::Packets::LobbyPacketContainer::addPacket( FFXIVPacketBasePtr pEntry )
{
  memcpy( m_dataBuf + m_header.size, &pEntry->getData()[ 0 ], pEntry->getSize() );

  // encryption key is set, we want to encrypt this packet
  if( m_encKey != nullptr )
  {
    BlowFish blowfish;
    blowfish.initialize( m_encKey, 0x10 );
    blowfish.Encode( m_dataBuf + m_header.size + 0x10, m_dataBuf + m_header.size + 0x10, pEntry->getSize() - 0x10 );
  }

  m_header.size += pEntry->getSize();
  m_header.count++;
}

uint16_t Sapphire::Network::Packets::LobbyPacketContainer::getSize() const
{
  return m_header.size;
}

uint8_t* Sapphire::Network::Packets::LobbyPacketContainer::getRawData( bool addstuff )
{
  if( addstuff )
  {
    m_header.unknown_0 = 0xff41a05252;
    m_header.timestamp = Sapphire::Util::getTimeMs();
  }
  memcpy( m_dataBuf, &m_header, sizeof( Sapphire::Network::Packets::FFXIVARR_PACKET_HEADER ) );
  return m_dataBuf;
}
