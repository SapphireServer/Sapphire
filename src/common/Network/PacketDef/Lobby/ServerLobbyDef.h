#pragma once

#include <Common.h>
#include <Network/CommonNetwork.h>

namespace Sapphire::Network::Packets::LobbyPackets::Server
{

struct FFXIVIpcSyncReply : FFXIVIpcBasePacket< SyncReply >
{
  uint32_t clientTimeValue;
};

struct AccountInfo
{
  uint64_t accountId;
  uint8_t accountIndex;
  uint8_t accParam1;
  uint16_t accStauts;
  char accountName[64];
};

struct FFXIVIpcLoginReply : FFXIVIpcBasePacket< LoginReply >
{
  uint32_t requestNumber;
  uint32_t clientTimeValue;
  uint8_t endOfList : 1;
  uint8_t accountListIndex : 7;
  uint8_t activeAccountCount;
  uint8_t regionCode;
  uint8_t optionParam;
  uint32_t optionArg;
  AccountInfo accountArray[8];
};

struct CharacterInfo
{
  uint64_t playerId;
  uint64_t characterId;
  uint8_t chrIndex;
  uint8_t chrParam1;
  uint16_t chrStatus;
  uint32_t chrParam2;
  uint16_t worldId;
  char chrName[32];
  char worldSetName[32];
  char graphicData[1030];
};

struct FFXIVIpcServiceLoginReply : FFXIVIpcBasePacket< ServiceLoginReply >
{
  uint32_t requestNumber;
  uint32_t clientTimeValue;
  uint8_t endOfList : 1;
  uint8_t listIndex : 7;
  uint8_t count;
  uint16_t optionParam;
  uint32_t optionArg;
  uint64_t billParam1;
  uint64_t billParam2;
  ///
  uint64_t billParam1_;
  uint32_t billParam1__;
/// ADDED FOR 2.3 ----------
  uint8_t unknown6; // 0x80 in case of last packet
  uint8_t veteranRank;
  uint8_t unknown7;
  uint8_t padding1;
  uint32_t daysSubscribed;
  uint32_t remainingDays;
  uint32_t daysToNextRank;
/// ------------------------
  uint16_t maxCreateCharacter;
  uint16_t maxCharacterList;
  uint32_t entitledExpansion;
  uint32_t unknown8;
  CharacterInfo chrArray[2];
};

struct FFXIVIpcCharaMakeReply : FFXIVIpcBasePacket< CharaMakeReply >
{
  uint32_t requestNumber;
  uint32_t clientTimeValue;
  uint8_t endOfList : 1;
  uint8_t listIndex : 7;
  uint8_t count;
  uint16_t optionParam;
  uint32_t optionArg;
  CharacterInfo chrArray[2];
};

struct FFXIVIpcGameLoginReply : FFXIVIpcBasePacket< GameLoginReply >
{
  uint32_t requestNumber;
  uint32_t clientTimeValue;
  uint32_t ticketId;
  uint64_t characterId;
  uint8_t characterIndex;
  uint8_t operation;
  uint16_t worldId;
  char ticketData[64];
  uint16_t flag;
  uint16_t frontendPort;
  char frontendHost[32];
  char worldSetName[32];
};

struct FFXIVIpcUpdateRetainerSlotsReply : FFXIVIpcBasePacket< UpdateRetainerSlotsReply >
{
  uint32_t requestNumber;
  uint32_t clientTimeValue;
  uint16_t optionParam;
  uint16_t padding;
  uint32_t optionArg;
  uint16_t contractedNum;
  uint16_t activeCharacterNum;
  uint16_t totalSlotNum;
  uint16_t freeSlotNum;
  uint16_t totalRetainerNum;
  uint16_t activeRetainerNum;
};

struct worldInfo
{
  uint16_t worldId;
  uint16_t worldIndex;
  uint8_t worldParam1;
  uint8_t __padding1;
  uint8_t __padding2;
  uint8_t __padding3;
  uint32_t stat1;
  uint32_t stat2;
  uint32_t mode;
  char worldSetName[32];
  char displayName[32];
};

struct FFXIVIpcDistWorldInfo : FFXIVIpcBasePacket< DistWorldInfo >
{
  uint32_t requestNumber;
  uint32_t clientTimeValue;
  uint8_t endOfList : 1;
  uint16_t listIndex;
  uint16_t count;
  uint16_t optionParam;
  uint8_t __padding2;
  uint8_t __padding3;
  uint32_t optionArg;
  worldInfo worldArray[6];
};

struct FFXIVIpcXiCharacterInfo : FFXIVIpcBasePacket< XiCharacterInfo >
{
  uint32_t requestNumber;
  uint32_t clientTimeValue;
  uint8_t endOfList : 1;
  uint8_t listIndex : 7;
  uint8_t count;
  uint16_t optionParam;
  uint32_t optionArg;

  struct XiCharacterInfo
  {
    uint32_t ffxiId;
    uint8_t chrIndex;
    uint8_t worldParam1;
    uint16_t status;
    char charactername[32];
  } characterArray[12];
};

struct RetainerInfo
{
  uint64_t retainerId;
  uint64_t ownerId;
  uint8_t slotID;
  uint8_t param1;
  uint16_t retainerStatus;
  uint32_t param2;
  char name[32];
};

struct FFXIVIpcDistRetainerInfo : FFXIVIpcBasePacket< DistRetainerInfo >
{
  uint32_t requestNumber;
  uint32_t clientTimeValue;
  uint8_t endOfList : 1;
  uint8_t listIndex : 7;
  uint8_t count;
  uint16_t optionParam;
  uint32_t optionArg;
  uint16_t contractedNum;
  uint16_t activeCharacterNum;
  uint16_t totalSlotNum;
  uint16_t freeSlotNum;
  uint16_t totalRetainerNum;
  uint16_t activeRetainerNum;
  RetainerInfo retainerArray[9];
};

struct FFXIVIpcDebugNullRepl : FFXIVIpcBasePacket< DebugNullRepl >
{
  uint32_t dummyArgument;
};

struct FFXIVIpcDebugLoginRepl : FFXIVIpcBasePacket< DebugLoginRepl >
{
  uint32_t requestNumber;
  uint32_t ticketNumber;
  uint16_t flag;
  uint16_t frontendPort;
  char frontendHost[32];
  char worldSetName[32];
};

struct FFXIVIpcNackReply : FFXIVIpcBasePacket< NackReply >
{
  uint32_t requestNumber;
  uint32_t clientTimeValue;
  int32_t errorCode;
  int32_t errorStatus;
  int16_t errorMessageNo;
  int16_t messageSize;
  uint8_t message[512];
};

}

