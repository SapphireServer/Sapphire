#ifndef _CALCBATTLE_H
#define _CALCBATTLE_H

#include <Server_Common/Common.h>
#include "Actor/Actor.h"

using namespace Core::Entity;

namespace Core {
namespace Math {
   
   class CalcBattle
   {
   public:
      static uint32_t calculateHealValue( PlayerPtr pPlayer, uint32_t potency );

   private:

   };

}
}

#endif
