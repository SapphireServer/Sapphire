#pragma once
#include <functional>
#include "Event.h"
#include <unordered_map>

#define BIND_EVENT( v1, v2 ) std::bind( v1, v2, _1 )

namespace Sapphire::Common::EventSystem
{

  class EventDispatcher
  {
  public:
    using SlotType = std::function< void( const Event& ) >;

    void subscribe( const Event::DescriptorType& descriptor, const SlotType& slot );
    void subscribe( const Event::DescriptorType& descriptor, const std::vector< SlotType >& slots );

    void emit( const Event& event ) const;

  private:
    std::unordered_map< Event::DescriptorType, std::vector< SlotType > > m_observers;

  };

}

