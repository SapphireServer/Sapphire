#ifndef SAPPHIRE_SERVICE_H
#define SAPPHIRE_SERVICE_H

#include <memory>
#include <utility>
#include <cassert>
#include <unordered_map>

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
  * Implementaion of the Service locator is replaced with a workaround for Visual Studio, api unchanged.
  */

  class ServiceContainer
  {
  private:
    std::unordered_map< size_t, std::shared_ptr< void > > serviceTable;
  public:
    std::shared_ptr< void > get( size_t id );
    void set( size_t id, std::shared_ptr< void > svc );
    static ServiceContainer* pSvcContainer;
  };

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
      auto id = typeid( SvcType ).hash_code();
      auto service = ServiceContainer::pSvcContainer->get( id );
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
      auto id = typeid( SvcType ).hash_code();
      auto service = std::reinterpret_pointer_cast< SvcType >( ServiceContainer::pSvcContainer->get( id ) );
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
      auto id = typeid( SvcType ).hash_code();
      auto service = std::reinterpret_pointer_cast< SvcType >( ServiceContainer::pSvcContainer->get( id ) );
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
      auto id = typeid( SvcType ).hash_code();
      std::shared_ptr< SvcType > ptr = std::make_shared< Impl >( std::forward< Args >( args )... );
      ServiceContainer::pSvcContainer->set( id, std::move( ptr ) );
    }

    /**
     * @brief Sets or replaces a service.
     * @param ptr Service to use to replace the current one.
     */
    static void set( std::shared_ptr< SvcType > ptr )
    {
      assert( static_cast< bool >( ptr ) );
      auto id = typeid( SvcType ).hash_code();
      ServiceContainer::pSvcContainer->set( id, std::move( ptr ) );
    }

    /**
     * @brief Resets a service.
     *
     * The service is no longer valid after a reset.
     */
    static void reset()
    {
      auto id = typeid( SvcType ).hash_code();
      ServiceContainer::pSvcContainer->set( id, nullptr );
    }
  };
}

#endif //SAPPHIRE_SERVICE_H
