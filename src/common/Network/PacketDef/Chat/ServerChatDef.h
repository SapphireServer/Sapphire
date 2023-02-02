#pragma once

#include <Common.h>
#include <Network/CommonNetwork.h>

namespace Sapphire::Network::Packets::Server
{

/**
* Structural representation of the packet sent by the server as response
* to a tell request
*/
struct FFXIVChatFrom : FFXIVIpcBasePacket< ChatFrom >
{
  uint64_t fromCharacterID;
  uint8_t type;
  char fromName[32]; //uint8_t
  char message[1024]; //uint8_t
};

/**
* Structural representation of the packet sent by the server as
* message from a chat channel that the player is associated to
*/
struct FFXIVChatToChannel : FFXIVIpcBasePacket< ChatToChannel >
{
  uint64_t channelID;
  uint64_t speakerCharacterID;
  uint32_t speakerEntityID;
  uint8_t type; 
  char speakerName[32];
  char message[1024];
};

struct FFXIVJoinChannelResult : FFXIVIpcBasePacket< JoinChannelResult >
{
  uint64_t channelID;
  uint64_t characterID;
  uint8_t result;
};

struct FFXIVRecvBusyStatus : FFXIVIpcBasePacket< RecvBusyStatus >
{
  char toName[32]; //uint8_t
};

struct FFXIVRecvFinderStatus : FFXIVIpcBasePacket< RecvFinderStatus >
{
  char toName[32]; //uint8_t
};

/**
* Structural representation of the packet sent by the server as response
* to a failed tell because of unavailable target player
*/
struct FFXIVIpcTellNotFound : FFXIVIpcBasePacket< TellNotFound >
{
  char toName[32]; //uint8_t
};


} /* Sapphire::Common::Network::Packets::Server */

