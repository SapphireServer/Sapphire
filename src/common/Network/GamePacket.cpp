
#include <stdio.h>
#include "GamePacket.h"

#include <time.h>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include "Util/Util.h"

Core::Network::Packets::GamePacket::GamePacket( uint16_t subType, uint16_t size,
                                                uint32_t id1, uint32_t id2, uint16_t type )
{
   m_dataBuf = std::vector< uint8_t >( size );
   memset( &m_segHdr, 0, sizeof( m_segHdr ) );

   setHeader( size, type, id1, id2, subType, 0x00 );
}

void Core::Network::Packets::GamePacket::setHeader( uint16_t size, uint16_t type, uint32_t id1,
                                                    uint32_t id2, uint16_t subType, uint32_t unknown )
{

   m_segHdr.size = size;
   m_segHdr.type = type;
   m_segHdr.source_actor = id1;
   m_segHdr.target_actor = id2;
   //m_segHdr._reserved_E = 0x00;
   m_subType = subType;

   m_timeStamp = static_cast< uint32_t >( time( nullptr ) );
   if( size > 0 )
   {
      memcpy( &m_dataBuf[0], &m_segHdr, sizeof( m_segHdr ) );
      m_dataBuf[0x10] = 0x14;
      *reinterpret_cast< uint16_t* >( &m_dataBuf[0] + 0x12 ) = m_subType;
   }
   if( size > 0x18 )
      *reinterpret_cast< uint32_t* >( &m_dataBuf[0] + 0x18 ) = m_timeStamp;
}

Core::Network::Packets::GamePacket::GamePacket( char * pData, uint16_t size, bool bWriteStamp )
{

   m_dataBuf = std::vector< uint8_t >( size );
   memcpy( &m_dataBuf[0], pData, size );
   m_unknown2 = 0;

   if( bWriteStamp && size > 0x18 )
   {
      m_timeStamp = static_cast< uint32_t >( time( nullptr ) );
      *reinterpret_cast< uint16_t* >( &m_dataBuf[0] + 0x10 ) = 0x14;
      *reinterpret_cast< uint32_t* >( &m_dataBuf[0] + 0x18 ) = m_timeStamp;
   }

   //m_segHdr._reserved_E = 0;
   m_segHdr.size = *reinterpret_cast< uint32_t* >( &m_dataBuf[0] );
   m_segHdr.type = *reinterpret_cast< uint16_t* >( &m_dataBuf[0] + 0x0C );
   m_subType = *reinterpret_cast< uint16_t* >( &m_dataBuf[0] + 0x12 );

   m_segHdr.source_actor = *reinterpret_cast< uint32_t* >( &m_dataBuf[0] + 0x04 );
   m_segHdr.target_actor = *reinterpret_cast< uint32_t* >( &m_dataBuf[0] + 0x08 );

}

Core::Network::Packets::GamePacket::GamePacket( const Packets::FFXIVARR_PACKET_RAW& packetData )
{

   m_segHdr = packetData.segHdr;
   m_dataBuf = std::vector< uint8_t >( m_segHdr.size );

   memcpy( &m_dataBuf[0] + sizeof( Packets::FFXIVARR_PACKET_SEGMENT_HEADER ),
           &packetData.data[0],
           m_segHdr.size - sizeof( Packets::FFXIVARR_PACKET_SEGMENT_HEADER ) );

   memcpy( &m_dataBuf[0], &m_segHdr, sizeof( Packets::FFXIVARR_PACKET_SEGMENT_HEADER ) );

   m_subType = *reinterpret_cast< uint16_t* >( &m_dataBuf[0] + 0x12 );

   if( m_segHdr.size > 0x18 )
      m_timeStamp = *reinterpret_cast< uint32_t* >( &m_dataBuf[0] + 0x18 );
}

Core::Network::Packets::GamePacket::GamePacket()
{
}


Core::Network::Packets::GamePacket::~GamePacket()
{
}

void Core::Network::Packets::GamePacket::savePacket()
{
   char filename[20];
   sprintf( filename, "dump_0x%x_%i.dat", m_subType, Util::getTimeMs() );
   FILE * fp = nullptr;
   fp = fopen( filename, "wb" );
   fwrite( &m_dataBuf[0], 1, m_segHdr.size, fp );
   fclose( fp );
}


std::string Core::Network::Packets::GamePacket::toString() const
{
   return Core::Util::binaryToHexDump( const_cast< uint8_t* >( &m_dataBuf[0] ), getSize() );
}
