#ifndef _ACTIONMOUNT_H_
#define _ACTIONMOUNT_H_

#include "src/servers/Server_Zone/Forwards.h"
#include "Action.h"

namespace Core { namespace Action {

   class ActionMount : public Action
   {
   private: 

   public:
      ActionMount();
      ~ActionMount();
      
      ActionMount( Entity::ActorPtr pActor, Entity::ActorPtr pTarget, uint32_t actionId );

      void onStart() override;
      void onFinish() override;
      void onInterrupt() override;

   };

}
}

#endif