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

  private:

  };

}

#endif
