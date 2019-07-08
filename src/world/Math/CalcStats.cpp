#include <cmath>

#include <Exd/ExdDataGenerated.h>
#include <Common.h>
#include <Logging/Logger.h>

#include "Actor/Chara.h"
#include "Actor/Player.h"

#include "Inventory/Item.h"

#include "CalcStats.h"
#include "Framework.h"

using namespace Sapphire::Math;
using namespace Sapphire::Entity;

const int levelTable[81][5] =
{ 
  // MAIN,SUB,DIV,HP,ELMT,THREAT
  { 1, 1, 1, 1, 1 },
  { 20, 56, 56, 0, 52 },
  { 21, 57, 57, 0, 54 },
  { 22, 60, 60, 0, 56 },
  { 24, 62, 62, 0, 58 },
  { 26, 65, 65, 0, 60 },
  { 27, 68, 68, 0, 62 },
  { 29, 70, 70, 0, 64 },
  { 31, 73, 73, 0, 66 },
  { 33, 76, 76, 0, 68 },
  { 35, 78, 78, 0, 70 },
  { 36, 82, 82, 0, 73 },
  { 38, 85, 85, 0, 75 },
  { 41, 89, 89, 0, 78 },
  { 44, 93, 93, 0, 81 },
  { 46, 96, 96, 0, 84 },
  { 49, 100, 100, 0, 86 },
  { 52, 104, 104, 0, 89 },
  { 54, 109, 109, 0, 93 },
  { 57, 113, 113, 0, 95 },
  { 60, 116, 116, 0, 98 },
  { 63, 122, 122, 0, 102 },
  { 67, 127, 127, 0, 105 },
  { 71, 133, 133, 0, 109 },
  { 74, 138, 138, 0, 113 },
  { 78, 144, 144, 0, 117 },
  { 81, 150, 150, 0, 121 },
  { 85, 155, 155, 0, 125 },
  { 89, 162, 162, 0, 129 },
  { 92, 168, 168, 0, 133 },
  { 97, 173, 173, 0, 137 },
  { 101, 181, 181, 0, 143 },
  { 106, 188, 188, 0, 148 },
  { 110, 194, 194, 0, 153 },
  { 115, 202, 202, 0, 159 },
  { 119, 209, 209, 0, 165 },
  { 124, 215, 215, 0, 170 },
  { 128, 223, 223, 0, 176 },
  { 134, 229, 229, 0, 181 },
  { 139, 236, 236, 0, 186 },
  { 144, 244, 244, 0, 192 },
  { 150, 253, 253, 0, 200 },
  { 155, 263, 263, 0, 207 },
  { 161, 272, 272, 0, 215 },
  { 166, 283, 283, 0, 223 },
  { 171, 292, 292, 0, 231 },
  { 177, 302, 302, 0, 238 },
  { 183, 311, 311, 0, 246 },
  { 189, 322, 322, 0, 254 },
  { 196, 331, 331, 0, 261 },
  { 202, 341, 341, 1700, 269 },
  { 204, 342, 393, 1774, 270 },
  { 205, 344, 444, 1851, 271 },
  { 207, 345, 496, 1931, 273 },
  { 209, 346, 548, 2015, 274 },
  { 210, 347, 600, 2102, 275 },
  { 212, 349, 651, 2194, 276 },
  { 214, 350, 703, 2289, 278 },
  { 215, 351, 755, 2388, 279 },
  { 217, 352, 806, 2492, 280 },
  { 218, 354, 858, 2600, 282 },
  { 224, 355, 941, 2700, 283 },
  { 228, 356, 1032, 2800, 284 },
  { 236, 357, 1133, 2900, 286 },
  { 244, 358, 1243, 3000, 287 },
  { 252, 359, 1364, 3100, 288 },
  { 260, 360, 1497, 3200, 290 },
  { 268, 361, 1643, 3300, 292 },
  { 276, 362, 1802, 3400, 293 },
  { 284, 363, 1978, 3500, 294 },
  { 292, 364, 2170, 3600, 295 },

  // todo: add proper shbr values
  // sub/div added from http://theoryjerks.akhmorning.com/resources/levelmods/
  { 292, 365, 2263, 3600, 295 },
  { 292, 366, 2360, 3600, 295 },
  { 292, 367, 2461, 3600, 295 },
  { 292, 368, 2566, 3600, 295 },
  { 292, 370, 2676, 3600, 295 },
  { 292, 372, 2790, 3600, 295 },
  { 292, 374, 2910, 3600, 295 },
  { 292, 376, 3034, 3600, 295 },
  { 292, 378, 3164, 3600, 295 },
  { 292, 380, 3300, 3600, 295 },
};

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

