#ifndef _EVENTLOGMESSAGE_H
#define _EVENTLOGMESSAGE_H

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Actor/Player.h>
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The packet sent for event log messages.
  */
  class EventLogMessageHeader : public ZoneChannelPacket< FFXIVIpcEventLogMessageHeader >
  {
  public:
    EventLogMessageHeader( const Entity::Player& player,
                           uint32_t directorId,
                           uint32_t msgId ) :
      ZoneChannelPacket< FFXIVIpcEventLogMessageHeader >( player.getId() )
    {
      initialize( player, directorId, msgId );
    };

  private:
    void initialize( const Entity::Player& player,
                     uint32_t directorId,
                     uint32_t msgId )
    {
      m_data.handlerId = directorId;
      m_data.messageId = msgId;
      m_data.numOfArgs = 0;
    };
  };
  class EventLogMessage2 : public ZoneChannelPacket< FFXIVIpcEventLogMessage2 >
  {
  public:
    EventLogMessage2( const Entity::Player& player, uint32_t directorId, uint32_t msgId, const std::initializer_list< uint32_t > args ) :
      ZoneChannelPacket< FFXIVIpcEventLogMessage2 >( player.getId() )
    {
      initialize( player, directorId, msgId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t directorId, uint32_t msgId, const std::initializer_list< uint32_t > args )
    {
      m_data.handlerId = directorId;
      m_data.messageId = msgId;
      m_data.numOfArgs = args.size();
      std::copy( args.begin(), args.end(), m_data.args );
    };
  };
  class EventLogMessage4 : public ZoneChannelPacket< FFXIVIpcEventLogMessage4 >
  {
  public:
    EventLogMessage4( const Entity::Player& player, uint32_t directorId, uint32_t msgId, const std::initializer_list< uint32_t > args ) :
      ZoneChannelPacket< FFXIVIpcEventLogMessage4 >( player.getId() )
    {
      initialize( player, directorId, msgId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t directorId, uint32_t msgId, const std::initializer_list< uint32_t > args )
    {
      m_data.handlerId = directorId;
      m_data.messageId = msgId;
      m_data.numOfArgs = args.size();
      std::copy( args.begin(), args.end(), m_data.args );
    };
  };
  class EventLogMessage8 : public ZoneChannelPacket< FFXIVIpcEventLogMessage8 >
  {
  public:
    EventLogMessage8( const Entity::Player& player, uint32_t directorId, uint32_t msgId, const std::initializer_list< uint32_t > args ) :
      ZoneChannelPacket< FFXIVIpcEventLogMessage8 >( player.getId() )
    {
      initialize( player, directorId, msgId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t directorId, uint32_t msgId, const std::initializer_list< uint32_t > args )
    {
      m_data.handlerId = directorId;
      m_data.messageId = msgId;
      m_data.numOfArgs = args.size();
      std::copy( args.begin(), args.end(), m_data.args );
    };
  };
  class EventLogMessage16 : public ZoneChannelPacket< FFXIVIpcEventLogMessage16 >
  {
  public:
    EventLogMessage16( const Entity::Player& player, uint32_t directorId, uint32_t msgId, const std::initializer_list< uint32_t > args ) :
      ZoneChannelPacket< FFXIVIpcEventLogMessage16 >( player.getId() )
    {
      initialize( player, directorId, msgId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t directorId, uint32_t msgId, const std::initializer_list< uint32_t > args )
    {
      m_data.handlerId = directorId;
      m_data.messageId = msgId;
      m_data.numOfArgs = args.size();
      std::copy( args.begin(), args.end(), m_data.args );
    };
  };
  class EventLogMessage32 : public ZoneChannelPacket< FFXIVIpcEventLogMessage32 >
  {
  public:
    EventLogMessage32( const Entity::Player& player, uint32_t directorId, uint32_t msgId, const std::initializer_list< uint32_t > args ) :
      ZoneChannelPacket< FFXIVIpcEventLogMessage32 >( player.getId() )
    {
      initialize( player, directorId, msgId, args );
    };

  private:
    void initialize( const Entity::Player& player, uint32_t directorId, uint32_t msgId, const std::initializer_list< uint32_t > args )
    {
      m_data.handlerId = directorId;
      m_data.messageId = msgId;
      m_data.numOfArgs = args.size();
      std::copy( args.begin(), args.end(), m_data.args );
    };
  };
}

#endif /*_EVENTLOGMESSAGE_H*/
