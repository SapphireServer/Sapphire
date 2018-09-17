#include <cmath>

#include <Exd/ExdDataGenerated.h>
#include <Common.h>

#include "Actor/Chara.h"

#include "Actor/Player.h"

#include "CalcStats.h"
#include "Framework.h"

using namespace Core::Math;
using namespace Core::Entity;

extern Core::Framework g_fw;

/*
   Class used for battle-related formulas and calculations.
   Big thanks to the Theoryjerks group!

   NOTE:
   Formulas here shouldn't be considered final. It's possible that the formula it was based on is correct but 
   wasn't implemented correctly here, or approximated things due to limited knowledge of how things work in retail.
   It's also possible that we're using formulas that were correct for previous patches, but not the current version.

   TODO:

   Base HP val modifier. I can only find values for levels 50~70.
   Dereferencing the actor (Player right now) for stats seem meh, perhaps consider a structure purely for stats?
   Reduce repeated code (more specifically the data we pull from exd)
*/

// 3 Versions. SB and HW are linear, ARR is polynomial.
// Originally from Player.cpp, calculateStats().

float CalcStats::calculateBaseStat( PlayerPtr pPlayer )
{
  float base = 0.0f;
  uint8_t level = pPlayer->getLevel();

  // SB Base Stat Formula  (Aligned)
  if( level > 60 )
  {
    base = static_cast< float >( ( ( ( level == 61 ) ? 224 : 220 ) + ( level - 61 ) * 8 ) );
  }
    // HW Base Stat Formula  (Aligned)
  else if( level > 50 )
    base = 1.63f * level + 121.02f;
    // ARR Base Stat Formula (Off by one in several cases)
  else
    base = 0.052602f * ( level * level ) + ( 1.0179f * level ) + 19.6f;

  return base;
}

// Leggerless' HP Formula
// ROUNDDOWN(JobModHP * (BaseHP / 100)) + ROUNDDOWN(VitHPMod / 100 * (VIT - BaseDET))

uint32_t CalcStats::calculateMaxHp( PlayerPtr pPlayer )
{
  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  // TODO: Replace ApproxBaseHP with something that can get us an accurate BaseHP.
  // Is there any way to pull reliable BaseHP without having to manually use a pet for every level, and using the values from a table?
  // More info here: https://docs.google.com/spreadsheets/d/1de06KGT0cNRUvyiXNmjNgcNvzBCCQku7jte5QxEQRbs/edit?usp=sharing

  auto classInfo = pExdData->get< Core::Data::ClassJob >( static_cast< uint8_t >( pPlayer->getClass() ) );
  auto paramGrowthInfo = pExdData->get< Core::Data::ParamGrow >( pPlayer->getLevel() );

  if( !classInfo || !paramGrowthInfo )
    return 0;

  uint8_t level = pPlayer->getLevel();

  float baseStat = calculateBaseStat( pPlayer );
  uint16_t vitStat = pPlayer->getStats().vit;
  uint16_t hpMod = paramGrowthInfo->hpModifier;
  uint16_t jobModHp = classInfo->modifierHitPoints;
  float approxBaseHp = 0.0f; // Read above

  // These values are not precise.

  if( level >= 60 )
    approxBaseHp = static_cast< float >( 2600 + ( level - 60 ) * 100 );
  else if( level >= 50 )
    approxBaseHp = 1700 + ( ( level - 50 ) * ( 1700 * 1.04325f ) );
  else
    approxBaseHp = paramGrowthInfo->mpModifier * 0.7667f;

  uint16_t result = static_cast< uint16_t >( floor( jobModHp * ( approxBaseHp / 100.0f ) ) +
                                             floor( hpMod / 100.0f * ( vitStat - baseStat ) ) );

  return result;
}

// Leggerless' MP Formula
// ROUNDDOWN(((ROUNDDOWN(((PIE - BaseDET) * PieMPMod/100),0) + BaseMP) * JobModMP / 100),0)

uint32_t CalcStats::calculateMaxMp( PlayerPtr pPlayer )
{
  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  auto classInfo = pExdData->get< Core::Data::ClassJob >( static_cast< uint8_t >( pPlayer->getClass() ) );
  auto paramGrowthInfo = pExdData->get< Core::Data::ParamGrow >( pPlayer->getLevel() );

  if( !classInfo || !paramGrowthInfo )
    return 0;

  float baseStat = calculateBaseStat( pPlayer );
  uint16_t piety = pPlayer->getStats().pie;
  uint16_t pietyScalar = paramGrowthInfo->mpModifier;
  uint16_t jobModMp = classInfo->modifierManaPoints;
  uint16_t baseMp = paramGrowthInfo->mpModifier;

  uint16_t result = static_cast< uint16_t >( floor( floor( piety - baseStat ) * ( pietyScalar / 100 ) + baseMp ) *
                                             jobModMp / 100 );

  return result;
}
