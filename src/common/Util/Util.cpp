#include "Util.h"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <string>

std::string Sapphire::Util::binaryToHexString( uint8_t* pBinData, uint16_t size )
{
  std::string outStr;

  for( uint32_t i = 0; i < size; i++ )
  {
    outStr += Util::intToHexString( static_cast< int8_t>( pBinData[ i ] & 0xFF ) );
  }

  return outStr;

}
std::string Sapphire::Util::toLowerCopy( const std::string& inStr )
{
  std::string out = inStr;
  std::transform( inStr.begin(), inStr.end(), out.begin(), [](unsigned char c) -> unsigned char { return ::tolower(c); });
  return out;
}

void Sapphire::Util::eraseAll( std::string& inOutStr, char remove )
{
  inOutStr.erase( std::remove( inOutStr.begin(), inOutStr.end(), remove ), inOutStr.end() );
}

void Sapphire::Util::eraseAllIn( std::string& inOutStr, std::string& remove )
{
  for( auto rem : remove )
    inOutStr.erase( std::remove( inOutStr.begin(), inOutStr.end(), rem ), inOutStr.end() );
}


std::string Sapphire::Util::intToHexString( uint64_t intValue, uint8_t width )
{
    std::string hexStr;

    /// integer value to hex-string
    std::stringstream sstream;
    sstream << std::setfill ('0') << std::setw( width )
            << std::hex << intValue;

    hexStr = sstream.str();
    sstream.clear();

    return hexStr;
}

std::string Sapphire::Util::binaryToHexDump( uint8_t* pBinData, uint16_t size )
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

uint64_t Sapphire::Util::getTimeMs()
{
  std::chrono::milliseconds epoch = std::chrono::duration_cast< std::chrono::milliseconds >
    ( std::chrono::system_clock::now().time_since_epoch() );
  return epoch.count();
}

uint32_t Sapphire::Util::getTimeSeconds()
{
  auto currClock = std::chrono::system_clock::now();
  return std::chrono::time_point_cast< std::chrono::seconds >( currClock ).time_since_epoch().count();
}

uint64_t Sapphire::Util::getEorzeanTimeStamp()
{
  return static_cast< uint64_t >( getTimeSeconds() * 20.571428571428573f );
}

void Sapphire::Util::valueToFlagByteIndexValue( uint32_t inVal, uint8_t& outVal, uint16_t& outIndex )
{
  uint32_t id = inVal;
  outIndex = id / 8;
  uint8_t bitIndex = id % 8;

  outVal = 1 << bitIndex;
}

