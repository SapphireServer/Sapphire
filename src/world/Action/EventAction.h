#ifndef _EVENTACTION_H_
#define _EVENTACTION_H_

#include <Common.h>

#include "ForwardsZone.h"
#include "Action.h"

namespace Sapphire::World::Action
{

class EventAction : public Action
{

public:
  virtual ~EventAction();

  EventAction( Entity::CharaPtr pActor, uint32_t eventId, uint16_t action,
               ActionCallback finishRef, ActionCallback interruptRef, uint64_t additional );

  void start() override;

  void execute() override;

  void interrupt( Common::ActionInterruptType type = Common::ActionInterruptType::RegularInterrupt ) override;

private:
  uint32_t m_eventId;
  uint64_t m_additional;

  ActionCallback m_onActionFinishClb;
  ActionCallback m_onActionInterruptClb;

};

}

#endif
