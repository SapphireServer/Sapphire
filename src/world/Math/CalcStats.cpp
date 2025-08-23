#include <cmath>

#include <Exd/ExdData.h>
#include <Common.h>
#include <Logging/Logger.h>
#include <Service.h>

#include "Actor/Chara.h"
#include "Actor/Player.h"
#include "Util/UtilMath.h"

#include "Inventory/Item.h"

#include "CalcStats.h"

#include "Manager/PlayerMgr.h"

using namespace Sapphire::Math;
using namespace Sapphire::Entity;
using namespace Sapphire::World::Manager;

const int levelTable[61][6] =
{
  // MAIN,SUB,DIV,HP,ELMT,THREAT
  { 1, 1, 1, 1, 1, 1 },
  { 20, 56, 56, 86, 52, 2 },
  { 21, 57, 57, 101, 54, 2 },
  { 22, 60, 60, 109, 56, 3 },
  { 24, 62, 62, 116, 58, 3 },
  { 26, 65, 65, 123, 60, 3 },
  { 27, 68, 68, 131, 62, 3 },
  { 29, 70, 70, 138, 64, 4 },
  { 31, 73, 73, 145, 66, 4 },
  { 33, 76, 76, 153, 68, 4 },
  { 35, 78, 78, 160, 70, 5 },
  { 36, 82, 82, 174, 73, 5 },
  { 38, 85, 85, 188, 75, 5 },
  { 41, 89, 89, 202, 78, 6 },
  { 44, 93, 93, 216, 81, 6 },
  { 46, 96, 96, 230, 84, 7 },
  { 49, 100, 100, 244, 86, 7 },
  { 52, 104, 104, 258, 89, 8 },
  { 54, 109, 109, 272, 93, 9 },
  { 57, 113, 113, 286, 95, 9 },
  { 60, 116, 116, 300, 98, 10 },
  { 63, 122, 122, 333, 102, 10 },
  { 67, 127, 127, 366, 105, 11 },
  { 71, 133, 133, 399, 109, 12 },
  { 74, 138, 138, 432, 113, 13 },
  { 78, 144, 144, 465, 117, 14 },
  { 81, 150, 150, 498, 121, 15 },
  { 85, 155, 155, 531, 125, 16 },
  { 89, 162, 162, 564, 129, 17 },
  { 92, 168, 168, 597, 133, 18 },
  { 97, 173, 173, 630, 137, 19 },
  { 101, 181, 181, 669, 143, 20 },
  { 106, 188, 188, 708, 148, 22 },
  { 110, 194, 194, 747, 153, 23 },
  { 115, 202, 202, 786, 159, 25 },
  { 119, 209, 209, 825, 165, 27 },
  { 124, 215, 215, 864, 170, 29 },
  { 128, 223, 223, 903, 176, 31 },
  { 134, 229, 229, 942, 181, 33 },
  { 139, 236, 236, 981, 186, 35 },
  { 144, 244, 244, 1020, 192, 38 },
  { 150, 253, 253, 1088, 200, 40 },
  { 155, 263, 263, 1156, 207, 43 },
  { 161, 272, 272, 1224, 215, 46 },
  { 166, 283, 283, 1292, 223, 49 },
  { 171, 292, 292, 1360, 231, 52 },
  { 177, 302, 302, 1428, 238, 55 },
  { 183, 311, 311, 1496, 246, 58 },
  { 189, 322, 322, 1564, 254, 62 },
  { 196, 331, 331, 1632, 261, 66 },
  { 202, 341, 341, 1700, 269, 70 },
  { 204, 342, 393, 1774, 270, 84 },
  { 205, 344, 444, 1851, 271, 99 },
  { 207, 345, 496, 1931, 273, 113 },
  { 209, 346, 548, 2015, 274, 128 },
  { 210, 347, 600, 2102, 275, 142 },
  { 212, 349, 651, 2194, 276, 157 },
  { 214, 350, 703, 2289, 278, 171 },
  { 215, 351, 755, 2388, 279, 186 },
  { 217, 352, 806, 2492, 280, 200 },
  { 218, 354, 858, 2600, 282, 215 },
};

