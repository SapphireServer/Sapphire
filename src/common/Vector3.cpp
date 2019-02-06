#include <string.h> 

#include "Vector3.h"

inline bool Sapphire::Common::FFXIVARR_POSITION3::operator == ( const FFXIVARR_POSITION3& target ) const
{
  return !memcmp( this, &target, sizeof( FFXIVARR_POSITION3 ) );
}
