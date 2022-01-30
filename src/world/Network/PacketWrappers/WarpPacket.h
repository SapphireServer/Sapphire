#pragma once

#include <Network/GamePacket.h>

#include "Forwards.h"
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Common.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The Ping response packet.
  */
  class WarpPacket : public ZoneChannelPacket< FFXIVIpcWarp >
  {
  public:
    WarpPacket( uint32_t playerId, Common::WarpType warpType, Common::FFXIVARR_POSITION3& targetPos, float rotation ) :
      ZoneChannelPacket< FFXIVIpcWarp >( playerId, playerId )
    {
      initialize( warpType, targetPos, rotation );
    };

  private:
    void initialize( Common::WarpType warpType, Common::FFXIVARR_POSITION3& targetPos, float rotation )
    {
      m_data.Dir = Sapphire::Common::Util::floatToUInt16Rot( rotation );
      m_data.Type = warpType;
      m_data.x = targetPos.x;
      m_data.y = targetPos.y;
      m_data.z = targetPos.z;
    };
  };
  template< typename... Args >
  std::shared_ptr< WarpPacket > makeWarp( Args... args )
  {
    return std::make_shared< WarpPacket >( args... );
  }
}

