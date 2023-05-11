#include "Oodle.h"

using namespace Sapphire;

Network::Oodle::Oodle() :
  m_htbits(17)
{
  auto stateSize = OodleNetwork1TCP_State_Size();
  auto sharedSize = OodleNetwork1_Shared_Size( m_htbits );

  m_state = std::vector< uint8_t >( stateSize, 0 );
  m_shared = std::vector< uint8_t >( sharedSize, 0 );
  m_window = std::vector< uint8_t >( 0x100000, 0 );

  oodleInit();
}

void Network::Oodle::oodleInit()
{
  OodleNetwork1_Shared_SetWindow( &m_shared[0], m_htbits, &m_window[0], (int) m_window.size() );
  OodleNetwork1TCP_Train( &m_state[0], &m_shared[0], nullptr, nullptr, 0 );
}

bool Network::Oodle::oodleDecode( const std::vector< uint8_t > &enc, uint32_t encSize, std::vector< uint8_t > &dec, uint32_t decSize )
{
  return OodleNetwork1TCP_Decode( &m_state[0], &m_shared[0], &enc[0], encSize, &dec[0], decSize );
}

intptr_t Network::Oodle::oodleEncode( const std::vector< uint8_t > &dec, uint32_t decSize, std::vector< uint8_t > &enc )
{
    return OodleNetwork1TCP_Encode( &m_state[0], &m_shared[0], &dec[0], decSize, &enc[0] );
}