#pragma once

#include <Event/Event.h>

namespace Sapphire::Common::EventSystem
{

  class LoginEvent : public Event
  {
  public:
    static constexpr DescriptorType descriptor = "LoginEvent";
    virtual DescriptorType type() const { return descriptor; }

    LoginEvent( uint64_t charId ) : characterId( charId ) {};
    virtual ~LoginEvent() = default;


    uint64_t characterId;
  };

}