#ifndef _MD52_H
#define _MD52_H

#include <stdint.h>

namespace Sapphire::Util
{
  using md5_context = struct
  {
    uint32_t total[2];
    uint32_t state[4];
    uint8_t buffer[64];
  };


  void md5( uint8_t* text, uint8_t* hash, int32_t size );

  void md5_starts( md5_context* ctx );

  void md5_update( md5_context* ctx, uint8_t* input, uint32_t length );

  void md5_finish( md5_context* ctx, uint8_t digest[16] );

  static const char* msg[] =
  {
    "",
    "a",
    "abc",
    "message digest",
    "abcdefghijklmnopqrstuvwxyz",
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
    "12345678901234567890123456789012345678901234567890123456789012345678901234567890"
  };

  static const char* val[] =
  {
    "d41d8cd98f00b204e9800998ecf8427e",
    "0cc175b9c0f1b6a831c399e269772661",
    "900150983cd24fb0d6963f7d28e17f72",
    "f96b697d7cb7938d525a2f31aaf161d0",
    "c3fcd3d76192e4007dfb496cca67e13b",
    "d174ab98d277d9f5a5611c2c9f419d9f",
    "57edf4a22be3c955ac49da2e2107b67a"
  };

}



#endif /* md5.h */
