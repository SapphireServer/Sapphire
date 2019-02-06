#include "Vector3.h"

inline bool Sapphire::Common::FFXIVARR_POSITION3::operator == ( const FFXIVARR_POSITION3 & target ) const
{
    return ( this->x == target.x && this->y == target.y && this->z == target.z );
}
