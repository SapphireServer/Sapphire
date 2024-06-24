#include "CommonNetwork.h"
#include "GamePacketParser.h"
#include "Oodle.h"

#include <string.h>   // memcpy
#include <Logging/Logger.h>

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
                                                          std::vector< FFXIVARR_PACKET_RAW >& packets,
                                                          Network::Oodle* oodle)
{
  // sanity check: check there's enough bytes in the buffer
  auto bytesExpected = packetHeader.size - sizeof( struct FFXIVARR_PACKET_HEADER );
  if( buffer.size() - offset < bytesExpected )
    return Incomplete;

  std::vector< uint8_t > decompBuf;

  // check compression, do decompress if Oodle/Zlib
  if( packetHeader.compressionType == Oodle )
  {
    if( oodle == nullptr )
    {
      Logger::warn( "Oodle compression type was specified, but no Oodle decompressor was supplied for this connection." );
      return Malformed;
    }

    std::vector< uint8_t > inBuf;
    inBuf.assign( buffer.begin() + sizeof( struct FFXIVARR_PACKET_HEADER ), buffer.end() );

    std::vector< uint8_t > outBuf;
    outBuf.resize( packetHeader.oodleDecompressedSize );

    bool oodleSuccess = oodle->oodleDecode( inBuf, static_cast<uint32_t>(bytesExpected), outBuf, packetHeader.oodleDecompressedSize );

    if( !oodleSuccess )
    {
      Logger::warn( "Oodle decompression failed." );
      return Malformed;
    }

    bytesExpected = packetHeader.oodleDecompressedSize;

    decompBuf.assign( buffer.begin(), buffer.begin() + sizeof( struct FFXIVARR_PACKET_HEADER ) );
    decompBuf.insert( decompBuf.end(), outBuf.begin(), outBuf.end() );
  }

  else if( packetHeader.compressionType == Zlib )
  {
    // to do(?): Zlib decompression should go here,
    // but I don't think the client ever sends Zlib packets? So it may not be needed
  }

  else if( packetHeader.compressionType == NoCompression )
    decompBuf.assign( buffer.begin(), buffer.end() );

  else
  {
    Logger::warn( "Unknown packet compression type: {}", packetHeader.compressionType );
    return Malformed;
  }

  // Loop each message
  uint32_t count = 0;
  uint32_t bytesProcessed = 0;
  while( count < packetHeader.count )
  {
    FFXIVARR_PACKET_RAW rawPacket;

    // Copy ipc packet message
    const auto packetResult = getPacket( decompBuf, offset + bytesProcessed, rawPacket );
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
