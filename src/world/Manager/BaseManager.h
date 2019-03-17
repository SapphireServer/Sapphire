#ifndef SAPPHIRE_MANAGER_H
#define SAPPHIRE_MANAGER_H

#include "ForwardsZone.h"

namespace Sapphire::World::Manager
{

  class BaseManager
  {
  public:
    explicit BaseManager( FrameworkPtr pFw ) : m_pFw( std::move( pFw ) ) {};
    virtual ~BaseManager() = default;

    FrameworkPtr framework() const
    { return m_pFw; }
    void setFw( FrameworkPtr pFw )
    { m_pFw = pFw; }

  private:
    FrameworkPtr m_pFw;
  };

}


#endif //SAPPHIRE_MANAGER_H
