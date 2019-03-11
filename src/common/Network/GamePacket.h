#ifndef _GAMEPACKET_H
#define _GAMEPACKET_H

#include <stdint.h>
#include <iostream>

#include <sstream>
#include <time.h>

#include <string.h>
#include <memory>
#include <Util/Util.h>

#include "CommonNetwork.h"
#include "PacketDef/Ipcs.h"

namespace Sapphire::Network::Packets
{

  // Must forward define these in order to enable the compiler to produce the
  // correct template functions.
  template< typename T, typename T1 >
  class FFXIVIpcPacket;

  template< class T >
  using ZoneChannelPacket = FFXIVIpcPacket< T, ServerZoneIpcType >;

  template< class T >
  using ChatChannelPacket = FFXIVIpcPacket< T, ServerChatIpcType >;

  template< class T >
  using LobbyChannelPacket = FFXIVIpcPacket< T, ServerLobbyIpcType >;


  template< class T, typename... Args >
  std::shared_ptr< ZoneChannelPacket< T > > makeZonePacket( Args... args )
  {
    return std::make_shared< ZoneChannelPacket< T > >( args... );
  }

  template< class T, typename... Args >
  std::shared_ptr< T > makeWrappedPacket( Args... args )
  {
    return std::make_shared< T >( args... );
  }

  template< class T, typename... Args >
  std::shared_ptr< ChatChannelPacket< T > > makeChatPacket( Args... args )
  {
    return std::make_shared< ChatChannelPacket< T > >( args... );
  }

  template< class T, typename... Args >
  std::shared_ptr< LobbyChannelPacket< T > > makeLobbyPacket( Args... args )
  {
    return std::make_shared< LobbyChannelPacket< T > >( args... );
  }

  /**
  * The base implementation of a game packet. Needed for parsing packets.
  */
  template< typename T1 >
  class FFXIVIpcPacketBase
  {
  public:
    virtual ~FFXIVIpcPacketBase() = default;

    /**
    * @brief Gets the IPC type of this packet. (Useful for determining the
    * type of a parsed packet.)
    */
    virtual T1 ipcType() = 0;
  };

  ////////////////////////////////////////////////7

  class FFXIVPacketBase
  {
  public:
    FFXIVPacketBase() :
      m_segmentType( 0 )
    {
      initializeSegmentHeader();
    }

    FFXIVPacketBase( uint16_t segmentType, uint32_t sourceActorId, uint32_t targetActorId ) :
      m_segmentType( segmentType )
    {
      initializeSegmentHeader();
      setSourceActor( sourceActorId );
      setTargetActor( targetActorId );
    }

    std::size_t getSize() const
    {
      return m_segHdr.size;
    }

    virtual std::vector< uint8_t > getData() const
    {
      return {};
    }

  protected:
    /** The segment header */
    FFXIVARR_PACKET_SEGMENT_HEADER m_segHdr;
    uint16_t m_segmentType;

  public:
    virtual size_t getContentSize()
    {
      return 0;
    };

    virtual std::vector< uint8_t > getContent()
    {
      return {};
    };

    /**
    * @brief Gets the segment type of this packet.
    */
    uint16_t getSegmentType() const
    {
      return m_segmentType;
    }

    /**
    * @brief Sets the source actor id for this packet.
    * @param actorId The source actor id.
    */
    void setSourceActor( uint32_t actorId )
    {
      m_segHdr.source_actor = actorId;
    };

    /**
    * @brief Gets the source actor id for this packet.
    * @return The source actor id.
    */
    uint32_t getSourceActor() const
    {
      return m_segHdr.source_actor;
    };

    /**
    * @brief Sets the target actor id for this packet.
    * @param actorId The target actor id.
    */
    void setTargetActor( uint32_t actorId )
    {
      m_segHdr.target_actor = actorId;
    };

    /**
    * @brief Gets the target actor id for this packet.
    */
    uint32_t getTargetActor( void ) const
    {
      return m_segHdr.target_actor;
    };

    /** Initializes the fields of the segment header structure */
    virtual void initializeSegmentHeader( void )
    {
      // Zero out the structure.
      memset( &m_segHdr, 0, sizeof( FFXIVARR_PACKET_SEGMENT_HEADER ) );

      // Set the values of static fields.
      // The size must be the sum of the segment header and the content
      m_segHdr.size = static_cast< uint32_t >( sizeof( FFXIVARR_PACKET_SEGMENT_HEADER ) + getContentSize() );
      m_segHdr.type = getSegmentType();
    }

  };