float CalcStats::calculateBaseStat( const Chara& chara )
{
  float base = 0.0f;
  uint8_t level = chara.getLevel();

  if( level > Common::MAX_PLAYER_LEVEL )
    level = Common::MAX_PLAYER_LEVEL;

  return static_cast< float >( levelTable[level][2] );
}

// Leggerless' HP Formula
// ROUNDDOWN(JobModHP * (BaseHP / 100)) + ROUNDDOWN(VitHPMod / 100 * (VIT - BaseDET))

uint32_t CalcStats::calculateMaxHp( PlayerPtr pPlayer, Sapphire::FrameworkPtr pFw )
{
  auto pExdData = pFw->get< Data::ExdDataGenerated >();
  // TODO: Replace ApproxBaseHP with something that can get us an accurate BaseHP.
  // Is there any way to pull reliable BaseHP without having to manually use a pet for every level, and using the values from a table?
  // More info here: https://docs.google.com/spreadsheets/d/1de06KGT0cNRUvyiXNmjNgcNvzBCCQku7jte5QxEQRbs/edit?usp=sharing

  auto classInfo = pExdData->get< Sapphire::Data::ClassJob >( static_cast< uint8_t >( pPlayer->getClass() ) );
  auto paramGrowthInfo = pExdData->get< Sapphire::Data::ParamGrow >( pPlayer->getLevel() );

  if( !classInfo || !paramGrowthInfo )
    return 0;

  uint8_t level = pPlayer->getLevel();

  auto vitMod = pPlayer->getBonusStat( Common::BaseParam::Vitality );
  float baseStat = calculateBaseStat( *pPlayer );
  uint16_t vitStat = pPlayer->getStats().vit + static_cast< uint16_t >( vitMod );
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

float CalcStats::blockProbability( const Chara& chara )
{
  auto level = chara.getLevel();
  auto blockRate = static_cast< float >( chara.getStatValue( Common::BaseParam::BlockRate ) );
  auto levelVal =  static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  return std::floor( ( 30 * blockRate ) / levelVal + 10 );
}

float CalcStats::directHitProbability( const Chara& chara )
{
  const auto& baseStats = chara.getStats();
  auto level = chara.getLevel();

  float dhRate = chara.getStatValue( Common::BaseParam::DirectHitRate );

  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );
  auto subVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::SUB ] );

  return std::floor( 550.f * ( dhRate - subVal ) / divVal ) / 10.f;
}

float CalcStats::criticalHitProbability( const Chara& chara )
{
  const auto& baseStats = chara.getStats();
  auto level = chara.getLevel();

  float chRate = chara.getStatValue( Common::BaseParam::CriticalHit );

  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );
  auto subVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::SUB ] );

  return std::floor( 200.f * ( chRate - subVal ) / divVal + 50.f ) / 10.f;
}


float CalcStats::potency( uint16_t potency )
{
  return potency / 100.f;
}

