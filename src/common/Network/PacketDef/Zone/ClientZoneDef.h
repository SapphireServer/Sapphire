#ifndef _CORE_NETWORK_PACKETS_ZONE_CLIENT_IPC_H
#define _CORE_NETWORK_PACKETS_ZONE_CLIENT_IPC_H

#include <Common.h>
#include <Network/CommonNetwork.h>

namespace Core {
namespace Network {
namespace Packets {
namespace Client {

struct FFXIVIpcGmCommand1 :
  FFXIVIpcBasePacket< GMCommand1 >
{
  /* 0000 */ uint32_t commandId;
  /* 0004 */ uint32_t param1;
  /* 0008 */ uint32_t param2;
  /* 000C */ uint8_t unknown_C[0xC];
  /* 0018 */ uint32_t param3;
};

struct FFXIVIpcGmCommand2 :
  FFXIVIpcBasePacket< GMCommand2 >
{
  /* 0000 */ uint32_t commandId;
  /* 0004 */ char unk_4[0x10];
  /* 0014 */ char param1[0x20];
};

struct FFXIVIpcClientTrigger :
  FFXIVIpcBasePacket< ClientTrigger >
{
  /* 0000 */ uint16_t commandId;
  /* 0002 */ uint8_t unk_2[2];
  /* 0004 */ uint32_t param11;
  /* 0008 */ uint32_t param12;
  /* 000C */ uint32_t param2;
  /* 0010 */ char unk_10[8];
  /* 0018 */ uint64_t param3;
};

struct FFXIVIpcSkillHandler :
  FFXIVIpcBasePacket< SkillHandler >
{
  /* 0000 */ char pad_0000[1];
  /* 0001 */ uint8_t type;
  /* 0002 */ char pad_0002[2];
  /* 0004 */ uint32_t actionId;
  /* 0008 */ uint32_t useCount;
  /* 000C */ char pad_000C[4];
  /* 0010 */ uint64_t targetId;
};

struct FFXIVIpcZoneLineHandler :
  FFXIVIpcBasePacket< ZoneLineHandler >
{
  /* 0000 */ uint32_t zoneLineId;
};

struct FFXIVIpcDiscoveryHandler :
  FFXIVIpcBasePacket< DiscoveryHandler >
{
  /* 0000 */ uint32_t positionRef;
};

struct FFXIVIpcEventHandlerReturn :
  FFXIVIpcBasePacket< ReturnEventHandler >
{
  /* 0000 */ uint32_t eventId;
  /* 0004 */ uint16_t scene;
  /* 0006 */ uint16_t param1;
  /* 0008 */ uint16_t param2;
  /* 000A */ char pad_000A[2];
  /* 000C */ uint16_t param3;
  /* 000E */ char pad_000E[2];
  /* 0010 */ uint16_t param4;
};

struct FFXIVIpcEnterTerritoryHandler :
  FFXIVIpcBasePacket< EnterTeriEventHandler >
{
  /* 0000 */ uint32_t eventId;
  /* 0004 */ uint16_t param1;
  /* 0006 */ uint16_t param2;
};

struct FFXIVIpcEventHandlerOutsideRange :
  FFXIVIpcBasePacket< OutOfRangeEventHandler >
{
  /* 0000 */ uint32_t param1;
  /* 0004 */ uint32_t eventId;
  /* 0008 */ Common::FFXIVARR_POSITION3 position;
};

struct FFXIVIpcEventHandlerWithinRange :
  FFXIVIpcBasePacket< WithinRangeEventHandler >
{
  /* 0000 */ uint32_t param1;
  /* 0004 */ uint32_t eventId;
  /* 0008 */ Common::FFXIVARR_POSITION3 position;
};

struct FFXIVIpcEventHandlerEmote :
  FFXIVIpcBasePacket< EmoteEventHandler >
{
  /* 0000 */ uint64_t actorId;
  /* 0008 */ uint32_t eventId;
  /* 000C */ uint16_t emoteId;
};

struct FFXIVIpcEventHandlerTalk :
  FFXIVIpcBasePacket< TalkEventHandler >
{
  /* 0000 */ uint64_t actorId;
  /* 0008 */ uint32_t eventId;
};

struct FFXIVIpcPingHandler :
  FFXIVIpcBasePacket< PingHandler >
{
  /* 0000 */ uint32_t timestamp; // maybe lol..
};

struct FFXIVIpcSetSearchInfo :
  FFXIVIpcBasePacket< SetSearchInfoHandler >
{
  union
  {
    /* 0000 */ uint64_t status;
    struct
    {
      /* 0000 */ uint32_t status1;
      /* 0004 */ uint32_t status2;
    };
  };

  /* 0008 */ char pad_0008[9];
  /* 0011 */ Common::ClientLanguage language;
  /* 0012 */ char searchComment[193];
};

struct FFXIVIpcTellHandler :
  FFXIVIpcBasePacket< TellReq >
{
  /* 0000 */ char pad_0000[4];
  /* 0004 */ char targetPCName[32];
  /* 0024 */ char message[1012];
};

struct FFXIVIpcChatHandler :
  FFXIVIpcBasePacket< ChatHandler >
{
  /* 0000 */ char pad_0000[4];
  /* 0004 */ uint32_t sourceId;
  /* 0008 */ char pad_0008[16];
  /* 0018 */ Common::ChatType chatType;
  /* 001A */ char message[1012];
};

struct FFXIVIpcLinkshellEventHandler :
  FFXIVIpcBasePacket< LinkshellEventHandler >
{
  /* 0000 */ uint32_t eventId;
  /* 0004 */ uint16_t scene;
  /* 0006 */ char pad_0006[1];
  /* 0007 */ char lsName[21];
};

struct FFXIVIpcInventoryModifyHandler :
  FFXIVIpcBasePacket< InventoryModifyHandler >
{
  /* 0000 */ uint32_t seq;
  /* 0004 */ Common::InventoryOperation action;
  /* 0005 */ char pad_0005[7];
  /* 000C */ uint16_t fromContainer;
  /* 000E */ char pad_000E[2];
  /* 0010 */ uint8_t fromSlot;
  /* 0011 */ char pad_0011[15];
  /* 0020 */ uint16_t toContainer;
  /* 0022 */ char pad_0022[2];
  /* 0024 */ uint8_t toSlot;
  /* 0025 */ uint8_t pad_0025[3];
  /* 0028 */ uint32_t splitCount;
};

}
}
}
}

#endif //_CORE_NETWORK_PACKETS_ZONE_CLIENT_IPC_H
