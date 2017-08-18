#ifndef _UTILNETWORK_H
#define _UTILNETWORK_H

#include "src/servers/Server_Common/Network/CommonNetwork.h"

namespace Core {
namespace Network {
namespace Util {


   bool bufferToPacketList( const std::vector< uint8_t > &buffer,
                            Packets::FFXIVARR_PACKET_HEADER &ipcHeader,
                            std::vector< Packets::FFXIVARR_PACKET_RAW > &packetList );
}
}
}

#endif