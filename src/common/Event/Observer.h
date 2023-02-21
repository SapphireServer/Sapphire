#pragma once
#include "Event.h"

namespace Sapphire::Common::EventSystem
{
  class EventObserver
  {
  public:
    virtual void handleEvent( const Event& e ) = 0;
  };
}