std::unique_ptr< Sapphire::Common::Random::RandGenerator< float > > CalcStats::rnd = nullptr;

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

  return static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::MAIN ] );
}

// Leggerless' HP Formula
// ROUNDDOWN(JobModHP * (BaseHP / 100)) + ROUNDDOWN(VitHPMod / 100 * (VIT - BaseDET))

uint32_t CalcStats::calculateMaxHp( Entity::Player& player )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  // TODO: Replace ApproxBaseHP with something that can get us an accurate BaseHP.
  // Is there any way to pull reliable BaseHP without having to manually use a pet for every level, and using the values from a table?
  // More info here: https://docs.google.com/spreadsheets/d/1de06KGT0cNRUvyiXNmjNgcNvzBCCQku7jte5QxEQRbs/edit?usp=sharing

  auto classInfo = exdData.getRow< Excel::ClassJob >( static_cast< uint8_t >( player.getClass() ) );
  auto paramGrowthInfo = exdData.getRow< Excel::ParamGrow >( player.getLevel() );

  if( !classInfo || !paramGrowthInfo )
    return 0;

  uint8_t level = player.getLevel();

  auto vitMod = player.getBonusStat( Common::BaseParam::Vitality );
  float baseStat = calculateBaseStat( player );
  auto baseParamVit = player.getStatValue( Common::BaseParam::Vitality );
  auto vitStat = player.getStatValue( Common::BaseParam::Vitality ) + vitMod;
  uint16_t hpMod = paramGrowthInfo->data().ParamBase;
  uint16_t jobModHp = classInfo->data().Hp;
  float approxBaseHp = 0.0f; // Read above
  float hpModPercent = player.getModifier( Common::ParamModifier::HPPercent );

  approxBaseHp = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::HP ] );

  auto result = static_cast< uint32_t >( floor( jobModHp * ( approxBaseHp / 100.0f ) ) +
                                         floor( hpMod / 100.0f * ( vitStat - baseStat ) ) );

  result *= hpModPercent;

  return result;
}

uint32_t CalcStats::calculateMaxHp( Chara& chara )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  // TODO: Replace ApproxBaseHP with something that can get us an accurate BaseHP.
  // Is there any way to pull reliable BaseHP without having to manually use a pet for every level, and using the values from a table?
  // More info here: https://docs.google.com/spreadsheets/d/1de06KGT0cNRUvyiXNmjNgcNvzBCCQku7jte5QxEQRbs/edit?usp=sharing

  auto classInfo = exdData.getRow< Excel::ClassJob >( static_cast< uint8_t >( chara.getClass() ) );
  auto paramGrowthInfo = exdData.getRow< Excel::ParamGrow >( chara.getLevel() );

  if( !classInfo || !paramGrowthInfo )
    return 0;

  uint8_t level = chara.getLevel();

  auto vitMod = chara.getBonusStat( Common::BaseParam::Vitality );
  float baseStat = calculateBaseStat( chara );
  uint16_t vitStat = static_cast< uint16_t >( chara.getStatValue( Common::BaseParam::Vitality ) ) + static_cast< uint16_t >( vitMod );
  uint16_t hpMod = paramGrowthInfo->data().ParamBase;
  uint16_t jobModHp = classInfo->data().Hp;
  float approxBaseHp = 0.0f; // Read above

  approxBaseHp = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::HP ] );

  auto result = static_cast< uint32_t >( floor( jobModHp * ( approxBaseHp / 100.0f ) ) +
                                             floor( hpMod / 100.0f * ( vitStat - baseStat ) ) );

  return result;
}

