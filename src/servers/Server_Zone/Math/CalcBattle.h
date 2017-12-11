#ifndef _CALCBATTLE_H
#define _CALCBATTLE_H

#include "Actor/Actor.h"
#include <Server_Common/Common.h>

using namespace Core::Entity;

namespace Core {
namespace Math {

   class CalcBattle
   {
   public:
      static uint32_t calculateHealValue( PlayerPtr pPlayer, uint32_t potency );

   private:
   };

} // namespace Math
} // namespace Core

#endif
