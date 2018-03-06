#ifndef _CALCSTATS_H
#define _CALCSTATS_H

#include <Common.h>
#include "Forwards.h"

using namespace Core::Entity;

namespace Core {
namespace Math {
   
   class CalcStats
   {
   public:
      static float calculateBaseStat( PlayerPtr pPlayer );
      static uint32_t calculateMaxMp( PlayerPtr pPlayer );
      static uint32_t calculateMaxHp( PlayerPtr pPlayer );

   private:

   };

}
}

#endif
