#ifndef _UTIL_H
#define _UTIL_H

#include <stdint.h>
#include <string>
#include <functional>

namespace Sapphire::Common::Util
{

  std::string binaryToHexString( uint8_t* pBinData, uint16_t size );

  std::string binaryToHexDump( uint8_t* pBinData, uint16_t size );

  std::string intToHexString( uint64_t intValue, uint8_t width = 2 );

  void eraseAll( std::string& inOutStr, char remove );
  void eraseAllIn( std::string& inOutStr, std::string& remove );

  std::string toLowerCopy( const std::string& inStr );

  std::string fmtUtcTime( const std::string& fmt );

  uint64_t getTimeMs();

  /*!
   * @brief Get a POSIX epoch representation of the current time
   * @return 32-bit unsigned integer
   */

  uint32_t getTimeSeconds();

  uint64_t getEorzeanTimeStamp();

  void valueToFlagByteIndexValue( uint32_t inVal, uint8_t& outVal, uint16_t& outIndex );

  template< class T >
  inline void hashCombine( std::size_t& seed, const T& v )
  {
      std::hash< T > hasher;
      seed ^= hasher( v ) + 0x9e3779b9 + ( seed << 6 ) + ( seed >> 2 );
  }

}

#endif
