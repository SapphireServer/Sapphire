#include "CommonNetwork.h"
#include "GamePacketParser.h"

#include <string.h>   // memcpy

using namespace Sapphire;
using namespace Sapphire::Network::Packets;

PacketParseResult Network::Packets::getHeader( const std::vector< uint8_t >& buffer,
                                                         const uint32_t offset,
                                                         FFXIVARR_PACKET_HEADER& header )
{
  const auto headerSize = sizeof( FFXIVARR_PACKET_HEADER );

  // Check if we have enough bytes in the buffer.
  auto remainingBytes = buffer.size() - offset;
  if( remainingBytes < headerSize )
    return Incomplete;

  // Copy packet header.
  memcpy( &header, buffer.data() + offset, headerSize );

  if( !checkHeader( header ) )
    return Malformed;

  return Success;
}

PacketParseResult Network::Packets::getSegmentHeader( const std::vector< uint8_t >& buffer,
                                                                const uint32_t offset,
                                                                FFXIVARR_PACKET_SEGMENT_HEADER& header )
{
  const auto headerSize = sizeof( FFXIVARR_PACKET_SEGMENT_HEADER );

  // Check if we have enough bytes in the buffer.
  auto remainingBytes = buffer.size() - offset;
  if( remainingBytes < headerSize )
    return Incomplete;

  // Copy segment header
  memcpy( &header, buffer.data() + offset, headerSize );

  return Success;
}

PacketParseResult Network::Packets::getPackets( const std::vector< uint8_t >& buffer,
                                                          const uint32_t offset,
                                                          const FFXIVARR_PACKET_HEADER& packetHeader,
                                                          std::vector< FFXIVARR_PACKET_RAW >& packets )
{
  // sanity check: check there's enough bytes in the buffer
  const auto bytesExpected = packetHeader.size - sizeof( struct FFXIVARR_PACKET_HEADER );
  if( buffer.size() - offset < bytesExpected )
    return Incomplete;

  // Loop each message
  uint32_t count = 0;
  uint32_t bytesProcessed = 0;
  while( count < packetHeader.count )
  {
    FFXIVARR_PACKET_RAW rawPacket;

    // Copy ipc packet message
    const auto packetResult = getPacket( buffer, offset + bytesProcessed, rawPacket );
    if( packetResult != Success )
      return packetResult;

    // NOTE: isn't rawPacket is allocated on stack?
    // why is okay to do this?
    packets.push_back( rawPacket );

    // Add message size and count
    bytesProcessed += rawPacket.segHdr.size;
    count += 1;
  }

  // sanity check: check if we processed all bytes.
  // this check can fail if size of messages don't add up to size reported from packet header.
  if( bytesExpected != bytesProcessed )
    return Malformed;

  return Success;
}

PacketParseResult Network::Packets::getPacket( const std::vector< uint8_t >& buffer, const uint32_t offset,
                                                         FFXIVARR_PACKET_RAW& packet )
{
  // Copy segment header
  const auto headerResult = getSegmentHeader( buffer, offset, packet.segHdr );
  if( headerResult != Success )
    return headerResult;

  // Check header sanity and it's size
  if( !checkSegmentHeader( packet.segHdr ) )
    return Malformed;

  const auto dataOffset = offset + sizeof( struct FFXIVARR_PACKET_SEGMENT_HEADER );
  const auto dataSize = packet.segHdr.size;

  // Allocate data buffer and copy
  packet.data.resize( dataSize );
  memcpy( packet.data.data(), buffer.data() + dataOffset, dataSize );

  return Success;
}

bool Network::Packets::checkHeader( const FFXIVARR_PACKET_HEADER& header )
{
  // Max size of the packet is capped at 1MB for now.
  if( header.size > 1 * 1024 * 1024 )
    return false;

  // Max number of message is capped at 255 for now.
  if( header.count > 255 )
    return false;

  return true;
}

bool Network::Packets::checkSegmentHeader( const FFXIVARR_PACKET_SEGMENT_HEADER& header )
{
  // Max size of individual message is capped at 256KB for now.
  if( header.size > 256 * 1024 )
    return false;

  return true;
}
