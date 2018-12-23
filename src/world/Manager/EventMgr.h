#ifndef _EVENTHELPER_H
#define _EVENTHELPER_H

#include <cstdint>
#include <string>
#include "Manager/BaseManager.h"

namespace Sapphire::World::Manager
{

  class EventMgr : public BaseManager
  {
  public:
    EventMgr( FrameworkPtr pFw );

    std::string getEventName( uint32_t eventId );

    uint32_t mapEventActorToRealActor( uint32_t eventActorId );
  };

}

#endif
