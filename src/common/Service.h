#pragma once

#include <memory>
#include <utility>
#include <cassert>
#include <typeindex>
#include <string>

#include "ServiceRegistry.h"

// stolen from: https://github.com/skypjack/entt/blob/master/src/entt/locator/locator.hpp

namespace Sapphire::Common
{
  /**
   * @brief Service locator with cross-module registry.
   *
   * Backed by a process-wide registry implemented in the 'common' shared library,
   * so all DLLs and the main executable see the same services.
   *
   * @tparam SvcType Type of service managed by the locator.
   */
  template< typename SvcType >
  struct Service
  {
    using ServiceType = SvcType;

    Service() = delete;

    ~Service() = delete;

    static bool empty() noexcept
    {
      return !static_cast< bool >( slot() );
    }

    static std::weak_ptr< SvcType > get() noexcept
    {
      return std::reinterpret_pointer_cast< SvcType >( slot() );
    }

    static SvcType& ref() noexcept
    {
      return *std::reinterpret_pointer_cast< SvcType >( slot() );
    }

    template< typename Impl = SvcType, typename... Args >
    static void set( Args&&... args )
    {
      // Construct the implementation, cast to the service base first to preserve pointer adjustment,
      // then erase to void. This avoids losing the correct base subobject address in MI/VI cases.
      auto impl = std::make_shared< Impl >( std::forward< Args >( args )... );
      std::shared_ptr< SvcType > base = std::static_pointer_cast< SvcType >( impl );
      std::shared_ptr< void > erased = base; // upcast keeps adjusted base pointer
      slot() = std::move( erased );
    }

    static void set( std::shared_ptr< SvcType > ptr )
    {
      assert( static_cast<bool>(ptr) );
      std::shared_ptr< void > erased = std::move( ptr );
      slot() = std::move( erased );
    }

    static void reset()
    {
      slot().reset();
    }

  private:
    static std::shared_ptr< void >& slot() noexcept
    {
      // Build a normalized key from RTTI name of pointer-to-type (avoids requiring complete type)
      // Strip MSVC-specific "class " / "struct " prefixes to ensure the same key across TUs/libraries.
      static const std::string key = []
      {
        std::string s = typeid( SvcType * ).name();
        auto erase_all = [&]( const char *token )
        {
          const size_t n = std::char_traits< char >::length( token );
          size_t pos = 0;
          while( ( pos = s.find( token, pos ) ) != std::string::npos )
            s.erase( pos, n );
        };
        erase_all( "class " );
        erase_all( "struct " );
        return s;
      }();
      return Sapphire::Common::detail::service_slot_by_name( key );
    }
  };
}
