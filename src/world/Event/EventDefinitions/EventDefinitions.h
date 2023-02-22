#pragma once

#include <Event/Event.h>

namespace Sapphire::Common::EventSystem
{

  class LoginEvent : public Event
  {
  public:
    static constexpr DescriptorType descriptor = "LoginEvent";
    DescriptorType type() const override { return descriptor; }

    explicit LoginEvent( uint64_t charId ) : characterId( charId ) {};

    uint64_t characterId;
  };

  class LogoutEvent : public Event
  {
  public:
    static constexpr DescriptorType descriptor = "LogoutEvent";
    DescriptorType type() const override { return descriptor; }

    LogoutEvent( uint64_t charId, bool disconnect ) : characterId( charId ), isDisconnect( disconnect ) {};

    uint64_t characterId;
    bool isDisconnect;
  };

}