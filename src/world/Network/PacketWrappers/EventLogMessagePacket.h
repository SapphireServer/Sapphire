#pragma once

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <ForwardsCommon.h>
#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

namespace Sapphire::Network::Packets::WorldPackets::Server
{
  template< typename PacketType >
  class EventLogMessagePacket : public ZoneChannelPacket< PacketType >
  {
  public:
    EventLogMessagePacket( uint32_t actorId, uint32_t handlerId, uint32_t messageId,
                           std::initializer_list< uint32_t > args ) :
      ZoneChannelPacket< PacketType >( actorId )
    {
      auto& data = this->data();
      if( args.size() > std::size( data.args ) )
        throw std::length_error( "Event log arguments exceed packet capacity" );

      data.handlerId = handlerId;
      data.messageId = messageId;
      data.numOfArgs = static_cast< uint8_t >( args.size() );
      std::copy( args.begin(), args.end(), data.args );
    }
  };

  inline FFXIVPacketBasePtr makeEventLogMessage( uint32_t actorId, uint32_t handlerId, uint32_t messageId,
                                                 std::initializer_list< uint32_t > args )
  {
    if( args.size() <= 2 )
    {
      return std::make_shared< EventLogMessagePacket< FFXIVIpcEventLogMessage2 > >( actorId, handlerId, messageId, args );
    }
    if( args.size() <= 4 )
    {
      return std::make_shared< EventLogMessagePacket< FFXIVIpcEventLogMessage4 > >( actorId, handlerId, messageId, args );
    }
    if( args.size() <= 8 )
    {
      return std::make_shared< EventLogMessagePacket< FFXIVIpcEventLogMessage8 > >( actorId, handlerId, messageId, args );
    }
    if( args.size() <= 16 )
    {
      return std::make_shared< EventLogMessagePacket< FFXIVIpcEventLogMessage16 > >( actorId, handlerId, messageId, args );
    }
    return std::make_shared< EventLogMessagePacket< FFXIVIpcEventLogMessage32 > >( actorId, handlerId, messageId, args );
  }
}
