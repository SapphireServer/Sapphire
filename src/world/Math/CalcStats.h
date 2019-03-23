#ifndef _CALCSTATS_H
#define _CALCSTATS_H

#include <Common.h>
#include "Forwards.h"

namespace Sapphire::Math
{

  class CalcStats
  {
  public:
    static float calculateBaseStat( Sapphire::Entity::PlayerPtr pPlayer );

    static uint32_t calculateMaxMp( Sapphire::Entity::PlayerPtr pPlayer, FrameworkPtr pFw );

    static uint32_t calculateMaxHp( Sapphire::Entity::PlayerPtr pPlayer, FrameworkPtr pFw  );

    /*!
     * @brief Calculates the MP cost of a spell given its base cost
     * @param chara The Chara that is casting the action
     * @param baseCost The action cost
     * @return The total MP to be consumed by a successful cast
     */
    static uint16_t calculateMpCost( const Sapphire::Entity::Chara& chara, uint16_t baseCost );

    /*!
     * @brief Calculates the probability of a block happening
     * @return
     */
    static float pBlk( const Sapphire::Entity::Chara& );

    /*!
     * @brief Calculates the probability of a direct hit happening
     * @return
     */
    static float pDhr( const Sapphire::Entity::Chara& );

    /*!
     * @brief Calculates the probability of a critical hit happening
     * @return
     */
    static float pChr( const Sapphire::Entity::Chara& );

  private:

  };

}

#endif
