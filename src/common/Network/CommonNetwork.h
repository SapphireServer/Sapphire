#ifndef _CORE_NETWORK_PACKETS_COMMON_H
#define _CORE_NETWORK_PACKETS_COMMON_H

#include <iostream>
#include <vector>
#include "PacketDef/Ipcs.h"

using namespace std;

namespace Core {
namespace Network {
namespace Packets {

/**
* Anticipated usage:
* ==================
* Set up a stream buffer to collect the bytes to be transmitted as a packet.
* Now, you can do the following (given you have the structs filled out already).
*
* FFXIVARR_PACKET_HEADER pkt_hdr = { . . . };
* FFXIVARR_PACKET_SEGMENT_HEADER pkt_seg_hdr[n] = { . . . };
*
* std::stringstream buf;
* buf << pkt_hdr;
* for( int i = 0; i < n; i++ )
* {
*     buf << pkt_seg_hdr[i];
*     buf << {pkt_seg_data[i]};
* }
*
* The reverse can be done parsing a packet. Remember to validate the packet
* type before parsing the headers.
*
* Compression and Encryption:
* ===========================
* By using std::iostream's, you can support stream filters. Simply create a
* stream that performs the compression or encryption, and use that stream to
* read and write.
*/

/**
* Structure representing the common header for all FFXIVARR packets.
*
* 0               4               8              12      14      16
* +-------------------------------+---------------+-------+-------+
* | unknown_0                     | unknown_8                     |
* +-------------------------------+---------------+-------+-------+
* | timestamp                     | size          | cType | count |
* +---+---+-------+---------------+---------------+-------+-------+
* | ? |CMP|   ?   | ?             |
* +---+---+-------+---------------+
* (followed by /count/ FFXIVARR_PACKET_SEGMENTs)
*/
struct FFXIVARR_PACKET_HEADER
{
   /** Unknown data, no actual use has been determined */
   uint64_t unknown_0;
   uint64_t unknown_8;
   /** Represents the number of milliseconds since epoch that the packet was sent. */
   uint64_t timestamp;
   /** The size of the packet header and its payload */
   uint32_t size;
   /** The type of this connection - 1 zone, 2 chat*/
   uint16_t connectionType;
   /** The number of packet segments that follow. */
   uint16_t count;
   uint8_t unknown_20;
   /** Indicates if the data segments of this packet are compressed. */
   uint8_t isCompressed;
   uint32_t unknown_24;
};

inline ostream& operator << ( ostream& os, const FFXIVARR_PACKET_HEADER& hdr )
{
   return os.write( reinterpret_cast< const char* >( &hdr ), sizeof hdr );
}

inline istream& operator >> ( istream& is, FFXIVARR_PACKET_HEADER& hdr )
{
   return is.read( reinterpret_cast< char* >( &hdr ), sizeof hdr );
}

/**
* Structure representing the header portion of a packet segment.
*
* NOTE: If the main packet header indicated the packet is compressed, this
* header will be compressed as well! The header will NOT ever be encrypted.
*
* 0               4               8              12              16
* +---------------+---------------+---------------+-------+-------+
* | size          | source_actor  | target_actor  | type  |  pad  |
* +---------------+---------------+---------------+-------+-------+
* |                                                               |
* :          type-specific data of length, size, follows          :
* |          (NOTE: Some segments MAY be encrypted)               |
* +---------------------------------------------------------------+
*/
struct FFXIVARR_PACKET_SEGMENT_HEADER
{
   /** The size of the segment header and its data. */
   uint32_t size;
   /** The session ID this segment describes. */
   uint32_t source_actor;
   /** The session ID this packet is being delivered to. */
   uint32_t target_actor;
   /** The segment type. (1, 2, 3, 7, 8, 9, 10) */
   uint16_t type;
   uint16_t padding;
};

inline ostream& operator << ( ostream& os, const FFXIVARR_PACKET_SEGMENT_HEADER& hdr )
{
   return os.write( reinterpret_cast< const char* >( &hdr ), sizeof hdr );
}

inline istream& operator >> ( istream& is, FFXIVARR_PACKET_SEGMENT_HEADER& hdr )
{
   return is.read( reinterpret_cast< char* >( &hdr ), sizeof hdr );
}

template < int T > struct FFXIVIpcBasePacket
{
   /** Creates a constant representing the IPC type */
   enum { _ServerIpcType = T };
};

struct FFXIVARR_PACKET_RAW
{
   FFXIVARR_PACKET_SEGMENT_HEADER segHdr;
   std::vector< uint8_t > data;
};

/**
* Structural representation of the common header for IPC packet segments.
* NOTE: This is packet segment type 3.
*
* 0               4      6          8              12              16
* +-------+-------+------+----------+---------------+---------------+
* | 14 00 | type  |  pad  | serverId |   timestamp   |      pad1    |
* +-------+-------+------+----------+---------------+---------------+
* |                                                                 |
* :                             data                                :
* |                                                                 |
* +-----------------------------------------------------------------+
*/
struct FFXIVARR_IPC_HEADER
{
   uint16_t reserved;
   uint16_t type;
   uint16_t padding;
   uint16_t serverId;
   uint32_t timestamp;
   uint32_t padding1;
};

inline ostream& operator << ( ostream& os, const FFXIVARR_IPC_HEADER& hdr )
{
   return os.write( reinterpret_cast< const char* >( &hdr ), sizeof hdr );
}

inline istream& operator >> ( istream& is, FFXIVARR_IPC_HEADER& hdr )
{
   return is.read( reinterpret_cast< char* >( &hdr ), sizeof hdr );
}

} /* Packets */
} /* Network */
} /* Core */

#endif /*_CORE_NETWORK_PACKETS_COMMON_H*/
