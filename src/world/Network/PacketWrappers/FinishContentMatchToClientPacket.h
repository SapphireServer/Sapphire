#pragma once

#include <Network/GamePacket.h>
#include "Actor/Player.h"
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief Packet to display a quest specific info message.
  */
  class FinishContentMatchToClientPacket : public ZoneChannelPacket< FFXIVIpcFinishContentMatchToClient >
  {
  public:
    FinishContentMatchToClientPacket( uint32_t playerId, uint16_t terriId, uint8_t classJob, uint8_t playerNum, uint8_t progress = 0, uint32_t flags = 0, uint32_t finishContentMatchFlags = 0 ) :
      ZoneChannelPacket< FFXIVIpcFinishContentMatchToClient >( playerId, playerId )
    {
      initialize( terriId, classJob, playerNum, progress, flags, finishContentMatchFlags );
    };

  private:
    void initialize( uint16_t terriId, uint8_t classJob, uint8_t playerNum, uint8_t progress, uint32_t flags, uint32_t finishContentMatchFlags )
    {
      m_data.territoryType = terriId;
      m_data.classJob = classJob;
      m_data.playerNum = playerNum;
      m_data.progress = progress;
      m_data.flags = flags;
      m_data.finishContentMatchFlags = finishContentMatchFlags;
      m_data.startTime = Common::Util::getTimeSeconds();
    };
  };

  template< typename... Args >
  std::shared_ptr< FinishContentMatchToClientPacket > makeFinishContentMatchToClient( Args... args )
  {
    return std::make_shared< FinishContentMatchToClientPacket >( args... );
  }
}