float CalcStats::autoAttackPotency( const Sapphire::Entity::Chara& chara )
{
  uint32_t aaPotency = AUTO_ATTACK_POTENCY;

  // check if ranged class
  switch( chara.getClass() )
  {
    case Common::ClassJob::Machinist:
    case Common::ClassJob::Bard:
    case Common::ClassJob::Archer:
      aaPotency = RANGED_AUTO_ATTACK_POTENCY;

    default:
      break;
  }

  float autoAttackDelay = 2.5f;
  // fetch actual auto attack delay if its a player
  if( chara.isPlayer() )
  {
    // todo: ew
    auto pPlayer = const_cast< Entity::Chara& >( chara ).getAsPlayer();
    assert( pPlayer );

    auto pItem = pPlayer->getEquippedWeapon();
    assert( pItem );

    autoAttackDelay = pItem->getDelay() / 1000.f;
  }

  // factors in f(PTC) in order to not lose precision
  return std::floor( aaPotency / 3.f * autoAttackDelay ) / 100.f;
}

float CalcStats::weaponDamage( const Sapphire::Entity::Chara& chara, float weaponDamage )
{
  const auto& baseStats = chara.getStats();
  auto level = chara.getLevel();

  auto mainVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::MAIN ] );

  uint32_t jobAttribute = 1;

  switch( chara.getPrimaryStat() )
  {
    case Common::BaseParam::Intelligence:
    {
      jobAttribute = baseStats.healingPotMagic;
      break;
    }
    case Common::BaseParam::Mind:
    {
      jobAttribute = baseStats.attackPotMagic;
      break;
    }

    default:
    {
      jobAttribute = baseStats.attack;
      break;
    }
  }

  return std::floor( ( ( mainVal * jobAttribute ) / 1000.f ) + weaponDamage );
}

float CalcStats::calcAttackPower( const Sapphire::Entity::Chara& chara, uint32_t attackPower )
{
  auto level = chara.getLevel();
  auto mainVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::MAIN ] );
  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  // todo: not sure if its ( ap - mv ) / mv or ( ap - mv ) / dv
  return std::floor( ( 125.f * ( attackPower - mainVal ) / divVal ) + 100.f ) / 100.f;
}

float CalcStats::getPrimaryAttackPower( const Sapphire::Entity::Chara& chara )
{
  const auto& baseStats = chara.getStats();

  switch( chara.getPrimaryStat() )
  {
    case Common::BaseParam::Mind:
    {
      return healingMagicPower( chara );
    }
    case Common::BaseParam::Intelligence:
    {
      return magicAttackPower( chara );
    }

    default:
    {
      return attackPower( chara );
    }
  }
}

float CalcStats::attackPower( const Sapphire::Entity::Chara& chara )
{
  return calcAttackPower( chara, chara.getStatValue( Common::BaseParam::AttackPower ) );
}

float CalcStats::magicAttackPower( const Sapphire::Entity::Chara& chara )
{
  return calcAttackPower( chara, chara.getStatValue( Common::BaseParam::AttackMagicPotency ) );
}

float CalcStats::healingMagicPower( const Sapphire::Entity::Chara& chara )
{
  return calcAttackPower( chara, chara.getStatValue( Common::BaseParam::HealingMagicPotency ) );
}

float CalcStats::determination( const Sapphire::Entity::Chara& chara )
{
  auto level = chara.getLevel();

  auto mainVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::MAIN ] );
  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  return std::floor( 130.f * ( chara.getStatValue( Common::BaseParam::Determination ) - mainVal ) / divVal + 1000.f ) / 1000.f;
}

float CalcStats::tenacity( const Sapphire::Entity::Chara& chara )
{
  auto level = chara.getLevel();

  auto subVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::SUB ] );
  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  return std::floor( 100.f * ( chara.getStatValue( Common::BaseParam::Tenacity ) - subVal ) / divVal + 1000.f ) / 1000.f;
}

float CalcStats::speed( const Sapphire::Entity::Chara& chara )
{
  auto level = chara.getLevel();

  auto subVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::SUB ] );
  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  uint32_t speedVal = 0;

  // check whether we use spellspeed or skillspeed
  switch( chara.getPrimaryStat() )
  {
    case Common::BaseParam::Intelligence:
    case Common::BaseParam::Mind:
      speedVal = chara.getStatValue( Common::BaseParam::SpellSpeed );
      break;

    default:
      speedVal = chara.getStatValue( Common::BaseParam::SkillSpeed );
  }

  return std::floor( 130.f * ( speedVal - subVal ) / divVal + 1000.f ) / 1000.f;
}

