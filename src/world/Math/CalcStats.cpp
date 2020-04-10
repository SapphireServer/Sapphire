#include <cmath>

#include <Exd/ExdDataGenerated.h>
#include <Common.h>
#include <Logging/Logger.h>
#include <Service.h>

#include "Actor/Chara.h"
#include "Actor/Player.h"

#include "Inventory/Item.h"

#include "StatusEffect/StatusEffect.h"

#include "Action/Action.h"

#include "CalcStats.h"

using namespace Sapphire::Math;
using namespace Sapphire::Entity;

const int levelTable[81][6] =
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
  { 224, 355, 941, 2700, 283, 232 },
  { 228, 356, 1032, 2800, 284, 250 },
  { 236, 357, 1133, 2900, 286, 269 },
  { 244, 358, 1243, 3000, 287, 290 },
  { 252, 359, 1364, 3100, 288, 313 },
  { 260, 360, 1497, 3200, 290, 337 },
  { 268, 361, 1643, 3300, 292, 363 },
  { 276, 362, 1802, 3400, 293, 392 },
  { 284, 363, 1978, 3500, 294, 422 },
  { 292, 364, 2170, 3600, 295, 455 },

  // todo: add proper shbr values - hp/elmt/threat
  // sub/div added from http://theoryjerks.akhmorning.com/resources/levelmods/
  { 296, 365, 2263, 3600, 295, 466 },
  { 300, 366, 2360, 3600, 295, 466 },
  { 305, 367, 2461, 3600, 295, 466 },
  { 310, 368, 2566, 3600, 295, 466 },
  { 315, 370, 2676, 3600, 295, 466 },
  { 320, 372, 2790, 3600, 295, 466 },
  { 325, 374, 2910, 3600, 295, 466 },
  { 330, 376, 3034, 3600, 295, 466 },
  { 335, 378, 3164, 3600, 295, 466 },
  { 340, 380, 3300, 3600, 569, 569 },
};

std::random_device CalcStats::dev;
std::mt19937 CalcStats::rng( dev() );
std::uniform_int_distribution< std::mt19937::result_type > CalcStats::range100( 0, 99 );

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

uint32_t CalcStats::calculateMaxHp( PlayerPtr pPlayer )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  // TODO: Replace ApproxBaseHP with something that can get us an accurate BaseHP.
  // Is there any way to pull reliable BaseHP without having to manually use a pet for every level, and using the values from a table?
  // More info here: https://docs.google.com/spreadsheets/d/1de06KGT0cNRUvyiXNmjNgcNvzBCCQku7jte5QxEQRbs/edit?usp=sharing

  auto classInfo = exdData.get< Sapphire::Data::ClassJob >( static_cast< uint8_t >( pPlayer->getClass() ) );
  auto paramGrowthInfo = exdData.get< Sapphire::Data::ParamGrow >( pPlayer->getLevel() );

  if( !classInfo || !paramGrowthInfo )
    return 0;

  uint8_t level = pPlayer->getLevel();

  auto vitMod = pPlayer->getBonusStat( Common::BaseParam::Vitality );
  float baseStat = calculateBaseStat( *pPlayer );
  uint16_t vitStat = static_cast< uint16_t >( pPlayer->getStats().vit ) + static_cast< uint16_t >( vitMod );
  uint16_t hpMod = paramGrowthInfo->hpModifier;
  uint16_t jobModHp = classInfo->modifierHitPoints;
  float approxBaseHp = 0.0f; // Read above

  // These values are not precise.
  /*
  if( level >= 60 )
    approxBaseHp = static_cast< float >( 2600 + ( level - 60 ) * 100 );
  else if( level >= 50 )
    approxBaseHp = 1700 + ( ( level - 50 ) * ( 1700 * 1.04325f ) );
  else
    approxBaseHp = paramGrowthInfo->mpModifier * 0.7667f;
  */
  // just use the table at least better than what it was
  approxBaseHp = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::HP ] );

  uint16_t result = static_cast< uint16_t >( floor( jobModHp * ( approxBaseHp / 100.0f ) ) +
                                             floor( hpMod / 100.0f * ( vitStat - baseStat ) ) );

  return result;
}

