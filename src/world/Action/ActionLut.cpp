#include <cassert>
#include "ActionLut.h"

using namespace Sapphire::World::Action;

bool ActionLut::validEntryExists( uint16_t actionId )
{
  auto it = m_actionLut.find( actionId );

  if( it == m_actionLut.end() )
    return false;

  const auto& entry = it->second;

  // if all of these fields are 0, it's not 'valid' due to parse error or no useful data
  return entry.damagePotency != 0 || entry.healPotency != 0 || entry.selfHealPotency != 0 || entry.selfStatus != 0 ||
    entry.targetStatus != 0 || entry.gainMPPercentage != 0 || entry.gainJobResource != 0;
}

const ActionEntry& ActionLut::getEntry( uint16_t actionId )
{
  auto it = m_actionLut.find( actionId );

  assert( it != m_actionLut.end() );

  return it->second;
}