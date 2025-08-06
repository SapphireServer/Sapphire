#include "ActionShapeLut.h"
#include <cassert>

using namespace Sapphire;
using namespace Sapphire::World::Action;

bool ActionShapeLut::validConeEntryExists( uint16_t actionId )
{
  auto it = m_coneLut.find( actionId );

  if( it == m_coneLut.end() )
    return false;

  const auto& entry = it->second;

  // if all of the fields are 0, it's not 'valid' due to parse error or no useful data
  return entry.startAngle != 0 || entry.endAngle != 0;
}

const ConeEntry& ActionShapeLut::getConeEntry( uint16_t actionId )
{
  auto it = m_coneLut.find( actionId );

  assert( it != m_coneLut.end() );

  return it->second;
}