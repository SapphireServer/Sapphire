#pragma once

#include <map>
#include <vector>
#include "ForwardsZone.h"

namespace Sapphire::Data
{
  using ChatChannelMembers = std::vector< uint32_t >;

  union ChatChannel
  {
    uint64_t ChannelID;

    struct ChannelData {
      uint32_t ChannelNo;
      uint16_t ChannelType;
      uint16_t WorldId;
    } data;
  };
}

namespace Sapphire::World::Manager
{
  class ChatChannelMgr
  {
  public:
    ChatChannelMgr() = default;
    ~ChatChannelMgr() = default;

    const uint64_t createChatChannel( Common::ChatChannelType type );

    void addToChannel( uint64_t channelId, Entity::Player& player );
    void removeFromChannel( uint64_t channelId, Entity::Player& player );

    void sendMessageToChannel( uint64_t channelId, Entity::Player& sender, const std::string& message );
    
    bool isChannelValid( uint64_t channelId ) const;
    const Data::ChatChannelMembers& getChatChannel( uint64_t channelId );

  private:
    std::map< uint64_t, Data::ChatChannelMembers > m_channels;
    uint32_t m_lastChatNo = 0x1000;
  };
}