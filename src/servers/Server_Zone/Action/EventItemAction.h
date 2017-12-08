#ifndef _EVENTITEMACTION_H_
#define _EVENTITEMACTION_H_

#include "../Forwards.h"
#include "Action.h"

namespace Core {
namespace Action {

   class EventItemAction : public Action 
   {

   public:
      EventItemAction();
      ~EventItemAction();
      
      EventItemAction( Entity::ActorPtr pActor, uint32_t eventId, uint16_t action,
                       ActionCallback finishRef, ActionCallback interruptRef, uint64_t additional );

      void onStart() override;
      void onFinish() override;
      void onInterrupt() override;

   private:
      uint32_t m_eventId;
      uint64_t m_additional;
      
      ActionCallback m_onActionFinishClb;
      ActionCallback m_onActionInterruptClb;

   };

}
}

#endif
