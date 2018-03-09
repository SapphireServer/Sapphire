#ifndef _GAMEPACKET_H_
#define _GAMEPACKET_H_

#include "CommonNetwork.h"
#include "Forwards.h"
#include <stdint.h>
#include <string.h>

namespace Core {
namespace Network {
namespace Packets {

class GamePacket
{
public:
   GamePacket( uint16_t subType, uint16_t size, uint32_t id1, uint32_t id2, uint16_t type = 0x03 );
   GamePacket( char* pData, uint16_t size, bool bWriteStamp = true );

   GamePacket( const Packets::FFXIVARR_PACKET_RAW& packetData );

   GamePacket( void );
   ~GamePacket( void );

   uint16_t getSize() const
   {
      return m_segHdr.size;
   }

   uint16_t getType() const
   {
      return m_segHdr.type;
   }

   uint16_t getSubType() const
   {
      return m_subType;
   }

   template< class T >
   void setValAt( uint16_t pos, T value )
   {
      assert( m_segHdr.size > pos );
      memcpy( reinterpret_cast< uint8_t* >( &m_dataBuf[0] + pos ), &value, sizeof( T ) );
   }

   template< class T >
   T getValAt( uint16_t pos ) const
   {
      assert( m_segHdr.size > pos );
      return *reinterpret_cast< const T* >( &m_dataBuf[0] + pos );
   }

   void setBytesAt( uint16_t offset, uint8_t * bytes, uint16_t length )
   {
      assert( m_segHdr.size > offset );
      memcpy( reinterpret_cast< uint8_t* >( &m_dataBuf[0] + offset ), bytes, length );
   }

   const char* getStringAt( uint16_t pos ) const
   {
      assert( m_segHdr.size > pos );
      return reinterpret_cast< const char* >( &m_dataBuf[0] + pos );
   }

   void setStringAt( uint16_t pos, const std::string& str )
   {
      assert( m_segHdr.size > pos );
      memcpy( reinterpret_cast< uint8_t* >( &m_dataBuf[0] + pos ), str.c_str(), str.length() );
   }

   const uint8_t* getData() const
   {
      return reinterpret_cast< const uint8_t* >( &m_dataBuf[0] );
   }

   const uint8_t* getDataAt(uint16_t pos) const
   {
      assert( m_segHdr.size > pos );
      return reinterpret_cast< const uint8_t* >( &m_dataBuf[0] + pos );
   }

   void setHeader( uint16_t size, uint16_t type, uint32_t id1, uint32_t id2, uint16_t subType, uint32_t unknown = 0xFED2E000 );

   std::string toString() const;

   void savePacket();

   FFXIVARR_PACKET_SEGMENT_HEADER m_segHdr;

protected:

   uint16_t m_unknown2;
   uint16_t m_subType;
   uint32_t m_timeStamp;
   std::vector< uint8_t > m_dataBuf;

};



}
}
}
#endif
