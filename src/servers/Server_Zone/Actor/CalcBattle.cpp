#include "CalcBattle.h"

#include <src/servers/Server_Common/Exd/ExdData.h>

#include "Actor.h"
#include "Player.h"

using namespace Core::Entity;

extern Core::Data::ExdData g_exdData;

/*
   Class used for battle-related formulas and calculatio ns.
   Big thanks to the Theoryjerks group!

   NOTE:
   Formulas here shouldn't be considered final. It's possible that the formula it was based on is correct but 
   wasn't implemented correctly here, or approximated things due to limited knowledge of how things work in retail.
   It's also possible that we're using formulas that were correct for previous patches, but not the current version.

   TODO:

   Vitality HP modifier. I can only find values for levels 50~70.
   HP calculation. Not a lot limiting us here. It should be next.
   Damage outgoing calculations. This includes auto-attacks, etc.
   Stats. Will need to align stats from retail with what we have.

*/

uint32_t Core::Entity::CalcBattle::measureHp( ActorPtr pActor )
{
   // todo: reduce autos here

   PlayerPtr pPlayer = pActor->getAsPlayer();

   auto classInfoIt = g_exdData.m_classJobInfoMap.find( pPlayer->getClass() );
   auto paramGrowthInfoIt = g_exdData.m_paramGrowthInfoMap.find( pPlayer->getLevel() );

   return 10;
}

uint32_t Core::Entity::CalcBattle::measureHeal( ActorPtr pActor, uint32_t potency )
{
   // todo: reduce autos here

   PlayerPtr pPlayer = pActor->getAsPlayer();

   auto classInfoIt = g_exdData.m_classJobInfoMap.find( pPlayer->getClass() );
   auto paramGrowthInfoIt = g_exdData.m_paramGrowthInfoMap.find( pPlayer->getLevel() );

   if (classInfoIt == g_exdData.m_classJobInfoMap.end() ||
      paramGrowthInfoIt == g_exdData.m_paramGrowthInfoMap.end())
      return 0;


   auto jobModVal = classInfoIt->second;

   // consider 3% variation
   return potency / 10;
}