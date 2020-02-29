#ifndef SAPPHIRE_SERVICE_H
#define SAPPHIRE_SERVICE_H

#include <memory>
#include <utility>

// stolen from: https://github.com/skypjack/entt/blob/master/src/entt/locator/locator.hpp

namespace Sapphire::Common
{
  /**
   * @brief Service locator, nothing more.
   *
   * A service locator can be used to do what it promises: locate services.<br/>
   * Usually service locators are tightly bound to the services they expose and
   * thus it's hard to define a general purpose class to do that. This template
   * based implementation tries to fill the gap and to get rid of the burden of
   * defining a different specific locator for each application.
   *
   * @tparam SvcType Type of service managed by the locator.
   */
  template< typename SvcType >
  struct Service
  {
    /*! @brief Type of service offered. */
    using ServiceType = SvcType;

    /*! @brief Default constructor, deleted on purpose. */
    Service() = delete;

    /*! @brief Default destructor, deleted on purpose. */
    ~Service() = delete;

    /**
     * @brief Tests if a valid service implementation is set.
     * @return True if the service is set, false otherwise.
     */
    static bool empty() noexcept
    {
      return !static_cast< bool >( service );
    }

    /**
     * @brief Returns a weak pointer to a service implementation, if any.
     *
     * Clients of a service shouldn't retain references to it. The recommended
     * way is to retrieve the service implementation currently set each and
     * every time the need of using it arises. Otherwise users can incur in
     * unexpected behaviors.
     *
     * @return A reference to the service implementation currently set, if any.
     */
    static std::weak_ptr< SvcType > get() noexcept
    {
      return service;
    }

    /**
     * @brief Returns a weak reference to a service implementation, if any.
     *
     * Clients of a service shouldn't retain references to it. The recommended
     * way is to retrieve the service implementation currently set each and
     * every time the need of using it arises. Otherwise users can incur in
     * unexpected behaviors.
     *
     * @warning
     * In case no service implementation has been set, a call to this function
     * results in undefined behavior.
     *
     * @return A reference to the service implementation currently set, if any.
     */
    static SvcType& ref() noexcept
    {
      return *service;
    }

    /**
     * @brief Sets or replaces a service.
     * @tparam Impl Type of the new service to use.
     * @tparam Args Types of arguments to use to construct the service.
     * @param args Parameters to use to construct the service.
     */
    template< typename Impl = SvcType, typename... Args >
    static void set( Args&& ... args )
    {
      service = std::make_shared< Impl >( std::forward< Args >( args )... );
    }

    /**
     * @brief Sets or replaces a service.
     * @param ptr Service to use to replace the current one.
     */
    static void set( std::shared_ptr< SvcType > ptr )
    {
      assert( static_cast< bool >( ptr ) );
      service = std::move( ptr );
    }

    /**
     * @brief Resets a service.
     *
     * The service is no longer valid after a reset.
     */
    static void reset()
    {
      service.reset();
    }

  private:
    inline static std::shared_ptr< SvcType > service = nullptr;
  };
}

#endif //SAPPHIRE_SERVICE_H
