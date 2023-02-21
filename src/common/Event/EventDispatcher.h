#pragma once
#include <functional>
#include "Event.h"
#include <unordered_map>

namespace Sapphire::Common::EventSystem
{

  class EventDispatcher
  {
  public:
    using SlotType = std::function< void( const Event& ) >;

    void subscribe( const Event::DescriptorType& descriptor, SlotType&& slot );

    void emit( const Event& event ) const;

  private:
    std::unordered_map< Event::DescriptorType, std::vector< SlotType > > m_observers;

  };

}