uint32_t CalcStats::calculateMaxMp( Entity::Player& player )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto classInfo = exdData.getRow< Excel::ClassJob >( static_cast< uint8_t >( player.getClass() ) );
  auto paramGrowthInfo = exdData.getRow< Excel::ParamGrow >( player.getLevel() );

  if( !classInfo || !paramGrowthInfo )
    return 0;

  float baseStat = calculateBaseStat( player );
  uint16_t piety = player.getStats()[ static_cast< uint32_t >( Common::BaseParam::Piety ) ];
  uint16_t pietyScalar = paramGrowthInfo->data().ParamBase;
  uint16_t jobModMp = classInfo->data().Mp;
  uint16_t baseMp = paramGrowthInfo->data().Mp;

  uint16_t result = static_cast< uint16_t >( std::floor( floor( piety - baseStat ) * ( pietyScalar / 100 ) + baseMp ) *
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
  auto blockRate = static_cast< float >( chara.getStatValue( Common::BaseParam::BlockRate ) );
  auto levelVal =  static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  return std::floor( ( 30 * blockRate ) / levelVal + 10 );
}

float CalcStats::criticalHitProbability( const Chara& chara )
{
  const auto& baseStats = chara.getStats();
  auto level = chara.getLevel();

  // ⌊ 200 × ( CHR - subVal )/ divVal + 50 ⌋ / 10
  // CHR is the critical hit stat. Additional modifiers from (de)buffs get applied at the end
  auto chRate = chara.getStatValueFloat( Common::BaseParam::CriticalHit );

  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );
  auto subVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::SUB ] );
  chRate = std::floor( 200.f * ( chRate - subVal ) / divVal + 50.f ) / 10.f;

  chRate *= chara.getModifier( Common::ParamModifier::CriticalHitPercent );
  chRate += chara.getModifier( Common::ParamModifier::CriticalHit );

  return chRate;
}


float CalcStats::potency( uint16_t potency )
{
  return static_cast< float >( potency ) / 100.f;
}

float CalcStats::autoAttackPotency( const Sapphire::Entity::Chara& chara )
{
  uint32_t aaPotency = AUTO_ATTACK_POTENCY;

  if( chara.getRole() == Common::Role::RangedPhysical )
  {
    aaPotency = RANGED_AUTO_ATTACK_POTENCY;
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
  //return std::floor( aaPotency / 3.f * autoAttackDelay ) / 100.f;
  return aaPotency / 100.f;
}

float CalcStats::weaponDamage( const Sapphire::Entity::Chara& chara, float weaponDamage )
{
  const auto& baseStats = chara.getStats();
  auto level = chara.getLevel();

  auto mainVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::MAIN ] );

  uint32_t jobMod = 1;

  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto classInfo = exdData.getRow< Excel::ClassJob >( static_cast< uint8_t >( chara.getClass() ) );

  if( !classInfo )
    return 0.f;

  switch( chara.getPrimaryStat() )
  {
    case Common::BaseParam::Intelligence:
    {
      jobMod = classInfo->data().INT_;
      break;
    }
    case Common::BaseParam::Mind:
    {
      jobMod = classInfo->data().MND;
      break;
    }
    case Common::BaseParam::Strength:
    {
      jobMod = classInfo->data().STR;
      break;
    }
    case Common::BaseParam::Dexterity:
    {
      jobMod = classInfo->data().DEX;
      break;
    }
    case Common::BaseParam::Vitality:
    {
      jobMod = classInfo->data().VIT;
      break;
    }
    case Common::BaseParam::Piety:
    {
      jobMod = classInfo->data().PIE;
      break;
    }
    default:
    {
      jobMod = 100;
      break;
    }
  }

  return ( std::floor( mainVal * jobMod / 1000.f ) + weaponDamage );
}

float CalcStats::calcAttackPower( const Sapphire::Entity::Chara& chara, uint32_t attackPower )
{
  auto level = chara.getLevel();
  auto mainVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::MAIN ] );
  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  return Common::Util::trunc( static_cast< float >( attackPower ) / divVal + ( 1.0f - mainVal / divVal ), 2 );
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

  return Common::Util::trunc( 1.0f + ( chara.getStatValue( Common::BaseParam::Determination ) - mainVal ) / divVal, 3 );
}

