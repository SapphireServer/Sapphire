#ifndef _CORE_NETWORK_PACKETS_ZONE_CLIENT_IPC_H
#define _CORE_NETWORK_PACKETS_ZONE_CLIENT_IPC_H

#include <Common.h>
#include <Network/CommonNetwork.h>

namespace Core {
namespace Network {
namespace Packets {
namespace Client {

struct FFXIVIpcGmCommand1 : FFXIVIpcBasePacket< GMCommand1 >
{
   /* 0000 */ uint32_t commandId;
   /* 0004 */ uint32_t param1;
   /* 0008 */ uint32_t param2;
   /* 000C */ uint8_t unknown_C[0xC];
   /* 0018 */ uint32_t param3;
};

}
}
}
}

#endif //_CORE_NETWORK_PACKETS_ZONE_CLIENT_IPC_H
