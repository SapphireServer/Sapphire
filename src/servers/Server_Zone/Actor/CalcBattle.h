#ifndef _CALCBATTLE_H
#define _CALCBATTLE_H

#include <src/servers/Server_Common/Common.h>
#include "Actor.h"

namespace Core {
namespace Entity {

   class CalcBattle
   {
   public:

      static uint32_t measureHp( ActorPtr Player );
      static uint32_t measureHeal( ActorPtr Player, uint32_t potency );

   private:

   };

}
}

#endif