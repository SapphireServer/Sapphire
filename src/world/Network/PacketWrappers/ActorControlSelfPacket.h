#pragma once

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The Ping response packet.
  */
  class ActorControlSelfPacket : public ZoneChannelPacket< FFXIVIpcActorControlSelf >
  {
  public:
    ActorControlSelfPacket( uint32_t actorId,
                            uint16_t category,
                            uint32_t param1 = 0,
                            uint32_t param2 = 0,
                            uint32_t param3 = 0,
                            uint32_t param4 = 0,
                            uint32_t param5 = 0,
                            uint32_t padding1 = 0 ) :
      ZoneChannelPacket< FFXIVIpcActorControlSelf >( actorId, actorId )
    {
      initialize( category, param1, param2, param3, param4, param5 );
    };

  private:
    void initialize( uint16_t category, uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4,
                     uint32_t param5 )
    {
      m_data.padding = 0;
      m_data.category = category;
      m_data.param1 = param1;
      m_data.param2 = param2;
      m_data.param3 = param3;
      m_data.param4 = param4;
      m_data.param5 = param5;
    };
  };

  template< typename... Args >
  std::shared_ptr< ActorControlSelfPacket > makeActorControlSelf( Args... args )
  {
    return std::make_shared< ActorControlSelfPacket >( args... );
  }

}