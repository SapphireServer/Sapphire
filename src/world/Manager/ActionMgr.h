#ifndef SAPPHIRE_ACTIONMGR_H
#define SAPPHIRE_ACTIONMGR_H

#include "BaseManager.h"
#include "ForwardsZone.h"

namespace Sapphire::Data
{
  struct Action;
  using ActionPtr = std::shared_ptr< Action >;

  struct ItemAction;
  using ItemActionPtr = std::shared_ptr< ItemAction >;
}

namespace Sapphire::World::Manager
{
  class ActionMgr : public Manager::BaseManager
  {
  public:
    explicit ActionMgr( FrameworkPtr pFw );
    ~ActionMgr() = default;

    void handleTargetedPlayerAction( Entity::Player& player, uint32_t actionId,
                                     Data::ActionPtr actionData, uint64_t targetId );
    void handleAoEPlayerAction( Entity::Player& player, uint32_t actionId,
                                Data::ActionPtr actionData, Common::FFXIVARR_POSITION3 pos );

    void handleItemAction( Entity::Player& player, uint32_t itemId, Data::ItemActionPtr itemActionData,
                           uint16_t itemSourceSlot, uint16_t itemSourceContainer );

  private:
    void bootstrapAction( Entity::Player& player, Action::ActionPtr currentAction, Data::Action& actionData );

    // item action handlers
    void handleItemActionVFX( Entity::Player& player, uint32_t itemId, uint16_t vfxId );
  };
}

#endif //SAPPHIRE_ACTIONMGR_H