float CalcStats::dodgeProbability( const Sapphire::Entity::Chara& chara )
{
  // fake value: 5% for players.
  return chara.isPlayer() ? 5 : 0;
}

float CalcStats::blockProbability( const Chara& chara )
{
  // fake value: 20% for pld.
  float result = chara.getClass() == Common::ClassJob::Paladin ? 20 : 0;
  /*
  auto level = chara.getLevel();
  auto blockRate = static_cast< float >( chara.getStatValue( Common::BaseParam::BlockRate ) );
  auto levelVal =  static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );

  float result = std::floor( ( 30 * blockRate ) / levelVal + 10 );
  */
  for( auto const& entry : chara.getStatusEffectMap() )
  {
    auto status = entry.second;
    auto effectEntry = status->getEffectEntry();
    if( static_cast< Common::StatusEffectType >( effectEntry.effectType ) != Common::StatusEffectType::BlockParryRateBonus )
      continue;
    result += effectEntry.effectValue2;
  }

  return result;
}

float CalcStats::parryProbability( const Sapphire::Entity::Chara& chara )
{
  // fake value: 10% for players.
  float result = chara.isPlayer() ? 10 : 0;

  for( auto const& entry : chara.getStatusEffectMap() )
  {
    auto status = entry.second;
    // hardcoded Camouflage
    if( status->getId() == 1832 )
    {
      result += 50;
      continue;
    }
    //
    auto effectEntry = status->getEffectEntry();
    if( static_cast< Common::StatusEffectType >( effectEntry.effectType ) != Common::StatusEffectType::BlockParryRateBonus )
      continue;
    result += effectEntry.effectValue3;
  }

  return result;
}

float CalcStats::directHitProbability( const Chara& chara, Sapphire::Common::CritDHBonusFilter filter )
{
  const auto& baseStats = chara.getStats();
  auto level = chara.getLevel();

  float dhRate = chara.getStatValue( Common::BaseParam::DirectHitRate );

  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );
  auto subVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::SUB ] );

  auto result = std::floor( 550.f * ( dhRate - subVal ) / divVal ) / 10.f;

  for( auto const& entry : chara.getStatusEffectMap() )
  {
    auto status = entry.second;
    auto effectEntry = status->getEffectEntry();
    if( static_cast< Common::StatusEffectType >( effectEntry.effectType ) != Common::StatusEffectType::CritDHRateBonus )
      continue;
    if( effectEntry.effectValue1 & static_cast< int32_t >( filter ) )
    {
      result += effectEntry.effectValue3;
    }
  }
  return result;
}

float CalcStats::criticalHitProbability( const Chara& chara, Sapphire::Common::CritDHBonusFilter filter )
{
  const auto& baseStats = chara.getStats();
  auto level = chara.getLevel();

  float chRate = chara.getStatValue( Common::BaseParam::CriticalHit );

  auto divVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::DIV ] );
  auto subVal = static_cast< float >( levelTable[ level ][ Common::LevelTableEntry::SUB ] );

  auto result = std::floor( 200.f * ( chRate - subVal ) / divVal + 50.f ) / 10.f;

  for( auto const& entry : chara.getStatusEffectMap() )
  {
    auto status = entry.second;
    auto effectEntry = status->getEffectEntry();
    if( static_cast< Common::StatusEffectType >( effectEntry.effectType ) != Common::StatusEffectType::CritDHRateBonus )
      continue;
    if( effectEntry.effectValue1 & static_cast< int32_t >( filter ) )
    {
      result += effectEntry.effectValue2;
    }
  }
  return result;
}


