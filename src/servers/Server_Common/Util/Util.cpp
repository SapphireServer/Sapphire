#include "Util.h"
#include <chrono>

std::string Core::Util::binaryToHexString( uint8_t* pBinData, uint16_t size )
{

   std::string outStr;

   for( uint32_t i = 0; i < size; i++ )
   {
      outStr += boost::str( boost::format( "%|02X|" ) % ( int32_t ) ( pBinData[i] & 0xFF ) );
   }

   return outStr;

}

uint64_t Core::Util::getTimeMs()
{
   std::chrono::milliseconds epoch = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
   return epoch.count();
}

uint64_t Core::Util::getTimeSeconds()
{
   std::chrono::seconds epoch = std::chrono::duration_cast< std::chrono::seconds >(std::chrono::system_clock::now().time_since_epoch());
   return epoch.count();
}

uint64_t Core::Util::getEorzeanTimeStamp()
{
   std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
   auto now = std::chrono::time_point_cast< std::chrono::seconds >( t1 ).time_since_epoch().count();

   return static_cast< uint64_t >( now * 20.571428571428573f );
}

void Core::Util::valueToFlagByteIndexValue( uint32_t inVal, uint8_t& outVal, uint16_t& outIndex )
{
   uint32_t id = inVal;
   outIndex = id / 8;
   uint8_t bitIndex = id % 8;

   outVal = 1 << bitIndex;
}

