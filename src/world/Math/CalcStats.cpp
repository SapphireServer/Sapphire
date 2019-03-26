#include <cmath>

#include <Exd/ExdDataGenerated.h>
#include <Common.h>

#include "Actor/Chara.h"

#include "Actor/Player.h"

#include "CalcStats.h"
#include "Framework.h"

using namespace Sapphire::Math;
using namespace Sapphire::Entity;

const int levelTable[71][7] =
{ 
// PIE, MP, MAIN,SUB,DIV,HP,ELMT,THREAT
  { 1, 1, 1, 1, 1, 1, 1 },
  { 50, 104, 20, 56, 56, 0, 52 },
  { 55, 114, 21, 57, 57, 0, 54 },
  { 60, 123, 22, 60, 60, 0, 56 },
  { 65, 133, 24, 62, 62, 0, 58 },
  { 70, 142, 26, 65, 65, 0, 60 },
  { 75, 152, 27, 68, 68, 0, 62 },
  { 80, 161, 29, 70, 70, 0, 64 },
  { 85, 171, 31, 73, 73, 0, 66 },
  { 90, 180, 33, 76, 76, 0, 68 },
  { 95, 190, 35, 78, 78, 0, 70 },
  { 100, 209, 36, 82, 82, 0, 73 },
  { 105, 228, 38, 85, 85, 0, 75 },
  { 110, 247, 41, 89, 89, 0, 78 },
  { 115, 266, 44, 93, 93, 0, 81 },
  { 120, 285, 46, 96, 96, 0, 84 },
  { 125, 304, 49, 100, 100, 0, 86 },
  { 130, 323, 52, 104, 104, 0, 89 },
  { 135, 342, 54, 109, 109, 0, 93 },
  { 140, 361, 57, 113, 113, 0, 95 },
  { 145, 380, 60, 116, 116, 0, 98 },
  { 150, 418, 63, 122, 122, 0, 102 },
  { 155, 456, 67, 127, 127, 0, 105 },
  { 160, 494, 71, 133, 133, 0, 109 },
  { 165, 532, 74, 138, 138, 0, 113 },
  { 170, 570, 78, 144, 144, 0, 117 },
  { 175, 608, 81, 150, 150, 0, 121 },
  { 180, 646, 85, 155, 155, 0, 125 },
  { 185, 684, 89, 162, 162, 0, 129 },
  { 190, 722, 92, 168, 168, 0, 133 },
  { 195, 760, 97, 173, 173, 0, 137 },
  { 200, 826, 101, 181, 181, 0, 143 },
  { 205, 893, 106, 188, 188, 0, 148 },
  { 210, 959, 110, 194, 194, 0, 153 },
  { 215, 1026, 115, 202, 202, 0, 159 },
  { 220, 1092, 119, 209, 209, 0, 165 },
  { 225, 1159, 124, 215, 215, 0, 170 },
  { 230, 1225, 128, 223, 223, 0, 176 },
  { 235, 1292, 134, 229, 229, 0, 181 },
  { 240, 1358, 139, 236, 236, 0, 186 },
  { 245, 1425, 144, 244, 244, 0, 192 },
  { 250, 1548, 150, 253, 253, 0, 200 },
  { 255, 1672, 155, 263, 263, 0, 207 },
  { 260, 1795, 161, 272, 272, 0, 215 },
  { 265, 1919, 166, 283, 283, 0, 223 },
  { 270, 2042, 171, 292, 292, 0, 231 },
  { 275, 2166, 177, 302, 302, 0, 238 },
  { 280, 2289, 183, 311, 311, 0, 246 },
  { 285, 2413, 189, 322, 322, 0, 254 },
  { 290, 2536, 196, 331, 331, 0, 261 },
  { 300, 2660, 202, 341, 341, 1700, 269 },
  { 315, 3000, 204, 342, 393, 1774, 270 },
  { 330, 3380, 205, 344, 444, 1851, 271 },
  { 360, 3810, 207, 345, 496, 1931, 273 },
  { 390, 4300, 209, 346, 548, 2015, 274 },
  { 420, 4850, 210, 347, 600, 2102, 275 },
  { 450, 5470, 212, 349, 651, 2194, 276 },
  { 480, 6170, 214, 350, 703, 2289, 278 },
  { 510, 6950, 215, 351, 755, 2388, 279 },
  { 540, 7840, 217, 352, 806, 2492, 280 },
  { 620, 8840, 218, 354, 858, 2600, 282 },
  { 650, 8980, 224, 355, 941, 2700, 283 },
  { 680, 9150, 228, 356, 1032, 2800, 284 },
  { 710, 9350, 236, 357, 1133, 2900, 286 },
  { 740, 9590, 244, 358, 1243, 3000, 287 },
  { 770, 9870, 252, 359, 1364, 3100, 288 },
  { 800, 10190, 260, 360, 1497, 3200, 290 },
  { 830, 10560, 268, 361, 1643, 3300, 292 },
  { 860, 10980, 276, 362, 1802, 3400, 293 },
  { 890, 11450, 284, 363, 1978, 3500, 294 },
  { 890, 12000, 292, 364, 2170, 3600, 295 } 
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

float CalcStats::calculateBaseStat( PlayerPtr pPlayer )
{
  float base = 0.0f;
  uint8_t level = pPlayer->getLevel();

  if( level > 70 )
    level = 70;

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
  float baseStat = calculateBaseStat( pPlayer );
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

// Leggerless' MP Formula
// ROUNDDOWN(((ROUNDDOWN(((PIE - BaseDET) * PieMPMod/100),0) + BaseMP) * JobModMP / 100),0)

uint32_t CalcStats::calculateMaxMp( PlayerPtr pPlayer, Sapphire::FrameworkPtr pFw )
{
  auto pExdData = pFw->get< Data::ExdDataGenerated >();
  auto classInfo = pExdData->get< Sapphire::Data::ClassJob >( static_cast< uint8_t >( pPlayer->getClass() ) );
  auto paramGrowthInfo = pExdData->get< Sapphire::Data::ParamGrow >( pPlayer->getLevel() );

  if( !classInfo || !paramGrowthInfo )
    return 0;

  auto pieMod = pPlayer->getBonusStat( Common::BaseParam::Piety );

  float baseStat = calculateBaseStat( pPlayer );
  uint16_t piety = pPlayer->getStats().pie + pieMod;
  uint16_t pietyScalar = paramGrowthInfo->mpModifier;
  uint16_t jobModMp = classInfo->modifierManaPoints;
  uint16_t baseMp = paramGrowthInfo->mpModifier;

  uint16_t result = static_cast< uint16_t >( floor( floor( piety - baseStat ) * ( pietyScalar / 100 ) + baseMp ) *
                                             jobModMp / 100 );

  return result;
}

uint16_t CalcStats::calculateMpCost( const Sapphire::Entity::Chara& chara, uint16_t baseCost )
{
  auto level = chara.getLevel();

  // each level range is 1-10, 11-20, 21-30, ... therefore:
  // level 50 should be in the 4th group, not the 5t
  // dividing by 10 on the border will break this unless we subtract 1
  auto levelGroup = std::max< uint8_t >( level - 1, 1 ) / 10;

  float cost = baseCost;

  // thanks to andrew for helping me figure this shit out
  // played with this some more and it seems to be accurate for everything i've tried
  switch( levelGroup )
  {
    // level 1-10
    case 0:
    {
      // r^2 = 0.9999
      cost = 0.0952f * level + 0.9467f;
      break;
    }

    // level 11-20
    case 1:
    {
      // r^2 = 1
      cost = 0.19f * level;
      break;
    }

    // level 21-30
    case 2:
    {
      // r^2 = 1
      cost = 0.38f * level - 3.8f;
      break;
    }

    // level 31-40
    case 3:
    {
      // r^2 = 1
      cost = 0.6652f * level - 12.358f;
      break;
    }

    // level 41-50
    case 4:
    {
      // r^2 = 1
      cost = 1.2352f * level - 35.159f;
      break;
    }

    // level 51-60
    case 5:
    {
      // r^2 = 1
      cost = 0.0654f * std::exp( 0.1201f * level );
      break;
    }

    // level 61-70
    case 6:
    {
      // r^2 = 0.9998
      cost = 0.2313f * ( level * level ) - 26.98f * level + 875.21f;
      break;
    }

    default:
    {
      return 0;
    }
  }

  return static_cast< uint16_t >( std::round( cost * baseCost ) );
}

float CalcStats::blockProbability( const Chara& chara )
{
  auto level = chara.getLevel();
  auto blockRate = static_cast< float >( chara.getBonusStat( Common::BaseParam::BlockRate ) );
  auto levelVal =  static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  return std::floor( ( 30 * blockRate ) / levelVal + 10 );
}

float CalcStats::directHitProbability( const Chara& chara )
{
  const auto& baseStats = chara.getStats();
  auto level = chara.getLevel();

  float dhRate = static_cast< float >( chara.getBonusStat( Common::BaseParam::DirectHitRate ) ) +
                 baseStats.accuracy;

  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );
  auto subVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::SUB ] );

  return std::floor( 550.f * ( dhRate - subVal ) / divVal ) / 10.f;
}