float CalcStats::potency( uint16_t potency )
{
  return potency / 100.f;
}

float CalcStats::autoAttackPotency( const Sapphire::Entity::Chara& chara, uint32_t aaPotency )
{
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

float CalcStats::getWeaponDamage( CharaPtr chara )
{
  auto wepDmg = chara->getLevel();

  if( auto player = chara->getAsPlayer() )
  {
    auto item = player->getEquippedWeapon();
    assert( item );

    auto role = player->getRole();
    if( role == Common::Role::RangedMagical || role == Common::Role::Healer )
    {
      wepDmg = item->getMagicalDmg();
    }
    else
    {
      wepDmg = item->getPhysicalDmg();
    }
  }

  return wepDmg;
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

float CalcStats::parryStrength( const Sapphire::Entity::Chara& chara )
{
  return 0.15f;
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
  else
  {
    weaponDamage = chara.getLevel() * 3;
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

std::pair< float, Sapphire::Common::ActionHitSeverityType > CalcStats::calcAutoAttackDamage( const Sapphire::Entity::Chara& chara, uint32_t ptc )
{
  // D = ⌊ f(ptc) × f(aa) × f(ap) × f(det) × f(tnc) × traits ⌋ × f(ss) ⌋ ×
  // f(chr) ⌋ × f(dhr) ⌋ × rand[ 0.95, 1.05 ] ⌋ × buff_1 ⌋ × buff... ⌋

  auto pot = autoAttackPotency( chara, ptc );
  auto aa = autoAttack( chara );
  auto ap = getPrimaryAttackPower( chara );
  auto det = determination( chara );

  auto ten = 1.f;
  if( chara.getRole() == Common::Role::Tank )
    ten = tenacity( chara );

  // todo: everything after tenacity
  auto factor = std::floor( pot * aa * ap * det * ten );
  Sapphire::Common::ActionHitSeverityType hitType = Sapphire::Common::ActionHitSeverityType::NormalDamage;

  // todo: traits

  factor = std::floor( factor * speed( chara ) );

  if( criticalHitProbability( chara, Common::CritDHBonusFilter::Damage ) > getRandomNumber0To99() )
  {
    factor *= criticalHitBonus( chara );
    hitType = Sapphire::Common::ActionHitSeverityType::CritDamage;
  }

  if( directHitProbability( chara, Common::CritDHBonusFilter::Damage ) > getRandomNumber0To99() )
  {
    factor *= 1.25f;
    hitType = hitType == Sapphire::Common::ActionHitSeverityType::CritDamage ?
                         Sapphire::Common::ActionHitSeverityType::CritDirectHitDamage :
                         Sapphire::Common::ActionHitSeverityType::DirectHitDamage;
  }

  factor *= 1.0f + ( ( getRandomNumber0To99() - 50.0f ) / 1000.0f );

  for( auto const& entry : chara.getStatusEffectMap() )
  {
    auto status = entry.second;
    auto effectEntry = status->getEffectEntry();
    if( static_cast< Common::StatusEffectType >( effectEntry.effectType ) != Common::StatusEffectType::DamageMultiplier )
      continue;
    if( effectEntry.effectValue1 & static_cast< int32_t >( Common::ActionTypeFilter::Physical ) )
    {
      factor *= 1.0f + ( effectEntry.effectValue2 / 100.0f );
    }
  }

  if( chara.isPlayer() )
  {
    auto player = const_cast< Entity::Chara& >( chara ).getAsPlayer();
    switch( player->getClass() )
    {
      case Common::ClassJob::Darkknight:
      {
        if( player->gaugeDrkGetDarkSideTimer() > 0 )
        {
          factor *= 1.1f;
        }
        break;
      }
    }
    constexpr auto format = "auto attack: pot: {} aa: {} ap: {} det: {} ten: {} = {}";
    player->sendDebug( format, pot, aa, ap, det, ten, factor );
  }

  return std::pair( factor, hitType );
}

float CalcStats::calcDamageBaseOnPotency( const Sapphire::Entity::Chara& chara, uint32_t ptc, float wepDmg )
{
  // D = ⌊ f(pot) × f(wd) × f(ap) × f(det) × f(tnc) × traits ⌋
  // × f(chr) ⌋ × f(dhr) ⌋ × rand[ 0.95, 1.05 ] ⌋ buff_1 ⌋ × buff_1 ⌋ × buff... ⌋

  auto pot = potency( static_cast< uint16_t >( ptc ) );
  auto wd = weaponDamage( chara, wepDmg );
  auto ap = getPrimaryAttackPower( chara );
  auto det = determination( chara );

  auto ten = 1.f;
  if( chara.getRole() == Common::Role::Tank )
    ten = tenacity( chara );

  auto factor = std::floor( pot * wd * ap * det * ten );

  constexpr auto format = "dmg: pot: {} ({}) wd: {} ({}) ap: {} det: {} ten: {} = {}";

  if( auto player = const_cast< Entity::Chara& >( chara ).getAsPlayer() )
  {
    player->sendDebug( format, pot, ptc, wd, wepDmg, ap, det, ten, factor );
  }

  return factor;
}

float CalcStats::calcHealBaseOnPotency( const Sapphire::Entity::Chara& chara, uint32_t ptc, float wepDmg )
{
  // reused damage formula just for testing
  auto pot = potency( static_cast< uint16_t >( ptc ) );
  auto wd = weaponDamage( chara, wepDmg );
  auto ap = getPrimaryAttackPower( chara );
  auto det = determination( chara );

  auto factor = std::floor( pot * wd * ap * det );

  constexpr auto format = "heal: pot: {} ({}) wd: {} ({}) ap: {} det: {} = {}";

  if( auto player = const_cast< Entity::Chara& >( chara ).getAsPlayer() )
  {
    player->sendDebug( format, pot, ptc, wd, wepDmg, ap, det, factor );
  }

  return factor;
}

std::pair< float, Sapphire::Common::ActionHitSeverityType > CalcStats::calcActionDamage( Sapphire::World::Action::Action* pAction, const Sapphire::Entity::Chara& chara, uint32_t ptc, float wepDmg )
{
  auto factor = calcDamageBaseOnPotency( chara, ptc, wepDmg );
  Sapphire::Common::ActionHitSeverityType hitType = Sapphire::Common::ActionHitSeverityType::NormalDamage;

  auto critProb = criticalHitProbability( chara, Common::CritDHBonusFilter::Damage );
  if( pAction )
  {
    auto lutEntry = pAction->getActionEntry();
    if( lutEntry.bonusEffect & Common::ActionBonusEffect::CritBonus )
    {
      if( pAction->checkActionBonusRequirement() )
      {
        critProb += lutEntry.bonusDataUInt16L;
      }
    }
  }

  if( critProb > getRandomNumber0To99() )
  {
    factor *= criticalHitBonus( chara );
    hitType = Sapphire::Common::ActionHitSeverityType::CritDamage;
  }

  auto dhProb = directHitProbability( chara, Common::CritDHBonusFilter::Damage );
  if( pAction )
  {
    auto lutEntry = pAction->getActionEntry();
    if( lutEntry.bonusEffect & Common::ActionBonusEffect::DHBonus )
    {
      if( pAction->checkActionBonusRequirement() )
      {
        dhProb += lutEntry.bonusDataUInt16L;
      }
    }
  }

  if( dhProb > getRandomNumber0To99() )
  {
    factor *= 1.25f;
    hitType = hitType == Sapphire::Common::ActionHitSeverityType::CritDamage ?
                         Sapphire::Common::ActionHitSeverityType::CritDirectHitDamage :
                         Sapphire::Common::ActionHitSeverityType::DirectHitDamage;
  }

  factor *= 1.0f + ( ( getRandomNumber0To99() - 50.0f ) / 1000.0f );

  Common::ActionTypeFilter actionTypeFilter = Common::ActionTypeFilter::Physical;
  if( pAction )
  {
    if( pAction->isMagical() )
      actionTypeFilter = Common::ActionTypeFilter::Magical;
  }

  for( auto const& entry : chara.getStatusEffectMap() )
  {
    auto status = entry.second;
    auto effectEntry = status->getEffectEntry();
    if( static_cast< Common::StatusEffectType >( effectEntry.effectType ) != Common::StatusEffectType::DamageMultiplier )
      continue;

    if( effectEntry.effectValue1 & static_cast< int32_t >( actionTypeFilter ) )
    {
      factor *= 1.0f + ( effectEntry.effectValue2 / 100.0f );
    }
  }

  if( chara.isPlayer() )
  {
    auto player = const_cast< Entity::Chara& >( chara ).getAsPlayer();
    switch( player->getClass() )
    {
      case Common::ClassJob::Darkknight:
      {
        if( player->gaugeDrkGetDarkSideTimer() > 0 )
        {
          factor *= 1.1f;
        }
        break;
      }
    }
  }

  return std::pair( factor, hitType );
}

float CalcStats::applyDamageReceiveMultiplier( const Sapphire::Entity::Chara& chara, float originalDamage, Sapphire::Common::AttackType attackType )
{
  float damage = originalDamage;

  Common::ActionTypeFilter actionTypeFilter = Common::ActionTypeFilter::Unknown;
  if( World::Action::Action::isAttackTypePhysical( attackType ) )
    actionTypeFilter = Common::ActionTypeFilter::Physical;
  else if( World::Action::Action::isAttackTypeMagical( attackType ) )
    actionTypeFilter = Common::ActionTypeFilter::Magical;

  for( auto const& entry : chara.getStatusEffectMap() )
  {
    auto status = entry.second;
    auto effectEntry = status->getEffectEntry();
    if( static_cast< Common::StatusEffectType >( effectEntry.effectType ) != Common::StatusEffectType::DamageReceiveMultiplier )
      continue;

    if( effectEntry.effectValue1 & static_cast< int32_t >( actionTypeFilter ) )
    {
      damage *= ( 1.0f + ( effectEntry.effectValue2 / 100.0f ) );
    }
  }
  return damage;
}

float CalcStats::applyHealingReceiveMultiplier( const Sapphire::Entity::Chara& chara, float originalHeal )
{
  float heal = originalHeal;
  for( auto const& entry : chara.getStatusEffectMap() )
  {
    auto status = entry.second;
    auto effectEntry = status->getEffectEntry();
    if( static_cast< Common::StatusEffectType >( effectEntry.effectType ) != Common::StatusEffectType::HealReceiveMultiplier )
      continue;
    heal *= ( 1.0f + ( effectEntry.effectValue2 / 100.0f ) );
  }
  return heal;
}

std::pair< float, Sapphire::Common::ActionHitSeverityType > CalcStats::calcActionHealing( Sapphire::World::Action::Action* pAction, const Sapphire::Entity::Chara& chara, uint32_t ptc, float wepDmg )
{
  auto factor = calcHealBaseOnPotency( chara, ptc, wepDmg );
  Sapphire::Common::ActionHitSeverityType hitType = Sapphire::Common::ActionHitSeverityType::NormalHeal;

  auto critProb = criticalHitProbability( chara, Common::CritDHBonusFilter::Heal );
  if( pAction )
  {
    auto lutEntry = pAction->getActionEntry();
    if( lutEntry.bonusEffect & Common::ActionBonusEffect::CritBonus )
    {
      if( pAction->checkActionBonusRequirement() )
      {
        critProb += lutEntry.bonusDataUInt16L;
      }
    }
  }

  if( critProb > getRandomNumber0To99() )
  {
    factor *= criticalHitBonus( chara );
    hitType = Sapphire::Common::ActionHitSeverityType::CritHeal;
  }

  factor *= 1.0f + ( ( getRandomNumber0To99() - 50.0f ) / 1000.0f );

  for( auto const& entry : chara.getStatusEffectMap() )
  {
    auto status = entry.second;
    auto effectEntry = status->getEffectEntry();
    if( static_cast< Common::StatusEffectType >( effectEntry.effectType ) != Common::StatusEffectType::HealCastMultiplier )
      continue;

    if( pAction->isGCD() ) // must be a "cast"
    {
      factor *= 1.0f + ( effectEntry.effectValue2 / 100.0f );
    }
  }

  return std::pair( factor, hitType );
}

uint32_t CalcStats::primaryStatValue( const Sapphire::Entity::Chara& chara )
{
  return chara.getStatValue( chara.getPrimaryStat() );
}

std::pair< float, Sapphire::Common::ActionHitSeverityType > CalcStats::calcDamageReflect( Sapphire::Entity::CharaPtr pCharaAttacker, Sapphire::Entity::CharaPtr pCharaVictim, float damage, Sapphire::Common::ActionTypeFilter filter )
{
  for( auto const& entry : pCharaVictim->getStatusEffectMap() )
  {
    auto status = entry.second;
    auto effectEntry = status->getEffectEntry();

    if( static_cast< Common::StatusEffectType >( effectEntry.effectType ) == Common::StatusEffectType::DamageReceiveTrigger && ( effectEntry.effectValue1 & static_cast< int32_t >( filter ) ) )
    {
      if( static_cast< Common::StatusEffectTriggerResult >( effectEntry.effectValue3 ) == Common::StatusEffectTriggerResult::ReflectDamage )
      {
          auto wepDmg = Sapphire::Math::CalcStats::getWeaponDamage( pCharaVictim );
          // any magical reflect damage exists?
          auto damage = Sapphire::Math::CalcStats::calcActionDamage( nullptr, *pCharaVictim, effectEntry.effectValue2, wepDmg );
          damage.first = Math::CalcStats::applyDamageReceiveMultiplier( *pCharaAttacker, damage.first, Common::AttackType::Physical );

          return damage;
      }
    }
  }
  return std::pair< float, Sapphire::Common::ActionHitSeverityType >( 0, Sapphire::Common::ActionHitSeverityType::NormalDamage );
}

float CalcStats::calcAbsorbHP( Sapphire::Entity::CharaPtr pChara, float damage )
{
  float result = 0;
  for( auto const& entry : pChara->getStatusEffectMap() )
  {
    auto status = entry.second;
    auto effectEntry = status->getEffectEntry();

    if( static_cast< Common::StatusEffectType >( effectEntry.effectType ) == Common::StatusEffectType::DamageDealtTrigger )
    {
      if( static_cast< Common::StatusEffectTriggerResult >( effectEntry.effectValue3 ) == Common::StatusEffectTriggerResult::AbsorbHP )
      {
        result += damage * effectEntry.effectValue2 / 100.0f;
      }
    }
  }
  return result;
}

bool CalcStats::calcDodge( const Sapphire::Entity::Chara& chara )
{
  if( dodgeProbability( chara ) > getRandomNumber0To99() )
  {
    return true;
  }
  return false;
}

float CalcStats::calcBlock( const Sapphire::Entity::Chara& chara, float damage )
{
  if( blockProbability( chara ) > getRandomNumber0To99() )
  {
    return damage * blockStrength( chara );
  }
  return 0;
}

float CalcStats::calcParry( const Sapphire::Entity::Chara& chara, float damage )
{
  if( parryProbability( chara ) > getRandomNumber0To99() )
  {
    return damage * parryStrength( chara );
  }
  return 0;
}

uint32_t CalcStats::getRandomNumber0To99()
{
  return range100( rng );
}