float CalcStats::tenacity( const Sapphire::Entity::Chara& chara )
{
  auto level = chara.getLevel();

  auto subVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::SUB ] );
  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  return std::floor( 100.f * ( chara.getStatValue( Common::BaseParam::Parry ) - subVal ) / divVal + 1000.f ) / 1000.f;
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
  float dmg = 10.f;

  // fetch actual auto attack delay if its a player
  if( chara.isPlayer() )
  {
    // todo: ew
    auto pPlayer = const_cast< Entity::Chara& >( chara ).getAsPlayer();
    assert( pPlayer );

    auto pItem = pPlayer->getEquippedWeapon();
    assert( pItem );

    autoAttackDelay = pItem->getDelay() / 1000.f;
    dmg = pItem->getWeaponDmg();
  }

  auto level = chara.getLevel();
  auto mainVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::MAIN ] );

  auto innerCalc = weaponDamage( chara, dmg );

  return std::floor( innerCalc * ( autoAttackDelay / 3.f ) );
}

float CalcStats::healingMagicPotency( const Sapphire::Entity::Chara& chara )
{
  return std::floor( 100.f * ( chara.getStatValue( Common::BaseParam::HealingMagicPotency ) - 292.f ) / 264.f + 100.f ) / 100.f;
}

std::pair< float, Sapphire::Common::CalcResultType > CalcStats::calcAutoAttackDamage( const Sapphire::Entity::Chara& chara )
{
  // D = ⌊ f(ptc) × f(aa) × f(ap) × f(det) × f(tnc) × traits ⌋ × f(ss) ⌋ ×
  // f(chr) ⌋ × f(dhr) ⌋ × rand[ 0.95, 1.05 ] ⌋ × buff_1 ⌋ × buff... ⌋

  auto pot = autoAttackPotency( chara );
  auto aa = autoAttack( chara );
  auto ap = getPrimaryAttackPower( chara );
  auto det = determination( chara );


  // todo: everything after tenacity
  auto factor = Common::Util::trunc( pot * aa * ap * det, 0 );
  Sapphire::Common::CalcResultType hitType = Sapphire::Common::CalcResultType::TypeDamageHp;

  // todo: traits

  factor = std::floor( factor * speed( chara ) );

  if( criticalHitProbability( chara ) > getRandomNumber0To100() )
  {
    factor *= criticalHitBonus( chara );
    hitType = Sapphire::Common::CalcResultType::TypeCriticalDamageHp;
  }

  factor *= 1.0f + ( ( getRandomNumber0To100() - 50.0f ) / 1000.0f );

  // todo: buffs

  constexpr auto format = "auto attack: pot: {} aa: {} ap: {} det: {} ten: {} = {}";

  if( auto player = const_cast< Entity::Chara& >( chara ).getAsPlayer() )
  {
    PlayerMgr::sendDebug( *player, format, pot, aa, ap, det, 1, factor );
  }
  else
  {
  //  Logger::debug( format, pot, aa, ap, det, ten, factor );
  }

  return std::pair( factor, hitType );
}

