#include "ExdData.h"

using namespace Sapphire;

bool Data::ExdData::init( const std::string& path )
{
  m_data = std::make_shared< xiv::dat::GameData >( path );

  if( !m_data )
  {
    return false;
  }

  m_exd_data = std::make_shared< xiv::exd::ExdData >( *m_data );

  if( !m_exd_data )
  {
    return false;
  }

  return true;
}

