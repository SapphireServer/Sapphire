#include "ExdData.h"

bool Data::ExdData::init( const std::string& path )
{
  m_data = std::make_shared< xivps3::dat::GameData >( path );

  if( !m_data )
  {
    return false;
  }

  m_exd_data = std::make_shared< xivps3::exd::ExdData >( *m_data );

  if( !m_exd_data )
  {
    return false;
  }

  return true;
}

