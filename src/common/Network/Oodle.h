#ifndef _OODLE_H
#define _OODLE_H

#include <vector>

#include <oodle2net.h>

namespace Sapphire::Network
{
  class Oodle
  {
  private:
    std::vector< uint8_t > m_state;
    std::vector< uint8_t > m_shared;
    std::vector< uint8_t > m_window;

    int m_htbits;

  public:
    Oodle();
    virtual ~Oodle() = default;

    void oodleInit();
    bool oodleDecode( const std::vector< uint8_t > &enc, uint32_t encSize, std::vector< uint8_t > &dec, uint32_t decSize );
    intptr_t oodleEncode( const std::vector< uint8_t > &raw, uint32_t rawSize, std::vector< uint8_t > &enc );
  };
}

#endif // _OODLE_H