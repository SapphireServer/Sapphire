#ifndef _CALCBATTLE_H
#define _CALCBATTLE_H

#include <src/servers/Server_Common/Common.h>

#include "Actor.h"

namespace Core {
namespace Entity {

   class CalcBattle
   {
   public:

      static float calculateBaseStat( PlayerPtr pPlayer );
      static uint32_t calculateMaxMp( PlayerPtr pPlayer );
      static uint32_t calculateMaxHp( PlayerPtr pPlayer );
      static uint32_t calculateHealValue( PlayerPtr pPlayer, uint32_t potency );

   private:

   };

}
}

#endif