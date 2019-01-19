#ifndef _CALCBATTLE_H
#define _CALCBATTLE_H

#include <Common.h>
#include "Forwards.h"

namespace Sapphire::Math
{

  class CalcBattle
  {
  public:
    static uint32_t calculateHealValue( Sapphire::Entity::PlayerPtr pPlayer, uint32_t potency, FrameworkPtr pFw );

  };

}

#endif
