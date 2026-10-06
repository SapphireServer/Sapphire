#pragma once

#include <Common.h>
#include <ForwardsCommon.h>

namespace Sapphire::Math
{

  class CalcBattle
  {
  public:
    static uint32_t calculateHealValue( Sapphire::Entity::PlayerPtr pPlayer, uint32_t potency, FrameworkPtr pFw );

  };

}

