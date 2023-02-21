#pragma once
#include <typeinfo>

namespace Sapphire::Common::EventSystem
{
  class Event
  {
  public:
    virtual~ Event() = default;

    using DescriptorType = const char*;
    virtual DescriptorType type() const = 0;
  };
}