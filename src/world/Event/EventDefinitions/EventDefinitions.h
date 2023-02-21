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

  class LogoutEvent : public Event
  {
  public:
    static constexpr DescriptorType descriptor = "LogoutEvent";
    virtual DescriptorType type() const { return descriptor; }

    LogoutEvent( uint64_t charId ) : characterId( charId ) {};
    virtual ~LogoutEvent() = default;


    uint64_t characterId;
  };

}