#ifndef _ACTIONTELEPORT_H_
#define _ACTIONTELEPORT_H_

#include "Forwards.h"
#include "Action.h"

namespace Core {
namespace Action {

   class ActionTeleport : public Action
   {
   private: 
      uint16_t m_targetAetheryte;
      uint16_t m_cost;

   public:
      ActionTeleport();
      ~ActionTeleport();
      
      ActionTeleport( Entity::CharaPtr pActor, uint16_t action, uint16_t cost );

      void onStart() override;
      void onFinish() override;
      void onInterrupt() override;

   };

}
}

#endif
