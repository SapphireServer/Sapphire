#include "PacketContainer.h"
#include "Util/Util.h"
#include "Common.h"
#include "Forwards.h"
#include "GamePacketParser.h"

#include <chrono>
#include <string.h>
#include <memory>

using namespace Sapphire;

Network::Packets::PacketContainer::PacketContainer( uint32_t segmentTargetOverride ) :
  m_segmentTargetOverride( segmentTargetOverride )
{
  memset( &m_ipcHdr, 0, sizeof( FFXIVARR_PACKET_HEADER ) );
  m_ipcHdr.size = sizeof( FFXIVARR_PACKET_HEADER );
  m_ipcHdr.count = 0;
}

Network::Packets::PacketContainer::~PacketContainer()
{
  m_entryList.clear();
}

void Network::Packets::PacketContainer::addPacket( Network::Packets::FFXIVPacketBasePtr entry )
{
  m_entryList.push_back( entry );

  m_ipcHdr.size += static_cast< uint32_t >( entry->getSize() );
  m_ipcHdr.count++;
}

void Network::Packets::PacketContainer::fillSendBuffer( std::vector< uint8_t >& sendBuffer, Network::Oodle* oodle )
{
  std::vector< uint8_t > tempBuffer( m_ipcHdr.size );
  memset( &tempBuffer[ 0 ], 0, m_ipcHdr.size );

  auto it = m_entryList.begin();
  std::size_t offset = 0;

  if( m_entryList.size() > 1 )
    offset = 0;

  for( ; it != m_entryList.end(); ++it )
  {
    auto pPacket = ( *it );

    if( m_segmentTargetOverride != 0 && pPacket->getSegmentType() == SEGMENTTYPE_IPC )
    {
      pPacket->setTargetActor( m_segmentTargetOverride );
    }

    auto data = pPacket->getData();
    memcpy( &tempBuffer[ 0 ] + sizeof( FFXIVARR_PACKET_HEADER ) + offset, &data[ 0 ], pPacket->getSize() );
    offset += pPacket->getSize();
  }

  // oodle is always nullptr, but i guess this is here if we ever want to encode like retail
  if ( oodle != nullptr )
  {
    std::vector< uint8_t > inBuf;
    inBuf.assign( tempBuffer.begin() + sizeof( struct FFXIVARR_PACKET_HEADER ), tempBuffer.end() );

    std::vector< uint8_t > outBuf;
    outBuf.resize( m_ipcHdr.size );

    auto compLen = oodle->oodleEncode(inBuf, (uint32_t)inBuf.size(), outBuf);

    // Check if we compressed at all
    if (compLen != m_ipcHdr.size) {
      tempBuffer.resize(compLen);
      memcpy(&inBuf[0], &outBuf[0], compLen);
      m_ipcHdr.oodleDecompressedSize = m_ipcHdr.size;
      m_ipcHdr.size = (uint32_t)compLen;
      m_ipcHdr.compressionType = static_cast< uint8_t >(Packets::CompressionType::Oodle);
    }
  }

  using namespace std::chrono;
  auto ms = duration_cast< milliseconds >( system_clock::now().time_since_epoch() );
  uint64_t tick = ms.count();
  m_ipcHdr.unknown_0 = 0xE2465DFF41a05252;
  m_ipcHdr.unknown_8 = 0x75C4997B4D642A7F;
  m_ipcHdr.timestamp = tick;
  m_ipcHdr.unknown_20 = 1;

  memcpy( &tempBuffer[ 0 ], &m_ipcHdr, sizeof( FFXIVARR_PACKET_HEADER ) );

  sendBuffer.assign( &tempBuffer[ 0 ], &tempBuffer[ 0 ] + m_ipcHdr.size );
}

std::string Network::Packets::PacketContainer::toString()
{
  std::vector< uint8_t > tmpBuffer;

  fillSendBuffer( tmpBuffer, nullptr );

  std::string str = "\n";
  for( uint32_t i = 0; i < m_ipcHdr.size; i++ )
  {
    str += Common::Util::intToHexString( static_cast< int32_t >( tmpBuffer[ i ] & 0xFF ) ) + " ";

    if( ( i + 1 ) % 16 == 0 )
      str += "\n";
  }
  str += "\n";

  return str;
}

