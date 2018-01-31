#ifndef _UTIL_H
#define _UTIL_H

#include <stdint.h>
#include <boost/format.hpp>

namespace Core {
namespace Util {

std::string binaryToHexString( uint8_t* pBinData, uint16_t size );

std::string binaryToHexDump( uint8_t* pBinData, uint16_t size );

uint64_t getTimeMs();

int64_t getTimeSeconds();

uint64_t getEorzeanTimeStamp();

void valueToFlagByteIndexValue( uint32_t inVal, uint8_t& outVal, uint16_t& outIndex );
}
}

#endif
