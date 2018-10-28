#ifndef _CALCSTATS_H
#define _CALCSTATS_H

#include <Common.h>
#include "Forwards.h"

namespace Core::Math
{

  class CalcStats
  {
  public:
    static float calculateBaseStat( Core::Entity::PlayerPtr pPlayer );

    static uint32_t calculateMaxMp( Core::Entity::PlayerPtr pPlayer );

    static uint32_t calculateMaxHp( Core::Entity::PlayerPtr pPlayer );

  private:

  };

}

#endif
