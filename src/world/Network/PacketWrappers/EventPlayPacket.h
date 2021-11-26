#ifndef _EVENTPLAY_H
#define _EVENTPLAY_H

#include <Network/GamePacket.h>
#include <Actor/Player.h>
#include <Event/EventHandler.h>
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The packet sent to play an event.
  */
  class EventPlayPacketHeader : public ZoneChannelPacket< FFXIVIpcPlayEventSceneHeader >
  {
  public:
    EventPlayPacketHeader( const Entity::Player& player,
                           uint64_t actorId,
                           uint32_t eventId,
                           uint16_t sceneId,
                           uint32_t flags ) :
      ZoneChannelPacket< FFXIVIpcPlayEventSceneHeader >( player.getId(), player.getId() )
    {
      initialize( player, actorId, eventId, sceneId, flags );
    };

  private:
    void initialize( const Entity::Player& player,
                     uint64_t actorId,
                     uint32_t eventId,
                     uint16_t sceneId,
                     uint32_t flags )
    {
      m_data.actorId = actorId;
      m_data.eventId = eventId;
      m_data.scene = sceneId;
      m_data.sceneFlags = flags;

      if( auto pEvent = player.getEvent( eventId ) )
      {
        auto size = static_cast< uint32_t >( pEvent->getScenePlayParams()->getParams( sceneId )->size() );
        if( size )
        {
          memcpy( &m_data.params[0], pEvent->getScenePlayParams()->getParams( sceneId )->data(), size * sizeof( uint32_t ) );
          m_data.paramCount = size;
          pEvent->getScenePlayParams()->getParams( sceneId )->clear();
        }
      }
    };
  };
  class EventPlayPacket2 : public ZoneChannelPacket< FFXIVIpcPlayEventScene2 >
  {
  public:
    EventPlayPacket2( const Entity::Player& player, uint64_t actorId, uint32_t eventId, uint16_t sceneId, uint32_t flags ) :
      ZoneChannelPacket< FFXIVIpcPlayEventScene2 >( player.getId(), player.getId() )
    {
      initialize( player, actorId, eventId, sceneId, flags );
    };

  private:
    void initialize( const Entity::Player& player, uint64_t actorId, uint32_t eventId, uint16_t sceneId, uint32_t flags )
    {
      m_data.actorId = actorId;
      m_data.eventId = eventId;
      m_data.scene = sceneId;
      m_data.sceneFlags = flags;

      if( auto pEvent = player.getEvent( eventId ) )
      {
        auto pEventParam = pEvent->getScenePlayParams()->getParams( sceneId );
        if( pEventParam )
        {
          auto size = static_cast< uint8_t >( pEventParam->size() );
          memcpy( &m_data.params[0], pEvent->getScenePlayParams()->getParams( sceneId )->data(), size * sizeof( uint32_t ) );
          m_data.paramCount = size;
          pEvent->getScenePlayParams()->getParams( sceneId )->clear();
        }
      }
    };
  };
  class EventPlayPacket4 : public ZoneChannelPacket< FFXIVIpcPlayEventScene4 >
  {
  public:
    EventPlayPacket4( const Entity::Player& player,
                      uint64_t actorId,
                      uint32_t eventId,
                      uint16_t sceneId,
                      uint32_t flags ) :
      ZoneChannelPacket< FFXIVIpcPlayEventScene4 >( player.getId(), player.getId() )
    {
      initialize( player, actorId, eventId, sceneId, flags );
    };

  private:
    void initialize( const Entity::Player& player,
                     uint64_t actorId,
                     uint32_t eventId,
                     uint16_t sceneId,
                     uint32_t flags )
    {
      m_data.actorId = actorId;
      m_data.eventId = eventId;
      m_data.scene = sceneId;
      m_data.sceneFlags = flags;

      if( auto pEvent = player.getEvent( eventId ) )
      {
        auto size = static_cast< uint32_t >( pEvent->getScenePlayParams()->getParams( sceneId )->size() );
        if( size )
        {
          memcpy( &m_data.params[0], pEvent->getScenePlayParams()->getParams( sceneId )->data(), size * sizeof( uint32_t ) );
          m_data.paramCount = size;
          pEvent->getScenePlayParams()->getParams( sceneId )->clear();
        }
      }
    };
  };
  class EventPlayPacket8 : public ZoneChannelPacket< FFXIVIpcPlayEventScene8 >
  {
  public:
    EventPlayPacket8( const Entity::Player& player,
                      uint64_t actorId,
                      uint32_t eventId,
                      uint16_t sceneId,
                      uint32_t flags ) :
      ZoneChannelPacket< FFXIVIpcPlayEventScene8 >( player.getId(), player.getId() )
    {
      initialize( player, actorId, eventId, sceneId, flags );
    };

  private:
    void initialize( const Entity::Player& player,
                     uint64_t actorId,
                     uint32_t eventId,
                     uint16_t sceneId,
                     uint32_t flags )
    {
      m_data.actorId = actorId;
      m_data.eventId = eventId;
      m_data.scene = sceneId;
      m_data.sceneFlags = flags;

      if( auto pEvent = player.getEvent( eventId ) )
      {
        auto size = static_cast< uint32_t >( pEvent->getScenePlayParams()->getParams( sceneId )->size() );
        if( size )
        {
          memcpy( &m_data.params[0], pEvent->getScenePlayParams()->getParams( sceneId )->data(), size * sizeof( uint32_t ) );
          m_data.paramCount = size;
          pEvent->getScenePlayParams()->getParams( sceneId )->clear();
        }
      }
    };
  };
  class EventPlayPacket16 : public ZoneChannelPacket< FFXIVIpcPlayEventScene16 >
  {
  public:
    EventPlayPacket16( const Entity::Player& player,
                       uint64_t actorId,
                       uint32_t eventId,
                       uint16_t sceneId,
                       uint32_t flags ) :
      ZoneChannelPacket< FFXIVIpcPlayEventScene16 >( player.getId(), player.getId() )
    {
      initialize( player, actorId, eventId, sceneId, flags );
    };

  private:
    void initialize( const Entity::Player& player,
                     uint64_t actorId,
                     uint32_t eventId,
                     uint16_t sceneId,
                     uint32_t flags )
    {
      m_data.actorId = actorId;
      m_data.eventId = eventId;
      m_data.scene = sceneId;
      m_data.sceneFlags = flags;

      if( auto pEvent = player.getEvent( eventId ) )
      {
        auto size = static_cast< uint32_t >( pEvent->getScenePlayParams()->getParams( sceneId )->size() );
        if( size )
        {
          memcpy( &m_data.params[0], pEvent->getScenePlayParams()->getParams( sceneId )->data(), size * sizeof( uint32_t ) );
          m_data.paramCount = size;
          pEvent->getScenePlayParams()->getParams( sceneId )->clear();
        }
      }
    };
  };
  class EventPlayPacket32 : public ZoneChannelPacket< FFXIVIpcPlayEventScene32 >
  {
  public:
    EventPlayPacket32( const Entity::Player& player,
                       uint64_t actorId,
                       uint32_t eventId,
                       uint16_t sceneId,
                       uint32_t flags ) :
      ZoneChannelPacket< FFXIVIpcPlayEventScene32 >( player.getId(), player.getId() )
    {
      initialize( player, actorId, eventId, sceneId, flags );
    };

  private:
    void initialize( const Entity::Player& player,
                     uint64_t actorId,
                     uint32_t eventId,
                     uint16_t sceneId,
                     uint32_t flags )
    {
      m_data.actorId = actorId;
      m_data.eventId = eventId;
      m_data.scene = sceneId;
      m_data.sceneFlags = flags;

      if( auto pEvent = player.getEvent( eventId ) )
      {
        auto size = static_cast< uint32_t >( pEvent->getScenePlayParams()->getParams( sceneId )->size() );
        if( size )
        {
          memcpy( &m_data.params[0], pEvent->getScenePlayParams()->getParams( sceneId )->data(), size * sizeof( uint32_t ) );
          m_data.paramCount = size;
          pEvent->getScenePlayParams()->getParams( sceneId )->clear();
        }
      }
    };
  };
  class EventPlayPacket64 : public ZoneChannelPacket< FFXIVIpcPlayEventScene64 >
  {
  public:
    EventPlayPacket64( const Entity::Player& player,
                       uint64_t actorId,
                       uint32_t eventId,
                       uint16_t sceneId,
                       uint32_t flags ) :
      ZoneChannelPacket< FFXIVIpcPlayEventScene64 >( player.getId(), player.getId() )
    {
      initialize( player, actorId, eventId, sceneId, flags );
    };

  private:
    void initialize( const Entity::Player& player,
                     uint64_t actorId,
                     uint32_t eventId,
                     uint16_t sceneId,
                     uint32_t flags )
    {
      m_data.actorId = actorId;
      m_data.eventId = eventId;
      m_data.scene = sceneId;
      m_data.sceneFlags = flags;

      if( auto pEvent = player.getEvent( eventId ) )
      {
        auto size = static_cast< uint32_t >( pEvent->getScenePlayParams()->getParams( sceneId )->size() );
        if( size )
        {
          memcpy( &m_data.params[0], pEvent->getScenePlayParams()->getParams( sceneId )->data(), size * sizeof( uint32_t ) );
          m_data.paramCount = size;
          pEvent->getScenePlayParams()->getParams( sceneId )->clear();
        }
      }
    };
  };
  class EventPlayPacket128 : public ZoneChannelPacket< FFXIVIpcPlayEventScene128 >
  {
  public:
    EventPlayPacket128( const Entity::Player& player,
                        uint64_t actorId,
                        uint32_t eventId,
                        uint16_t sceneId,
                        uint32_t flags ) :
      ZoneChannelPacket< FFXIVIpcPlayEventScene128 >( player.getId(), player.getId() )
    {
      initialize( player, actorId, eventId, sceneId, flags );
    };

  private:
    void initialize( const Entity::Player& player,
                     uint64_t actorId,
                     uint32_t eventId,
                     uint16_t sceneId,
                     uint32_t flags )
    {
      m_data.actorId = actorId;
      m_data.eventId = eventId;
      m_data.scene = sceneId;
      m_data.sceneFlags = flags;

      if( auto pEvent = player.getEvent( eventId ) )
      {
        auto size = static_cast< uint32_t >( pEvent->getScenePlayParams()->getParams( sceneId )->size() );
        if( size )
        {
          memcpy( &m_data.params[0], pEvent->getScenePlayParams()->getParams( sceneId )->data(), size * sizeof( uint32_t ) );
          m_data.paramCount = size;
          pEvent->getScenePlayParams()->getParams( sceneId )->clear();
        }
      }
    };
  };
  class EventPlayPacket255 : public ZoneChannelPacket< FFXIVIpcPlayEventScene255 >
  {
  public:
    EventPlayPacket255( const Entity::Player& player,
                        uint64_t actorId,
                        uint32_t eventId,
                        uint16_t sceneId,
                        uint32_t flags ) :
      ZoneChannelPacket< FFXIVIpcPlayEventScene255 >( player.getId(), player.getId() )
    {
      initialize( player, actorId, eventId, sceneId, flags );
    };

  private:
    void initialize( const Entity::Player& player,
                     uint64_t actorId,
                     uint32_t eventId,
                     uint16_t sceneId,
                     uint32_t flags )
    {
      m_data.actorId = actorId;
      m_data.eventId = eventId;
      m_data.scene = sceneId;
      m_data.sceneFlags = flags;

      if( auto pEvent = player.getEvent( eventId ) )
      {
        auto size = static_cast< uint32_t >( pEvent->getScenePlayParams()->getParams( sceneId )->size() );
        if( size )
        {
          memcpy( &m_data.params[0], pEvent->getScenePlayParams()->getParams( sceneId )->data(), size * sizeof( uint32_t ) );
          m_data.paramCount = size;
          pEvent->getScenePlayParams()->getParams( sceneId )->clear();
        }
      }
    };
  };
}

#endif /*_EVENTPLAY_H*/
