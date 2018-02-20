#ifndef _ACTIONCAST_H_
#define _ACTIONCAST_H_

#include "../Forwards.h"
#include "Action.h"

namespace Core {
namespace Action {

   class ActionCast : public Action
   {
   private: 

   public:
      ActionCast();
      ~ActionCast();
      
      ActionCast( Entity::CharaPtr pActor, Entity::CharaPtr pTarget, uint16_t actionId );

      void onStart() override;
      void onFinish() override;
      void onInterrupt() override;

   };

}
}

#endif
