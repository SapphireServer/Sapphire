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

struct FFXIVIpcGmCommand2 : FFXIVIpcBasePacket< GMCommand2 >
{
   /* 0000 */ uint32_t commandId;
   /* 0004 */ char unk_4[0x10];
   /* 0014 */ char param1[0x20];
};

struct FFXIVIpcClientTrigger : FFXIVIpcBasePacket< ClientTrigger >
{
   /* 0000 */ uint16_t commandId;
   /* 0002 */ char unk_2[2];
   /* 0004 */ uint64_t param1;
   /* 000C */ uint32_t param2;
   /* 0010 */ char unk_10[8];
   /* 0018 */ uint64_t param3;
};

struct FFXIVIpcSkillHandler : FFXIVIpcBasePacket< SkillHandler >
{
   /* 0000 */ char pad_0000[1];
   /* 0001 */ uint8_t type;
   /* 0002 */ char pad_0002[2];
   /* 0004 */ uint32_t actionId;
   /* 0008 */ uint32_t useCount;
   /* 000C */ char pad_000C[4];
   /* 0010 */ uint64_t targetId;
};

}
}
}
}

#endif //_CORE_NETWORK_PACKETS_ZONE_CLIENT_IPC_H
