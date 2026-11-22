#pragma once

#include <functional>
#include <utility>
#include <vector>

namespace Sapphire::World::Notifications
{
  template< typename Event >
  class EventSignal
  {
  public:
    using Handler = std::function< void( const Event& ) >;

    void subscribe( Handler handler )
    {
      m_handlers.push_back( std::move( handler ) );
    }

    // Callbacks run synchronously in subscription order. Subscribe during server setup.
    void publish( const Event& event ) const
    {
      for( const auto& handler : m_handlers )
        handler( event );
    }

  private:
    std::vector< Handler > m_handlers;
  };
}
