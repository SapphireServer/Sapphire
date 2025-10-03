#include "ActionShapeLut.h"
#include <cassert>

using namespace Sapphire;
using namespace Sapphire::World::Action;

bool ActionShapeLut::validConeEntryExists( uint16_t actionId )
{
  auto& map = lut();
  auto it = map.find( actionId );

  if( it == map.end() )
    return false;

  const auto& entry = it->second;

  // if all of the fields are 0, it's not 'valid' due to parse error or no useful data
  return entry.startAngle != 0 || entry.endAngle != 0;
}

const ConeEntry& ActionShapeLut::getConeEntry( uint16_t actionId )
{
  auto& map = lut();
  auto it = map.find( actionId );

  assert( it != map.end() );

  return it->second;
}
