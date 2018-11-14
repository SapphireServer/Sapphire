#ifndef _CALCBATTLE_H
#define _CALCBATTLE_H

#include <Common.h>
#include "Forwards.h"

namespace Core::Math
{

  class CalcBattle
  {
  public:
    static uint32_t calculateHealValue( Core::Entity::PlayerPtr pPlayer, uint32_t potency );

  };

}

#endif
