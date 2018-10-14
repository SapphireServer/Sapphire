#include "Util.h"
#include <chrono>
#include <boost/variant/detail/substitute.hpp>
#include <boost/format.hpp>

std::string Core::Util::binaryToHexString( uint8_t* pBinData, uint16_t size )
{
  std::string outStr;

  for( uint32_t i = 0; i < size; i++ )
  {
    outStr += boost::str( boost::format( "%|02X|" ) % ( int32_t ) ( pBinData[ i ] & 0xFF ) );
  }

  return outStr;

}

std::string Core::Util::binaryToHexDump( uint8_t* pBinData, uint16_t size )
{
  int bytesPerLine = 16;
  constexpr char hexChars[] = "0123456789ABCDEF";

  int offsetBlock = 8 + 3;
  int byteBlock = offsetBlock + bytesPerLine * 3 + ( bytesPerLine - 1 ) / 8 + 2;
  int lineLength = byteBlock + bytesPerLine + 1;

  std::string line( lineLength, ' ' );
  int numLines = ( size + bytesPerLine - 1 ) / bytesPerLine;


  std::string outStr;

  for( uint32_t i = 0; i < size; i += bytesPerLine )
  {
    line[ 0 ] = hexChars[ ( i >> 28 ) & 0xF ];
    line[ 1 ] = hexChars[ ( i >> 24 ) & 0xF ];
    line[ 2 ] = hexChars[ ( i >> 20 ) & 0xF ];
    line[ 3 ] = hexChars[ ( i >> 16 ) & 0xF ];
    line[ 4 ] = hexChars[ ( i >> 12 ) & 0xF ];
    line[ 5 ] = hexChars[ ( i >> 8 ) & 0xF ];
    line[ 6 ] = hexChars[ ( i >> 4 ) & 0xF ];
    line[ 7 ] = hexChars[ ( i >> 0 ) & 0xF ];

    int hexColumn = offsetBlock;
    int charColumn = byteBlock;

    for( int j = 0; j < bytesPerLine; j++ )
    {
      if( j > 0 && ( j & 7 ) == 0 )
      {
        hexColumn++;
      }

      if( i + j >= size )
      {
        line[ hexColumn ] = ' ';
        line[ hexColumn + 1 ] = ' ';
        line[ charColumn ] = ' ';
      }
      else
      {
        uint8_t by = pBinData[ i + j ];
        line[ hexColumn ] = hexChars[ ( by >> 4 ) & 0xF ];
        line[ hexColumn + 1 ] = hexChars[ by & 0xF ];
        line[ charColumn ] = by < 32 ? '.' : static_cast< char >( by );
      }

      hexColumn += 3;
      charColumn++;
    }

    outStr += line + "\n";
  }

  return outStr;

}

uint64_t Core::Util::getTimeMs()
{
  std::chrono::milliseconds epoch = std::chrono::duration_cast< std::chrono::milliseconds >
    ( std::chrono::system_clock::now().time_since_epoch() );
  return epoch.count();
}

int64_t Core::Util::getTimeSeconds()
{
  std::chrono::seconds epoch = std::chrono::seconds( std::time( nullptr ) );
  return epoch.count();
}

uint64_t Core::Util::getEorzeanTimeStamp()
{
  return static_cast< uint64_t >( getTimeSeconds() * 20.571428571428573f );
}

void Core::Util::valueToFlagByteIndexValue( uint32_t inVal, uint8_t& outVal, uint16_t& outIndex )
{
  uint32_t id = inVal;
  outIndex = id / 8;
  uint8_t bitIndex = id % 8;

  outVal = 1 << bitIndex;
}

