#ifndef _GAMEPACKETPARSER_H
#define _GAMEPACKETPARSER_H
#include "CommonNetwork.h"

namespace Core
{
   namespace Network
   {
      namespace Packets
      {
         enum PacketParseResult
         {
            /// Dissected game packet successfully
            Success,

            /// Buffer is too short to dissect a message.
            Incomplete,
            
            /// Invalid data detected.
            Malformed
         };

         /// Read packet header from buffer with given offset.
         /// Buffer with given offset must be pointing to start of the new FFXIV packet.
         PacketParseResult getHeader(
            const std::vector< uint8_t > &buffer,
            const uint32_t offset,
            FFXIVARR_PACKET_HEADER &header
         );

         /// Read packet header from buffer with given offset.
         /// Buffer with given offset must be pointing to start of FFXIVARR_PACKET_SEGMENT_HEADER data.
         /// Keep in mind that this function does check for data validity. Call checkSegmentHeader() if that's needed.
         PacketParseResult getSegmentHeader(
            const std::vector< uint8_t > &buffer,
            const uint32_t offset,
            FFXIVARR_PACKET_SEGMENT_HEADER &header
         );

         /// Read packets from the buffer with given offset.
         /// Buffer with given offset must be pointing to end of FFXIVARR_PACKET_HEADER data.
         PacketParseResult getPackets(
            const std::vector< uint8_t > &buffer,
            const uint32_t offset,
            const FFXIVARR_PACKET_HEADER &header,
            std::vector< Packets::FFXIVARR_PACKET_RAW > &packets);
         
         /// Read single packet from the buffer with given offset.
         /// Buffer with an offset must be pointing to start of FFXIVARR_PACKET_SEGMENT_HEADER data.
         PacketParseResult getPacket(
            const std::vector< uint8_t > &buffer,
            const uint32_t offset,
            FFXIVARR_PACKET_RAW &packet
         );

         bool checkHeader(const FFXIVARR_PACKET_HEADER &header);
         bool checkSegmentHeader(const FFXIVARR_PACKET_SEGMENT_HEADER &header);

      }
   }
}


#endif