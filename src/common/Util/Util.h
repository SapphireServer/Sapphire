#ifndef _UTIL_H
#define _UTIL_H

#include <stdint.h>
#include <string>
#include <functional>
#include <Network/CommonNetwork.h>

namespace Sapphire::Common::Util
{
  // Retrieves the operation code from a raw network packet
  uint16_t getOpCode( Network::Packets::FFXIVARR_PACKET_RAW& raw );

  // Converts binary data to a hexadecimal string representation
  std::string binaryToHexString( uint8_t* pBinData, uint16_t size );

  // Converts binary data to a formatted hexadecimal dump
  std::string binaryToHexDump( uint8_t* pBinData, uint16_t size );

  // Converts an integer value to a hexadecimal string representation with the specified width
  std::string intToHexString( uint64_t intValue, uint8_t width = 2 );

  // Erases all occurrences of the specified character from the input/output string
  void eraseAll( std::string& inOutStr, char remove );

  // Erases all occurrences of any character in the remove string from the input/output string
  void eraseAllIn( std::string& inOutStr, std::string& remove );

  // Returns a lowercase copy of the input string
  std::string toLowerCopy( const std::string& inStr );

  // Formats the current UTC time according to the given format string
  std::string fmtUtcTime( const std::string& fmt );

  // Gets the current time in milliseconds
  uint64_t getTimeMs();

  /*!
   * Gets the current time in seconds
   * @brief Get a POSIX epoch representation of the current time
   * @return 32-bit unsigned integer
   */
  uint32_t getTimeSeconds();

  // Gets the current Eorzean timestamp (used in the game world)
  uint64_t getEorzeanTimeStamp();

  // Converts a value to a flag byte index value pair
  void valueToFlagByteIndexValue( uint32_t inVal, uint8_t& outVal, uint16_t& outIndex );

  template< class T >
  inline void hashCombine( std::size_t& seed, const T& v )
  {
    std::hash< T > hasher;
    seed ^= hasher( v ) + 0x9e3779b9 + ( seed << 6 ) + ( seed >> 2 );
  }

}

#endif