  template< typename T, typename T1 >
  class FFXIVIpcPacket :
    public FFXIVIpcPacketBase< T1 >, public FFXIVPacketBase
  {
  public:
    FFXIVIpcPacket< T, T1 >( uint32_t sourceActorId, uint32_t targetActorId ) :
      FFXIVPacketBase( 3, sourceActorId, targetActorId )
    {
      initialize();
    };

    FFXIVIpcPacket< T, T1 >( uint32_t sourceActorId ) :
      FFXIVPacketBase( 3, sourceActorId, sourceActorId )
    {
      initialize();
    };

    FFXIVIpcPacket< T, T1 >( const FFXIVARR_PACKET_RAW& rawPacket )
    {
      auto ipcHdrSize = sizeof( FFXIVARR_IPC_HEADER );
      auto copySize = std::min< size_t >( sizeof( T ), rawPacket.segHdr.size - ipcHdrSize );

      memcpy( &m_segHdr, &rawPacket.segHdr, sizeof( FFXIVARR_PACKET_SEGMENT_HEADER ) );
      memcpy( &m_data, &rawPacket.data[ 0 ] + ipcHdrSize, copySize );

      memset( &m_ipcHdr, 0, ipcHdrSize );
      m_ipcHdr.type = static_cast< ServerZoneIpcType >( m_data._ServerIpcType );
    }

    size_t getContentSize() override
    {
      return sizeof( FFXIVARR_IPC_HEADER ) + sizeof( T );
    }

    std::vector< uint8_t > getContent() override
    {
      std::vector< uint8_t > content( getContentSize() );
      memcpy( content.data(), &m_ipcHdr, sizeof( FFXIVARR_IPC_HEADER ) );
      memcpy( content.data() + sizeof( FFXIVARR_IPC_HEADER ), &m_data, sizeof( T ) );
      return content;
    }

    std::vector< uint8_t > getData() const override
    {
      auto segmentHeaderSize = sizeof( FFXIVARR_PACKET_SEGMENT_HEADER );
      auto ipcHeaderSize = sizeof( FFXIVARR_IPC_HEADER );
      auto dataSize = sizeof( m_data );

      std::vector< uint8_t > data( segmentHeaderSize + ipcHeaderSize + dataSize );

      memcpy( &data[ 0 ], &m_segHdr, segmentHeaderSize );
      memcpy( &data[ segmentHeaderSize ], &m_ipcHdr, ipcHeaderSize );
      memcpy( &data[ segmentHeaderSize + ipcHeaderSize ], &m_data, dataSize );

      return data;
    }

    T1 ipcType() override
    {
      return static_cast< T1 >( m_data._ServerIpcType );
    };

    /** Gets a reference to the underlying IPC data structure. */
    T& data()
    {
      return m_data;
    };

    const T& data() const
    {
      return m_data;
    }

  protected:
    /** Initializes the fields of the header structures */
    virtual void initialize()
    {
      // Zero out the structures.
      memset( &m_ipcHdr, 0, sizeof( FFXIVARR_IPC_HEADER ) );
      memset( &m_data, 0, sizeof( T ) );

      // The IPC type itself.
      m_ipcHdr.type = static_cast< ServerZoneIpcType >( m_data._ServerIpcType );
      m_ipcHdr.timestamp = Util::getTimeSeconds();
      m_segHdr.size = sizeof( T ) + sizeof( FFXIVARR_IPC_HEADER ) + sizeof( FFXIVARR_PACKET_SEGMENT_HEADER );
    };

  protected:
    /** The IPC packet header */
    FFXIVARR_IPC_HEADER m_ipcHdr;
    /** The underlying data portion of the packet as a structure */
    T m_data;
  };


  class FFXIVRawPacket :
    public FFXIVPacketBase
  {
  public:
    FFXIVRawPacket( uint16_t type, uint32_t size, uint32_t sourceActorId, uint32_t targetActorId ) :
      m_data( std::vector< uint8_t >( size - sizeof( FFXIVARR_PACKET_SEGMENT_HEADER ) ) ),
      FFXIVPacketBase( type, sourceActorId, targetActorId )
    {
      initialize();
      m_segHdr.size = size;
    };

    FFXIVRawPacket( char* data, uint16_t size ) :
      m_data( std::vector< uint8_t >( size ) )
    {
      auto segmentHdrSize = sizeof( FFXIVARR_PACKET_SEGMENT_HEADER );

      memcpy( &m_data[ 0 ], data + segmentHdrSize, size - segmentHdrSize );
      memcpy( &m_segHdr, data, segmentHdrSize );
    }

    size_t getContentSize() override
    {
      return m_data.size();
    }

    std::vector< uint8_t > getContent() override
    {
      return m_data;
    }

    virtual std::vector< uint8_t > getData() const override
    {
      std::vector< uint8_t > data( sizeof( FFXIVARR_PACKET_SEGMENT_HEADER ) + m_data.size() );

      memcpy( &data[ 0 ], &m_segHdr, sizeof( FFXIVARR_PACKET_SEGMENT_HEADER ) );
      memcpy( &data[ sizeof( FFXIVARR_PACKET_SEGMENT_HEADER ) ], &m_data[ 0 ], m_data.size() );

      return data;
    }

    /** Gets a reference to the underlying IPC data structure. */
    std::vector< uint8_t >& data()
    {
      return m_data;
    };

  protected:
    /** Initializes the fields of the header structures */
    virtual void initialize()
    {
      // Zero out the structures.
      memset( &m_data[ 0 ], 0, m_data.size() );
    };

  protected:
    /** The underlying data portion of the packet as a structure */
    std::vector< uint8_t > m_data;
  };

}

#endif