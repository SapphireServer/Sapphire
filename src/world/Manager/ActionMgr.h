#pragma once

#include "ForwardsZone.h"
#include <Exd/Structs.h>

namespace Sapphire::Data
{
  struct Action;
  using ActionPtr = std::shared_ptr< Action >;

  struct ItemAction;
  using ItemActionPtr = std::shared_ptr< ItemAction >;
}

namespace Sapphire::World::Manager
{
  class ActionMgr
  {
  public:
    ActionMgr() = default;
    ~ActionMgr() = default;

    bool cacheActionLut();

    void handleItemManipulationAction( Entity::Player& player, uint32_t actionId, Excel::ExcelStructPtr< Excel::Action > actionData, uint16_t sequence );

    void handleTargetedPlayerAction( Entity::Player& player, uint32_t actionId,
                                     std::shared_ptr< Excel::ExcelStruct< Excel::Action > > actionData, uint64_t targetId, uint16_t sequence );
    void handlePlacedPlayerAction( Entity::Player& player, uint32_t actionId,
                                   std::shared_ptr< Excel::ExcelStruct< Excel::Action > > actionData, Common::FFXIVARR_POSITION3 pos, uint16_t sequence );

    void handleItemAction( Entity::Player& player, uint32_t itemId, std::shared_ptr< Excel::ExcelStruct< Excel::ItemAction > > itemActionData,
                           uint16_t itemSourceSlot, uint16_t itemSourceContainer );

    void handleEventItemAction( Entity::Player& player, uint32_t itemId,
                                std::shared_ptr< Excel::ExcelStruct< Excel::EventItem > > itemActionData, uint32_t sequence, uint64_t targetId );

    void handleMountAction( Entity::Player& player, uint16_t mountId,
                            std::shared_ptr< Excel::ExcelStruct< Excel::Action > > actionData, uint64_t targetId, uint16_t sequence );

    bool actionHasCastTime( uint32_t actionId );
  private:
    void bootstrapAction( Entity::Player& player, Action::ActionPtr currentAction, std::shared_ptr< Excel::ExcelStruct< Excel::Action > > actionData );

    // item action handlers
    void handleItemActionVFX( Entity::Player& player, uint32_t itemId, uint16_t vfxId );
  };
}
