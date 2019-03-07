#ifndef _CORE_NETWORK_PACKETS_ZONE_CLIENT_IPC_H
#define _CORE_NETWORK_PACKETS_ZONE_CLIENT_IPC_H

#include <Common.h>
#include <Network/CommonNetwork.h>

namespace Sapphire {
namespace Network {
namespace Packets {
namespace Client {

struct FFXIVIpcGmCommand1 :
  FFXIVIpcBasePacket< GMCommand1 >
{
  /* 0000 */ uint32_t commandId;
  /* 0004 */ uint32_t param1;
  /* 0008 */ uint32_t param2;
  /* 000C */ uint32_t param3;
  /* 0010 */ uint32_t param4;
  /* 0014 */ uint32_t unknown1;
  /* 0018 */ uint32_t target;
};

struct FFXIVIpcGmCommand2 :
  FFXIVIpcBasePacket< GMCommand2 >
{
  /* 0000 */ uint32_t commandId;
  /* 0004 */ uint32_t param1;
  /* 0008 */ uint32_t param2;
  /* 000C */ uint32_t param3;
  /* 0010 */ uint32_t param4;
  /* 0014 */ uint16_t worldId;
  /* 0016 */ char target[0x20];
  /* 0036 */ uint16_t unknown1;
};

struct FFXIVIpcClientTrigger :
  FFXIVIpcBasePacket< ClientTrigger >
{
  /* 0000 */ uint16_t commandId;
  /* 0002 */ uint8_t unk_2[2];
  /* 0004 */ uint32_t param11;
  /* 0008 */ uint32_t param12;
  /* 000C */ uint32_t param2;
  /* 0010 */ uint32_t param4; // todo: really?
  /* 0014 */ uint32_t param5;
  /* 0018 */ uint64_t param3;
};

struct FFXIVIpcUpdatePosition :
  FFXIVIpcBasePacket< UpdatePositionHandler >
{
  /* 0000 */ float rotation;
  /* 0004 */ uint8_t unk_1[ 3 ];
  /* 0007 */ uint8_t headPosition;
  /* 0008 */ uint8_t animationType;
  /* 0009 */ uint8_t animationState;
  /* 000A */ uint8_t clientAnimationType;
  /* 000B */ uint8_t unk_2;
  /* 000C */ Common::FFXIVARR_POSITION3 position;
};

struct FFXIVIpcSkillHandler :
  FFXIVIpcBasePacket< SkillHandler >
{
  /* 0000 */ uint8_t pad_0000;
  /* 0001 */ uint8_t type;
  /* 0002 */ uint8_t pad_0002[2];
  /* 0004 */ uint32_t actionId;
  /* 0008 */ uint16_t sequence;
  /* 000A */ uint8_t pad_000C[6];
  /* 0010 */ uint64_t targetId;
  /* 0018 */ uint16_t itemSourceSlot;
  /* 001A */ uint16_t itemSourceContainer;
  /* 001C */ uint32_t unknown;
};

struct FFXIVIpcAoESkillHandler :
  FFXIVIpcBasePacket< AoESkillHandler >
{
  /* 0000 */ uint8_t pad_0000;
  /* 0001 */ uint8_t type;
  /* 0002 */ uint8_t pad_0002[2];
  /* 0004 */ uint32_t actionId;
  /* 0008 */ uint16_t sequence;
  /* 000A */ uint8_t pad_000C[6];
  /* 0010 */ Common::FFXIVARR_POSITION3 pos;
  /* 001C */ uint32_t unknown; // could almost be rotation + 16 bits more padding?
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
  /* 000A */ uint8_t pad_000A[2];
  /* 000C */ uint16_t param3;
  /* 000E */ uint8_t pad_000E[2];
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

  /* 0008 */ uint8_t pad_0008[9];
  /* 0011 */ Common::ClientLanguage language;
  /* 0012 */ char searchComment[193];
};

struct FFXIVIpcTellHandler : FFXIVIpcBasePacket< TellReq >
{
  uint64_t contentId;
  uint16_t worldId;
  uint16_t u0A;
  uint32_t u0C;
  uint16_t worldId1;
  uint8_t preName;
  /* 0004 */ char targetPCName[32];
  /* 0024 */ char message[1029];
};

struct FFXIVIpcChatHandler :
  FFXIVIpcBasePacket< ChatHandler >
{
  /* 0000 */ uint8_t pad_0000[4];
  /* 0004 */ uint32_t sourceId;
  /* 0008 */ uint8_t pad_0008[16];
  /* 0018 */ Common::ChatType chatType;
  /* 001A */ char message[1012];
};

struct FFXIVIpcShopEventHandler :
  FFXIVIpcBasePacket< ShopEventHandler >
{
  /* 0000 */ uint32_t eventId;
  /* 0004 */ uint32_t param;
};

struct FFXIVIpcLinkshellEventHandler :
  FFXIVIpcBasePacket< LinkshellEventHandler >
{
  /* 0000 */ uint32_t eventId;
  /* 0004 */ uint16_t scene;
  /* 0006 */ uint8_t pad_0006[1];
  /* 0007 */ char lsName[21];
};

struct FFXIVIpcInventoryModifyHandler :
  FFXIVIpcBasePacket< InventoryModifyHandler >
{
  /* 0000 */ uint32_t seq;
  /* 0004 */ Common::InventoryOperation action;
  /* 0005 */ uint8_t pad_0005[7];
  /* 000C */ uint16_t fromContainer;
  /* 000E */ uint8_t pad_000E[2];
  /* 0010 */ uint8_t fromSlot;
  /* 0011 */ uint8_t pad_0011[15];
  /* 0020 */ uint16_t toContainer;
  /* 0022 */ uint8_t pad_0022[2];
  /* 0024 */ uint8_t toSlot;
  /* 0025 */ uint8_t pad_0025[3];
  /* 0028 */ uint32_t splitCount;
};

struct FFXIVIpcRenameLandHandler :
  FFXIVIpcBasePacket< LandRenameHandler >
{
  /* 0000 */ Common::LandIdent ident;
  /* 0008 */ char houseName[20];
  /* 0028 */ uint32_t padding;
};

struct FFXIVIpcHousingUpdateHouseGreeting :
  FFXIVIpcBasePacket< HousingUpdateHouseGreeting >
{
  /* 0000 */ Common::LandIdent ident;
  /* 0008 */ char greeting[200];
};

struct FFXIVIpcBuildPresetHandler :
  FFXIVIpcBasePacket< BuildPresetHandler >
{
  /* 0000 */ uint32_t itemId;
  /* 0004 */ uint8_t plotNum;
  /* 0005 */ char stateString[27];
};

struct FFXIVIpcSetSharedEstateSettings :
  FFXIVIpcBasePacket< SetSharedEstateSettings >
{
  /* 0000 */ uint64_t char1ContentId;
  /* 0008 */ uint64_t char2ContentId;
  /* 0010 */ uint64_t char3ContentId;
  /* 0018 */ uint8_t char1Permissions;
  /* 0019 */ uint8_t padding1[0x7];
  /* 0020 */ uint8_t char2Permissions;
  /* 0021 */ uint8_t padding2[0x7];
  /* 0028 */ uint8_t char3Permissions;
  /* 0029 */ uint8_t padding3[0x7];
};

struct FFXIVIpcMarketBoardRequestItemListings :
  FFXIVIpcBasePacket< MarketBoardRequestItemListings >
{
  /* 0000 */ uint16_t padding1;
  /* 0002 */ uint16_t itemCatalogId;
  /* 0004 */ uint32_t padding2;
};

struct FFXIVIpcReqPlaceHousingItem :
  FFXIVIpcBasePacket< ReqPlaceHousingItem >
{
  /* 0000 */ uint16_t landId; // 0 when plot 0 or inside an estate
  /* 0002 */ uint16_t unknown1;
  /* 0004 */ uint32_t unknown2;
  /* 0008 */ uint16_t sourceInvContainerId;
  /* 000A */ uint16_t sourceInvSlotId;

  /* 000C */ Common::FFXIVARR_POSITION3 position;
  /* 0018 */ float rotation;

  /* 001C */ uint32_t shouldPlaceItem; // 1 if placing an item, 0 if placing in store
  /* 0020 */ uint32_t unknown4[2]; // always 0 it looks like
};

struct FFXIVIpcHousingUpdateObjectPosition :
  FFXIVIpcBasePacket< HousingUpdateObjectPosition >
{
  /* 0000 */ Common::LandIdent ident;
  /* 0008 */ uint16_t slot;
  /* 000A */ uint16_t unk;

  /* 000C */ Common::FFXIVARR_POSITION3 pos;
  /* 0018 */ float rotation;

  /* 001C */ uint32_t padding;
};

struct FFXIVIpcMarketBoardSearch :
  FFXIVIpcBasePacket< MarketBoardSearch >
{
  /* 0000 */ uint32_t startIdx;
  /* 0004 */ uint16_t requestId;
  /* 0006 */ uint8_t itemSearchCategory;
  /* 0007 */ uint8_t shouldCheckClassJobId; // wat? seems only 1 there at least...
  /* 0008 */ uint8_t maxEquipLevel;
  /* 0009 */ uint8_t classJobId;
  /* 000A */ char searchStr[40];
  /* 0032 */ uint16_t unk4[43];
};

struct FFXIVIpcMarketBoardRequestItemListingInfo :
  FFXIVIpcBasePacket< MarketBoardRequestItemListingInfo >
{
  /* 0000 */ uint32_t catalogId;
  /* 0000 */ uint32_t requestId;
};

}
}
}
}

#endif //_CORE_NETWORK_PACKETS_ZONE_CLIENT_IPC_H
