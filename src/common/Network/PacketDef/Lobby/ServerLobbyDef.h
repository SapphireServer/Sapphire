#ifndef _CORE_NETWORK_PACKETS_LOBBY_SERVER_IPC_H
#define _CORE_NETWORK_PACKETS_LOBBY_SERVER_IPC_H

#include <Common.h>
#include <Network/CommonNetwork.h>

namespace Sapphire::Network::Packets::Server {

struct FFXIVIpcRetainerList :
  FFXIVIpcBasePacket< LobbyRetainerList >
{
  uint8_t padding[0x210];
};

/**
*/
struct FFXIVIpcServiceIdInfo :
  FFXIVIpcBasePacket< LobbyServiceAccountList >
{
  uint64_t seq;
  uint8_t padding;
  uint8_t numServiceAccounts;
  uint8_t u1;
  uint8_t u2;
  uint32_t padding1;

  struct
  {
    uint32_t id;
    uint32_t unknown;
    uint32_t index;
    char name[0x44];
  } serviceAccount[8];
};


struct FFXIVIpcServerList :
  FFXIVIpcBasePacket< LobbyServerList >
{
  uint64_t seq;
  uint16_t final;
  uint16_t offset;
  uint32_t numServers;
  uint32_t padding;
  uint32_t padding1;

  struct
  {
    uint16_t id;
    uint16_t index;
    uint32_t flags;      // 0x02 = World not accepting new characters
    uint32_t padding1;
    uint32_t icon;       // 2 = bonus XP star
    uint32_t padding2;
    char name[0x40];
  } server[6];
};

struct FFXIVIpcCharList : FFXIVIpcBasePacket< LobbyCharList >
{
  uint64_t seq;
  uint8_t counter; // current packet count * 4, count * 4 +1 on last packet.
  uint8_t numInPacket; // always 2??
  uint16_t padding;
  uint8_t unknown1;
  uint8_t unknown2;
  uint8_t unknown3;
  uint8_t unknown4; // 0x80 in case of last packet
  uint32_t unknown5[7];
  uint8_t unknown6; // 0x80 in case of last packet
  uint8_t veteranRank;
  uint8_t unknown7;
  uint8_t padding1;
  uint32_t daysSubscribed;
  uint32_t remainingDays;
  uint32_t daysToNextRank;
  uint16_t maxCharOnWorld;
  uint16_t unknown8;
  uint32_t entitledExpansion;
  uint32_t padding2;
  uint32_t padding3;
  uint32_t padding4;

  struct CharaDetails
  {
    uint32_t uniqueId;
    uint32_t padding;
    uint64_t contentId;
    uint32_t index;
    uint32_t padding2;
    uint16_t serverId;
    uint16_t serverId1;
    uint8_t unknown[9];
    char nameChara[32];
    char nameServer[32];
    char nameServer1[32];
    char charDetailJson[1051];
  } charaDetails[2];

};

struct FFXIVIpcEnterWorld : FFXIVIpcBasePacket< LobbyEnterWorld >
{
  uint64_t seq;
  uint32_t charId;
  uint32_t padding;
  uint64_t contentId;
  uint32_t padding2;
  char sid[66];
  uint16_t port;
  char host[48];
  uint64_t padding3;
  uint64_t padding4;
};

struct FFXIVIpcCharCreate : FFXIVIpcBasePacket< LobbyCharCreate >
{
  uint64_t seq;
  uint8_t unknown;
  uint8_t unknown_2;
  uint8_t type;
  uint8_t padding;
  uint32_t unknown_3;
  uint32_t unknown_4;
  uint32_t unknown_5;
  uint64_t unknown_6;
  uint64_t unknown_61;
  uint64_t unknown_62;
  uint64_t unknown_63;
  uint64_t content_id;
  uint16_t unknown_7;
  uint16_t unknown_8;
  uint32_t unknown_9;
  uint16_t unknown_10;
  uint8_t unknown_11[11];
  char name[32];
  char world[32];
  char world2[32];
  uint8_t unknown_12[0x953];
};

struct FFXIVIpcLobbyError : FFXIVIpcBasePacket< LobbyError >
{
  uint64_t seq;
  uint32_t error_id;
  uint32_t param;
  uint16_t message_id;
  char message[516];
};

}

#endif
