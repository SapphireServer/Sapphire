#include "EventDispatcher.h"

using namespace Sapphire::Common::EventSystem;

void EventDispatcher::subscribe( const Event::DescriptorType& descriptor, const SlotType& slot )
{
  m_observers[ descriptor ].push_back( slot );
}

void EventDispatcher::subscribe( const Event::DescriptorType& descriptor, const std::vector< SlotType >& slots )
{
  for( auto& slot : slots )
    subscribe( descriptor, slot );
}

void EventDispatcher::emit( const Event& event ) const
{
  auto type = event.type();

  if( m_observers.find( type ) == m_observers.end() )
    return;

  auto& observers = m_observers.at( type );

  for( auto& observer : observers )
    observer( event );
}