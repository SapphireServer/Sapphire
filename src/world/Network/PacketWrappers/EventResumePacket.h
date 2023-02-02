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
  class EventResumePacketHeader : public ZoneChannelPacket< FFXIVIpcResumeEventSceneHeader >
  {
  public:
    EventResumePacketHeader( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args ) :
      ZoneChannelPacket< FFXIVIpcResumeEventSceneHeader >( player.getId(), player.getId() )
    {
      initialize( player, handlerId, sceneId, resumeId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args )
    {
      m_data.handlerId = handlerId;
      m_data.sceneId = sceneId;
      m_data.resumeId = resumeId;
      m_data.numOfArgs = static_cast< uint8_t >( args.size() );
      if( !args.empty() )
      {
        int i = 0;
        for( auto& val : args )
          m_data.args[ i++ ] = val;
      }
    }

  };

  class EventResume2Packet : public ZoneChannelPacket< FFXIVIpcResumeEventScene2 >
  {
  public:
    EventResume2Packet( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args ) :
      ZoneChannelPacket< FFXIVIpcResumeEventScene2 >( player.getId(), player.getId() )
    {
      initialize( player, handlerId, sceneId, resumeId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args )
    {
      m_data.handlerId = handlerId;
      m_data.sceneId = sceneId;
      m_data.resumeId = resumeId;
      m_data.numOfArgs = static_cast< uint8_t >( args.size() );
      if( !args.empty() )
      {
        int i = 0;
        for( auto& val : args )
          m_data.args[ i++ ] = val;
      }
    }
  };

  class EventResume4Packet : public ZoneChannelPacket< FFXIVIpcResumeEventScene4 >
  {
  public:
    EventResume4Packet( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args ) :
      ZoneChannelPacket< FFXIVIpcResumeEventScene4 >( player.getId(), player.getId() )
    {
      initialize( player, handlerId, sceneId, resumeId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args )
    {
      m_data.handlerId = handlerId;
      m_data.sceneId = sceneId;
      m_data.resumeId = resumeId;
      m_data.numOfArgs = static_cast< uint8_t >( args.size() );
      if( !args.empty() )
      {
        int i = 0;
        for( auto& val : args )
          m_data.args[ i++ ] = val;
      }
    }
  };

  class EventResume8Packet : public ZoneChannelPacket< FFXIVIpcResumeEventScene8 >
  {
  public:
    EventResume8Packet( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args ) :
      ZoneChannelPacket< FFXIVIpcResumeEventScene8 >( player.getId(), player.getId() )
    {
      initialize( player, handlerId, sceneId, resumeId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args )
    {
      m_data.handlerId = handlerId;
      m_data.sceneId = sceneId;
      m_data.resumeId = resumeId;
      m_data.numOfArgs = static_cast< uint8_t >( args.size() );
      if( !args.empty() )
      {
        int i = 0;
        for( auto& val : args )
          m_data.args[ i++ ] = val;
      }
    }
  };

  class EventResume16Packet : public ZoneChannelPacket< FFXIVIpcResumeEventScene16 >
  {
  public:
    EventResume16Packet( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args ) :
      ZoneChannelPacket< FFXIVIpcResumeEventScene16 >( player.getId(), player.getId() )
    {
      initialize( player, handlerId, sceneId, resumeId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args )
    {
      m_data.handlerId = handlerId;
      m_data.sceneId = sceneId;
      m_data.resumeId = resumeId;
      m_data.numOfArgs = static_cast< uint8_t >( args.size() );
      if( !args.empty() )
      {
        int i = 0;
        for( auto& val : args )
          m_data.args[ i++ ] = val;
      }
    }
  };

  class EventResume32Packet : public ZoneChannelPacket< FFXIVIpcResumeEventScene32 >
  {
  public:
    EventResume32Packet( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args ) :
      ZoneChannelPacket< FFXIVIpcResumeEventScene32 >( player.getId(), player.getId() )
    {
      initialize( player, handlerId, sceneId, resumeId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args )
    {
      m_data.handlerId = handlerId;
      m_data.sceneId = sceneId;
      m_data.resumeId = resumeId;
      m_data.numOfArgs = static_cast< uint8_t >( args.size() );
      if( !args.empty() )
      {
        int i = 0;
        for( auto& val : args )
          m_data.args[ i++ ] = val;
      }
    }
  };

  class EventResume64Packet : public ZoneChannelPacket< FFXIVIpcResumeEventScene64 >
  {
  public:
    EventResume64Packet( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args ) :
      ZoneChannelPacket< FFXIVIpcResumeEventScene64 >( player.getId(), player.getId() )
    {
      initialize( player, handlerId, sceneId, resumeId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args )
    {
      m_data.handlerId = handlerId;
      m_data.sceneId = sceneId;
      m_data.resumeId = resumeId;
      m_data.numOfArgs = static_cast< uint8_t >( args.size() );
      if( !args.empty() )
      {
        int i = 0;
        for( auto& val : args )
          m_data.args[ i++ ] = val;
      }
    }
  };

  class EventResume128Packet : public ZoneChannelPacket< FFXIVIpcResumeEventScene128 >
  {
  public:
    EventResume128Packet( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args ) :
      ZoneChannelPacket< FFXIVIpcResumeEventScene128 >( player.getId(), player.getId() )
    {
      initialize( player, handlerId, sceneId, resumeId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args )
    {
      m_data.handlerId = handlerId;
      m_data.sceneId = sceneId;
      m_data.resumeId = resumeId;
      m_data.numOfArgs = static_cast< uint8_t >( args.size() );
      if( !args.empty() )
      {
        int i = 0;
        for( auto& val : args )
          m_data.args[ i++ ] = val;
      }
    }
  };

  class EventResume255Packet : public ZoneChannelPacket< FFXIVIpcResumeEventScene255 >
  {
  public:
    EventResume255Packet( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args ) :
      ZoneChannelPacket< FFXIVIpcResumeEventScene255 >( player.getId(), player.getId() )
    {
      initialize( player, handlerId, sceneId, resumeId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t handlerId, uint16_t sceneId, uint8_t resumeId, std::vector< uint32_t > args )
    {
      m_data.handlerId = handlerId;
      m_data.sceneId = sceneId;
      m_data.resumeId = resumeId;
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
