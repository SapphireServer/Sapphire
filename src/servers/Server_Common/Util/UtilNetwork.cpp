#include "UtilNetwork.h"
#include <string.h>

bool Core::Network::Util::bufferToPacketList( const std::vector< uint8_t > &buffer,
                                              Packets::FFXIVARR_PACKET_HEADER &ipcHeader,
                                              std::vector< Packets::FFXIVARR_PACKET_RAW > &packetList )
{
   memcpy( &ipcHeader, ( uint8_t* ) &buffer[0], sizeof( struct Packets::FFXIVARR_PACKET_HEADER ) );

   uint16_t offset = 0;
   for( std::size_t x = 0; x < ipcHeader.count; x++ )
   {
      Packets::FFXIVARR_PACKET_RAW packet;

      uint32_t headerSize = sizeof( struct Packets::FFXIVARR_PACKET_HEADER );
      uint32_t headerSegSize = sizeof( struct Packets::FFXIVARR_PACKET_SEGMENT_HEADER );
      memcpy( &packet.segHdr, ( uint8_t* ) &buffer[headerSize + offset], headerSegSize );

      std::vector<uint8_t> packetData;

      uint16_t startOff = sizeof( struct Packets::FFXIVARR_PACKET_HEADER ) + offset;

      for( std::size_t y = 0; y < packet.segHdr.size - sizeof( struct Packets::FFXIVARR_PACKET_SEGMENT_HEADER ); y++ )
      {
         packet.data.push_back( buffer.at( startOff + y + sizeof( struct Packets::FFXIVARR_PACKET_SEGMENT_HEADER ) ) );
      }

      offset += packet.segHdr.size;

      packetList.push_back( packet );

   }

   return true;
}
