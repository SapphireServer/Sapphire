#ifndef _GAMEPACKET_H_
#define _GAMEPACKET_H_

#include "CommonNetwork.h"
#include "Forwards.h"
#include <stdint.h>
#include <string.h>

namespace Core {
namespace Network {
namespace Packets {

class GamePacket {
public:
   GamePacket( uint16_t subType, uint16_t size, uint32_t id1, uint32_t id2, uint16_t type = 0x03 );
   GamePacket( char * pData, uint16_t size, bool bWriteStamp = true );

   GamePacket( const Packets::FFXIVARR_PACKET_RAW& packetData );

   GamePacket( void );
   ~GamePacket( void );

   uint16_t getSize()
   {
      return m_segHdr.size;
   }

   uint16_t getType()
   {
      return m_segHdr.type;
   }

   uint16_t getSubType()
   {
      return m_subType;
   }

   template<class T>
   void setValAt( uint16_t pos, T value )
   {
      memcpy( reinterpret_cast< unsigned char* >( &m_dataBuf[0] + pos ), &value, sizeof( T ) );
   }

   template<class T>
   T getValAt( uint16_t pos )
   {
      return *reinterpret_cast< T* >( &m_dataBuf[0] + pos );
   }

   void setBytesAt( uint16_t offset, unsigned char * bytes, uint16_t length )
   {
      memcpy( reinterpret_cast< unsigned char* >( &m_dataBuf[0] + offset ), bytes, length );
   }

   char * getStringAt( uint16_t pos )
   {
      return reinterpret_cast< char* >( &m_dataBuf[0] + pos );
   }

   void setStringAt( uint16_t pos, const std::string& str )
   {
      memcpy( reinterpret_cast< unsigned char* >( &m_dataBuf[0] + pos ), str.c_str(), str.length() );
   }

   unsigned char * getData()
   {
      return reinterpret_cast< unsigned char* >( &m_dataBuf[0] );
   }

   void setHeader( uint16_t size, uint16_t type, uint32_t id1, uint32_t id2, uint16_t subType, uint32_t unknown = 0xFED2E000 );

   std::string toString();

   void savePacket();

   FFXIVARR_PACKET_SEGMENT_HEADER m_segHdr;

protected:

   uint16_t m_unknown2;
   uint16_t m_subType;
   uint32_t m_timeStamp;
   std::vector<uint8_t> m_dataBuf;

};



}
}
}
#endif