float CalcStats::criticalHitProbability( const Chara& chara )
{
  const auto& baseStats = chara.getStats();
  auto level = chara.getLevel();

  float chRate = static_cast< float >( chara.getBonusStat( Common::BaseParam::CriticalHit ) ) +
                 baseStats.critHitRate;

  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );
  auto subVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::SUB ] );

  return std::floor( 200.f * ( chRate - subVal ) / divVal + 50.f ) / 10.f;
}


float CalcStats::potency( uint16_t potency )
{
  return potency / 100.f;
}

//float CalcStats::weaponDamage( const Sapphire::Entity::Chara& chara, float weaponDamage, bool isMagicDamage )
//{
//  const auto& baseStats = chara.getStats();
//  auto level = chara.getLevel();
//
//  auto mainVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::MAIN ] );
//
//  float jobAttribute = 1.f;
//
//  // todo: fix this
//  return 1.f
//}

// todo: this is all retarded, needs to be per weapon and etcetc
//uint32_t CalcStats::getPrimaryClassJobAttribute( const Sapphire::Entity::Chara& chara )
//{
//
//}

float CalcStats::calcAttackPower( uint32_t attackPower )
{
  return std::floor( ( 125.f * ( attackPower - 292.f ) / 292.f ) + 100.f ) / 100.f;
}

