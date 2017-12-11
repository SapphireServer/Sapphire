#ifndef _CALCSTATS_H
#define _CALCSTATS_H

#include "Actor/Actor.h"
#include <Server_Common/Common.h>

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

} // namespace Math
} // namespace Core

#endif
