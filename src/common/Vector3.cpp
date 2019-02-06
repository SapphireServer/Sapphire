#include "Vector3.h"

inline bool Sapphire::Common::FFXIVARR_POSITION3::operator == ( const FFXIVARR_POSITION3& target ) const
{
  return x == target.x && y == target.y && z == target.z;
}
