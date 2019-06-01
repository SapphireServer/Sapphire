#include <cassert>
#include "ActionLut.h"

using namespace Sapphire::World::Action;

bool ActionLut::validEntryExists( uint16_t actionId )
{
  auto it = m_actionLut.find( actionId );

  if( it == m_actionLut.end() )
    return false;

  const auto& entry = it->second;

  // if all of the fields are 0, it's not 'valid' due to parse error or no useful data in the tooltip
  return entry.potency != 0 || entry.comboPotency != 0 || entry.flankPotency != 0 || entry.frontPotency != 0 ||
         entry.rearPotency != 0 || entry.curePotency != 0;
}

const ActionEntry& ActionLut::getEntry( uint16_t actionId )
{
  auto it = m_actionLut.find( actionId );

  assert( it != m_actionLut.end() );

  return it->second;
}