float CalcStats::magicAttackPower( const Sapphire::Entity::Chara& chara )
{
  const auto& baseStats = chara.getStats();

  return calcAttackPower( baseStats.attackPotMagic );
}

float CalcStats::healingMagicPower( const Sapphire::Entity::Chara& chara )
{
  const auto& baseStats = chara.getStats();

  return calcAttackPower( baseStats.healingPotMagic );
}

float CalcStats::attackPower( const Sapphire::Entity::Chara& chara )
{
  const auto& baseStats = chara.getStats();

  return calcAttackPower( baseStats.attack );
}

float CalcStats::determination( const Sapphire::Entity::Chara& chara )
{
  auto level = chara.getLevel();
  const auto& baseStats = chara.getStats();

  auto mainVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::MAIN ] );
  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  return std::floor( 130.f * ( baseStats.determination - mainVal ) / divVal + 1000.f ) / 1000.f;
}

float CalcStats::tenacity( const Sapphire::Entity::Chara& chara )
{
  auto level = chara.getLevel();
  const auto& baseStats = chara.getStats();

  auto subVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::SUB ] );
  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  return std::floor( 100.f * ( baseStats.tenacity - subVal ) / divVal + 1000.f ) / 1000.f;
}

float CalcStats::speed( const Sapphire::Entity::Chara& chara )
{
  auto level = chara.getLevel();
  const auto& baseStats = chara.getStats();

  auto subVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::SUB ] );
  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  uint32_t speedVal = 0;

  // check whether we use spellspeed or skillspeed
  // todo: this is kinda shitty though
  switch( chara.getClass() )
  {
    case Common::ClassJob::Arcanist:
    case Common::ClassJob::Astrologian:
    case Common::ClassJob::Whitemage:
    case Common::ClassJob::Redmage:
    case Common::ClassJob::Bluemage:
    case Common::ClassJob::Blackmage:
    case Common::ClassJob::Summoner:
    case Common::ClassJob::Scholar:
    case Common::ClassJob::Thaumaturge:
      speedVal = baseStats.spellSpeed;
      break;

    default:
      speedVal = baseStats.skillSpeed;
  }

  return std::floor( 130.f * ( speedVal - subVal ) / divVal + 1000.f ) / 1000.f;
}

float CalcStats::criticalHitBonus( const Sapphire::Entity::Chara& chara )
{
  auto level = chara.getLevel();
  const auto& baseStats = chara.getStats();

  auto subVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::SUB ] );
  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  return std::floor( 200.f * ( baseStats.critHitRate - subVal ) / divVal + 1400.f ) / 1000.f;
}

float CalcStats::physicalDefence( const Sapphire::Entity::Chara& chara )
{
  auto level = chara.getLevel();
  const auto& baseStats = chara.getStats();

  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  return std::floor( 15.f * baseStats.defense ) / 100.f;
}

float CalcStats::magicDefence( const Sapphire::Entity::Chara& chara )
{
  auto level = chara.getLevel();
  const auto& baseStats = chara.getStats();

  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  return std::floor( 15.f * baseStats.magicDefense ) / 100.f;
}

//float CalcStats::blockStrength( const Sapphire::Entity::Chara& chara )
//{
//
//}

float CalcStats::healingMagicPotency( const Sapphire::Entity::Chara& chara )
{
  const auto& baseStats = chara.getStats();

  return std::floor( 100.f * ( baseStats.healingPotMagic - 292.f ) / 264.f + 100.f ) / 100.f;
}