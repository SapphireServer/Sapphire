#pragma once

#include <Network/GamePacket.h>
#include <Actor/Player.h>
#include <Event/EventHandler.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The packet sent to resume an event and fill it with additional data.
  */
  class EventNoticePacketHeader : public ZoneChannelPacket< FFXIVIpcNoticeHeader >
  {
  public:
    EventNoticePacketHeader( const Entity::Player& player, uint32_t handlerId, uint8_t noticeId, std::vector< uint32_t > args = {} ) :
      ZoneChannelPacket< FFXIVIpcNoticeHeader >( player.getId(), player.getId() )
    {
      initialize( player, handlerId, noticeId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t handlerId, uint8_t noticeId, std::vector< uint32_t > args )
    {
      m_data.handlerId = handlerId;
      m_data.noticeId = noticeId;
      m_data.numOfArgs = static_cast< uint8_t >( args.size() );
      if( !args.empty() )
      {
        int i = 0;
        for( auto& val : args )
          m_data.args[ i++ ] = val;
      }
    }
  };

  class EventNotice2Packet : public ZoneChannelPacket< FFXIVIpcNotice2 >
  {
  public:
    EventNotice2Packet( const Entity::Player& player, uint32_t handlerId, uint8_t noticeId, std::vector< uint32_t > args = {} ) :
      ZoneChannelPacket< FFXIVIpcNotice2 >( player.getId(), player.getId() )
    {
      initialize( player, handlerId, noticeId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t handlerId, uint8_t noticeId, std::vector< uint32_t > args )
    {
      m_data.handlerId = handlerId;
      m_data.noticeId = noticeId;
      m_data.numOfArgs = static_cast< uint8_t >( args.size() );
      if( !args.empty() )
      {
        int i = 0;
        for( auto& val : args )
          m_data.args[ i++ ] = val;
      }
    }
  };

  class EventNotice4Packet : public ZoneChannelPacket< FFXIVIpcNotice4 >
  {
  public:
    EventNotice4Packet( const Entity::Player& player, uint32_t handlerId, uint8_t noticeId, std::vector< uint32_t > args = {} ) :
      ZoneChannelPacket< FFXIVIpcNotice4 >( player.getId(), player.getId() )
    {
      initialize( player, handlerId, noticeId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t handlerId, uint8_t noticeId, std::vector< uint32_t > args )
    {
      m_data.handlerId = handlerId;
      m_data.noticeId = noticeId;
      m_data.numOfArgs = static_cast< uint8_t >( args.size() );
      if( !args.empty() )
      {
        int i = 0;
        for( auto& val : args )
          m_data.args[ i++ ] = val;
      }
    }
  };

  class EventNotice8Packet : public ZoneChannelPacket< FFXIVIpcNotice8 >
  {
  public:
    EventNotice8Packet( const Entity::Player& player, uint32_t handlerId, uint8_t noticeId, std::vector< uint32_t > args = {} ) :
      ZoneChannelPacket< FFXIVIpcNotice8 >( player.getId(), player.getId() )
    {
      initialize( player, handlerId, noticeId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t handlerId, uint8_t noticeId, std::vector< uint32_t > args )
    {
      m_data.handlerId = handlerId;
      m_data.noticeId = noticeId;
      m_data.numOfArgs = static_cast< uint8_t >( args.size() );
      if( !args.empty() )
      {
        int i = 0;
        for( auto& val : args )
          m_data.args[ i++ ] = val;
      }
    }
  };

  class EventNotice16Packet : public ZoneChannelPacket< FFXIVIpcNotice16 >
  {
  public:
    EventNotice16Packet( const Entity::Player& player, uint32_t handlerId, uint8_t noticeId, std::vector< uint32_t > args = {} ) :
      ZoneChannelPacket< FFXIVIpcNotice16 >( player.getId(), player.getId() )
    {
      initialize( player, handlerId, noticeId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t handlerId, uint8_t noticeId, std::vector< uint32_t > args )
    {
      m_data.handlerId = handlerId;
      m_data.noticeId = noticeId;
      m_data.numOfArgs = static_cast< uint8_t >( args.size() );
      if( !args.empty() )
      {
        int i = 0;
        for( auto& val : args )
          m_data.args[ i++ ] = val;
      }
    }
  };

  class EventNotice32Packet : public ZoneChannelPacket< FFXIVIpcNotice32 >
  {
  public:
    EventNotice32Packet( const Entity::Player& player, uint32_t handlerId, uint8_t noticeId, std::vector< uint32_t > args = {} ) :
      ZoneChannelPacket< FFXIVIpcNotice32 >( player.getId(), player.getId() )
    {
      initialize( player, handlerId, noticeId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t handlerId, uint8_t noticeId, std::vector< uint32_t > args )
    {
      m_data.handlerId = handlerId;
      m_data.noticeId = noticeId;
      m_data.numOfArgs = static_cast< uint8_t >( args.size() );
      if( !args.empty() )
      {
        int i = 0;
        for( auto& val : args )
          m_data.args[ i++ ] = val;
      }
    }
  };

}
