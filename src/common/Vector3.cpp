#include "Vector3.h"

using namespace Sapphire::Common;

inline bool FFXIVARR_POSITION3::operator == ( const FFXIVARR_POSITION3& target ) const
{
  return x == target.x && y == target.y && z == target.z;
}

FFXIVARR_POSITION3 FFXIVARR_POSITION3::operator - ( const FFXIVARR_POSITION3& target ) const
{
  return FFXIVARR_POSITION3{ x - target.x, y - target.y, z - target.z };
}

inline bool Vector3::operator == ( const Vector3& target ) const
{
  return x == target.x && y == target.y && z == target.z && reserve == target.reserve;
}

Vector3 Vector3::operator - ( const Vector3& target ) const
{
  return Vector3{ x - target.x, y - target.y, z - target.z };
}
