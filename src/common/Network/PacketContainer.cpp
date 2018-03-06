#include "PacketContainer.h"
#include "GamePacket.h"
#include "Common.h"

#include <boost/format.hpp>

#include <chrono>


Core::Network::Packets::PacketContainer::PacketContainer( void )
{
   memset( &m_ipcHdr, 0, sizeof( FFXIVARR_PACKET_HEADER ) );
   m_ipcHdr.size = sizeof( FFXIVARR_PACKET_HEADER );
   m_ipcHdr.count = 0;
}

Core::Network::Packets::PacketContainer::~PacketContainer( void )
{
   m_entryList.clear();
}

void Core::Network::Packets::PacketContainer::addPacket( GamePacket pEntry )
{
   m_entryList.push_back( pEntry );

   m_ipcHdr.size += pEntry.getSize();
   m_ipcHdr.count++;
}

void Core::Network::Packets::PacketContainer::fillSendBuffer( std::vector< uint8_t >& sendBuffer )
{
   uint8_t* tempBuffer = new uint8_t[m_ipcHdr.size];
   memset( tempBuffer, 0, m_ipcHdr.size );

   using namespace std::chrono;
   auto ms = duration_cast< milliseconds >( system_clock::now().time_since_epoch() );
   uint64_t tick = ms.count();
   m_ipcHdr.unknown_0 = 0xE2465DFF41a05252;
   m_ipcHdr.unknown_8 = 0x75C4997B4D642A7F;
   m_ipcHdr.timestamp = tick;
   m_ipcHdr.unknown_20 = 1;

   memcpy( tempBuffer, &m_ipcHdr, sizeof( FFXIVARR_PACKET_HEADER ) );

   auto it = m_entryList.begin();
   uint16_t offset = 0;

   if( m_entryList.size() > 1 )
      offset = 0;

   for( ; it != m_entryList.end(); ++it )
   {
      memcpy( tempBuffer + sizeof( FFXIVARR_PACKET_HEADER ) + offset, it->getData(), it->m_segHdr.size );
      offset += it->m_segHdr.size;
   }

   sendBuffer.assign( tempBuffer, tempBuffer + m_ipcHdr.size );

   delete[] tempBuffer;

}

std::string Core::Network::Packets::PacketContainer::toString()
{
   std::vector< uint8_t > tmpBuffer;

   fillSendBuffer( tmpBuffer );

   std::string str = "\n";
   for( uint32_t i = 0; i < m_ipcHdr.size; i++ )
   {
      str += boost::str( boost::format( "%|02X|" ) % static_cast< int32_t >( tmpBuffer[i] & 0xFF ) ) + " ";

      if( ( i + 1 ) % 16 == 0 )
         str += "\n";
   }
   str += "\n";

   return str;
}