float CalcStats::criticalHitBonus( const Sapphire::Entity::Chara& chara )
{
  auto level = chara.getLevel();

  auto subVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::SUB ] );
  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  return std::floor( 200.f * ( chara.getStatValue( Common::BaseParam::CriticalHit ) - subVal ) / divVal + 1400.f ) / 1000.f;
}

float CalcStats::physicalDefence( const Sapphire::Entity::Chara& chara )
{
  auto level = chara.getLevel();

  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  return std::floor( 15.f * chara.getStatValue( Common::BaseParam::Defense ) ) / 100.f;
}

float CalcStats::magicDefence( const Sapphire::Entity::Chara& chara )
{
  auto level = chara.getLevel();

  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  return std::floor( 15.f * chara.getStatValue( Common::BaseParam::MagicDefense ) ) / 100.f;
}

float CalcStats::blockStrength( const Sapphire::Entity::Chara& chara )
{
  auto level = chara.getLevel();
  auto blockStrength = static_cast< float >( chara.getBonusStat( Common::BaseParam::BlockStrength ) );
  auto levelVal =  static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  return std::floor( ( 30 * blockStrength ) / levelVal + 10 ) / 100.f;
}

float CalcStats::autoAttack( const Sapphire::Entity::Chara& chara )
{
  // todo: default values for NPCs, not sure what we should have here
  float autoAttackDelay = 2.f;
  float weaponDamage = 10.f;

  // fetch actual auto attack delay if its a player
  if( chara.isPlayer() )
  {
    // todo: ew
    auto pPlayer = const_cast< Entity::Chara& >( chara ).getAsPlayer();
    assert( pPlayer );

    auto pItem = pPlayer->getEquippedWeapon();
    assert( pItem );

    autoAttackDelay = pItem->getDelay() / 1000.f;
    weaponDamage = pItem->getWeaponDmg();
  }

  auto level = chara.getLevel();
  auto mainVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::MAIN ] );

  auto innerCalc = std::floor( ( mainVal * primaryStatValue( chara ) / 1000.f ) + weaponDamage );

  return std::floor( innerCalc * ( autoAttackDelay / 3.f ) );
}

float CalcStats::healingMagicPotency( const Sapphire::Entity::Chara& chara )
{
  return std::floor( 100.f * ( chara.getStatValue( Common::BaseParam::HealingMagicPotency ) - 292.f ) / 264.f + 100.f ) / 100.f;
}

float CalcStats::calculateAutoAttackDamage( const Sapphire::Entity::Chara& chara )
{
  // D = ⌊ f(ptc) × f(aa) × f(ap) × f(det) × f(tnc) × traits ⌋ × f(ss) ⌋ ×
  // f(chr) ⌋ × f(dhr) ⌋ × rand[ 0.95, 1.05 ] ⌋ × buff_1 ⌋ × buff... ⌋

  auto pot = autoAttackPotency( chara );
  auto aa = autoAttack( chara );
  auto ap = getPrimaryAttackPower( chara );
  auto det = determination( chara );
  auto ten = tenacity( chara );

  Logger::debug( "auto attack: pot: {} aa: {} ap: {} det: {} ten: {}", pot, aa, ap, det, ten );

  auto factor = std::floor( pot * aa * ap * det * ten );

  // todo: traits

  factor = std::floor( factor * speed( chara ) );

  // todo: surely this aint right?
  //factor = std::floor( factor * criticalHitProbability( chara ) );
  //factor = std::floor( factor * directHitProbability( chara ) );

  // todo: random 0.95 - 1.05 factor

  // todo: buffs

  return factor;
}

uint32_t CalcStats::primaryStatValue( const Sapphire::Entity::Chara& chara )
{
  return chara.getStatValue( chara.getPrimaryStat() );
}