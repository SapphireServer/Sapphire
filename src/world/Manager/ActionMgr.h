#ifndef SAPPHIRE_ACTIONMGR_H
#define SAPPHIRE_ACTIONMGR_H

#include "BaseManager.h"

namespace Sapphire::World::Manager
{
  class ActionMgr : public Manager::BaseManager
  {
  public:
    explicit ActionMgr( FrameworkPtr pFw );
    ~ActionMgr() = default;

//    void handlePlayerCast( Entity::Player& player)
  };
}

#endif //SAPPHIRE_ACTIONMGR_H
