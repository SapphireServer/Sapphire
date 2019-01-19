#ifndef _ACTIONCAST_H_
#define _ACTIONCAST_H_

#include "ForwardsZone.h"
#include "Action.h"

namespace Sapphire::Action
{

  class ActionCast : public Action
  {
  private:

  public:
    ActionCast();

    ~ActionCast();

    ActionCast( Entity::CharaPtr pActor, Entity::CharaPtr pTarget, uint16_t actionId, FrameworkPtr pFw );

    void onStart() override;

    void onFinish() override;

    void onInterrupt() override;

  };

}

#endif
