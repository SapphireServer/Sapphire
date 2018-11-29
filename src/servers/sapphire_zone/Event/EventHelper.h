#ifndef _EVENTHELPER_H
#define _EVENTHELPER_H

#include <cstdint>
#include <string>

namespace Sapphire::Event
{

  std::string getEventName( uint32_t eventId );
  uint32_t mapEventActorToRealActor( uint32_t eventActorId );

}

#endif
