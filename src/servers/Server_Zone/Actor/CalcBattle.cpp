#include "CalcBattle.h"

#include <src/servers/Server_Common/Exd/ExdData.h>
#include <src/servers/Server_Common/Logging/Logger.h>

#include "Actor.h"
#include "Player.h"

using namespace Core::Entity;

extern Core::Data::ExdData g_exdData;
extern Core::Logger g_log;

/*
   Class used for battle-related formulas and calculations.
   Big thanks to the Theoryjerks group!

   NOTE:
   Formulas here shouldn't be considered final. It's possible that the formula it was based on is correct but 
   wasn't implemented correctly here, or approximated things due to limited knowledge of how things work in retail.
   It's also possible that we're using formulas that were correct for previous patches, but not the current version.

   TODO:

   Base HP val modifier. I can only find values for levels 50~70.
   Attack power (and healing power). Need more researchg on this.
   Damage outgoing calculations. This includes auto-attacks, etc.

*/

uint32_t Core::Entity::CalcBattle::calculateBaseStat(PlayerPtr pPlayer)
{
   // Don't know too much about this formula, but seems to work for some of the levels tested.
   // Originally from Player.cpp, calculateStats().

   float base = 0.0f;
   uint8_t level = pPlayer->getLevel();

   if (level < 51)
      base = static_cast<uint32_t>(0.053f * (level * level) + (1.022f * level) - 0.907f + 20);
   else
      base = static_cast<uint32_t>(1.627f * level + 120.773f);

   return base;
}

// ROUNDDOWN(JobModHP * (BaseHP / 100)) + ROUNDDOWN(VitHPMod / 100 * (VIT - BaseDET))

uint32_t Core::Entity::CalcBattle::calculateMaxHp( PlayerPtr pPlayer )
{
   // TODO: Replace ApproxBaseHP with something that can get us a BaseHP reliably.
   // Is there any way to pull BaseHP without having to manually use a pet for every level, and using the values from a table?

   auto classInfoIt = g_exdData.m_classJobInfoMap.find(pPlayer->getClass());
   auto paramGrowthInfoIt = g_exdData.m_paramGrowthInfoMap.find(pPlayer->getLevel());

   float baseStat = calculateBaseStat(pPlayer);
   uint16_t vit = pPlayer->getStats().vit;
   uint16_t hp_mod = paramGrowthInfoIt->second.hp_mod;
   uint16_t jobModHp = classInfoIt->second.mod_hp;
   uint16_t approxBaseHp = 0; // Read above

   // These values are not precise.
   if (pPlayer->getLevel() > 50)
      approxBaseHp = 0.1452f * paramGrowthInfoIt->second.mp_const + 1356.6f;
   else
      approxBaseHp = paramGrowthInfoIt->second.mp_const * 0.525f;

   uint16_t result = floor( jobModHp * ( approxBaseHp / 100.0f ) ) + floor( hp_mod / 100.0f * ( vit - baseStat ) );

   g_log.error("MaxHP: " + std::to_string(result)
      + " vit is " + std::to_string(vit)
      + " basestat is " + std::to_string(baseStat)
      + " hp_mod is " + std::to_string(hp_mod)
      + " approxBaseHp is " + std::to_string(approxBaseHp)
      + " jobmodhp is " + std::to_string(jobModHp)
   );

   return result;
}

// Floor[(Floor[(283 - 218) * (540/100)] + 8840) * (115/100)]
// Floor[(Floor[(Piety - BaseDet) (PieMPMod / 100)] + BaseMP) * (JobModMP / 100)]
// ROUNDDOWN(((ROUNDDOWN(((PIE - BaseDET) * PieMPMod/100),0) + BaseMP) * JobModMP / 100),0)

uint32_t Core::Entity::CalcBattle::calculateMaxMp( PlayerPtr pPlayer )
{
   auto classInfoIt = g_exdData.m_classJobInfoMap.find(pPlayer->getClass());
   auto paramGrowthInfoIt = g_exdData.m_paramGrowthInfoMap.find(pPlayer->getLevel());

   float baseStat = calculateBaseStat( pPlayer );
   uint16_t piety = pPlayer->getStats().pie;
   uint16_t piety_scalar = paramGrowthInfoIt->second.mp_mod;
   uint16_t jobModMp = classInfoIt->second.mod_mpcpgp;
   uint16_t baseMp = paramGrowthInfoIt->second.mp_const;

   uint16_t result = floor( floor( piety - baseStat ) * ( piety_scalar / 100 ) + baseMp ) * jobModMp / 100;

   g_log.error("MaxMP: " + std::to_string(result) 
      + " piety is " + std::to_string(piety)
      + " basestat is " + std::to_string(baseStat)
      + " mp_mod is " + std::to_string(piety_scalar)
      + " baseMp is " + std::to_string(baseMp)
      + " jobmodmp is " + std::to_string(jobModMp)
   );

   return result;
}


uint32_t Core::Entity::CalcBattle::calculateHealValue( PlayerPtr pPlayer, uint32_t potency )
{
   auto classInfoIt = g_exdData.m_classJobInfoMap.find( pPlayer->getClass() );
   auto paramGrowthInfoIt = g_exdData.m_paramGrowthInfoMap.find( pPlayer->getLevel() );

   if (classInfoIt == g_exdData.m_classJobInfoMap.end() ||
      paramGrowthInfoIt == g_exdData.m_paramGrowthInfoMap.end())
      return 0;


   auto jobModVal = classInfoIt->second;

   // consider 3% variation
   return potency / 10;
}