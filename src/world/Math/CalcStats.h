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

    static uint16_t calculateMpCost( const Sapphire::Entity::Chara& chara, uint16_t baseCost );

    static float pBlk( const Sapphire::Entity::Chara& );
    static float pDhr( const Sapphire::Entity::Chara& );
    static float pChr( const Sapphire::Entity::Chara& );

  private:

  };

}

#endif
