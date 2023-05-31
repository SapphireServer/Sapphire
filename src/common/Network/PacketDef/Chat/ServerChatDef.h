#ifndef _CORE_NETWORK_PACKETS_CHAT_SERVER_IPC_H
#define _CORE_NETWORK_PACKETS_CHAT_SERVER_IPC_H

#include <Common.h>
#include <Network/CommonNetwork.h>

namespace Sapphire::Network::Packets::Server
{

/**
* Structural representation of the packet sent by the server as response
* to a tell request
*/
struct FFXIVIpcTell : FFXIVIpcBasePacket< Tell >
{
  uint64_t contentId;
  uint16_t worldId;
  uint8_t flags;
  char receipientName[32];
  char msg[1029];
};

struct FFXIVIpcChannelChat : FFXIVIpcBasePacket< ChannelChat >
{
  uint64_t channelId;
  uint64_t contentId;
  uint32_t charaId;
  uint8_t type;
  uint8_t unknown1;
  uint8_t unknown2;
  char name[32];
  char message[1024];
  uint8_t padding;
};

/**
* Structural representation of the packet sent by the server as response
* to a failed tell because of unavailable target player
*/
struct FFXIVIpcTellErrNotFound : FFXIVIpcBasePacket< TellErrNotFound >
{
  char receipientName[32];
};

struct FFXIVIpcFreeCompanyEvent : FFXIVIpcBasePacket< FreeCompanyEvent >
{
  uint16_t unknown;
  uint16_t unknown1;
  uint16_t unknown2;
  uint16_t unknown3;
  uint16_t unknown4;
  char padding[6];
  uint8_t eventID;
  /*
  * 0x0F Login
  * 0x10 Logout
  */
  uint8_t padding1;
  char padding2[6];
  uint16_t unknown5;
  char parameter[46];
  /**
  * eventID  | parameter usage
  * 0x0F       FC name
  * 0x10       FC name
  */
  char parameter1[32];
  /**
  * eventID  | parameter1 usage
  * 0x0F       Character name
  * 0x10       Character name
  */
};

} /* Sapphire::Common::Network::Packets::Server */



#endif /*_CORE_NETWORK_PACKETS_CHAT_SERVER_IPC_H*/