std::pair< float, Sapphire::Common::CalcResultType > CalcStats::calcActionDamage( const Sapphire::Entity::Chara& chara, uint32_t ptc, float wepDmg )
{
  // D = ⌊ f(pot) × f(wd) × f(ap) × f(det) × f(tnc) × traits ⌋
  // × f(chr) ⌋ × f(dhr) ⌋ × rand[ 0.95, 1.05 ] ⌋ buff_1 ⌋ × buff_1 ⌋ × buff... ⌋

  auto pot = potency( static_cast< uint16_t >( ptc ) );
  auto wd = weaponDamage( chara, wepDmg );
  auto ap = getPrimaryAttackPower( chara );
  auto det = determination( chara );
  auto damageDealtMod = chara.getModifier( Common::ParamModifier::DamageDealtPercent );

  auto factor = Common::Util::trunc( pot * wd * ap * det, 0 );
  Sapphire::Common::CalcResultType hitType = Sapphire::Common::CalcResultType::TypeDamageHp;

  if( criticalHitProbability( chara ) > getRandomNumber0To100() )
  {
    factor *= criticalHitBonus( chara );
    hitType = Sapphire::Common::CalcResultType::TypeCriticalDamageHp;
  }

  factor *= 1.0f + ( ( getRandomNumber0To100() - 50.0f ) / 1000.0f );

  // todo: buffs

  factor *= damageDealtMod;

  constexpr auto format = "dmg: pot: {} ({}) wd: {} ({}) ap: {} det: {}  = {}";

  if( auto player = const_cast< Entity::Chara& >( chara ).getAsPlayer() )
  {
    PlayerMgr::sendDebug( *player, format, pot, ptc, wd, wepDmg, ap, det, factor );
    PlayerMgr::sendDebug( *player, "DamageDealtPercent: {}", damageDealtMod );
  }
  else
  {
    Logger::debug( format, pot, ptc, wd, wepDmg, ap, det, factor );
  }

  return std::pair( factor, hitType );
}

std::pair< float, Sapphire::Common::CalcResultType > CalcStats::calcActionHealing( const Sapphire::Entity::Chara& chara, uint32_t ptc, float wepDmg )
{
  // lol just for testing
  float det = chara.getStatValue( Common::BaseParam::Determination );
  float mnd = chara.getStatValue( Common::BaseParam::Mind );

  auto factor = std::floor( ( wepDmg * ( mnd / 200 ) + ( det / 10 ) ) * ( ptc / 100 ) * 1.3f );

  Sapphire::Common::CalcResultType hitType = Sapphire::Common::CalcResultType::TypeRecoverHp;

  if( criticalHitProbability( chara ) > getRandomNumber0To100() )
  {
    factor *= criticalHitBonus( chara );
    hitType = Sapphire::Common::CalcResultType::TypeCriticalRecoverHp;
  }

  factor *= 1.0f + ( ( getRandomNumber0To100() - 50.0f ) / 1000.0f );

  return std::pair( factor, hitType );
}

int32_t CalcStats::calcAggro( const Sapphire::Entity::Chara& source, int32_t value, float actionAggroModifier )
{
  int32_t aggro = value * actionAggroModifier;
  auto aggroMod = 1 - ( source.getModifier( Common::ParamModifier::EnmityReduction ) / 100 );
  return aggro * aggroMod;
}

int32_t CalcStats::calcStatusAggro( const Sapphire::Entity::Chara& source )
{
  int32_t aggro = static_cast< int32_t >( levelTable[ source.getLevel() ][ Common::LevelTableEntry::THREAT ] );
  auto aggroMod = 1 - ( source.getModifier( Common::ParamModifier::EnmityReduction ) / 100 );
  return aggro * aggroMod;
}

uint32_t CalcStats::calcMpRefresh(uint32_t potency, uint8_t level)
{
  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto paramGrowthInfo = exdData.getRow< Excel::ParamGrow >( level );

  if (!paramGrowthInfo)
  {
    Logger::error( "Failed to read paramgrow exd when calculating MP refresh!" );
    // Just assume max level (60) if we fail to read the file
    return std::floor( potency * 0.884f );
  }

  uint32_t mpMod = paramGrowthInfo->data().Mp;
  return std::floor( potency * mpMod / 1000 );
}

uint32_t CalcStats::primaryStatValue( const Sapphire::Entity::Chara& chara )
{
  return chara.getStatValue( chara.getPrimaryStat() );
}

float CalcStats::getRandomNumber0To100()
{
  if( !rnd )
  {
    rnd = std::make_unique< Common::Random::RandGenerator< float > >( Common::Service< Common::Random::RNGMgr >::ref().getRandGenerator< float >( 0, 100 ) );
  }
  return rnd->next();
}
