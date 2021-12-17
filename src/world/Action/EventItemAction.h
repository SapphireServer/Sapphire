#pragma once

#include "Action.h"
#include <Exd/Structs.h>

namespace Sapphire::Data
{
  struct ItemAction;
  using ItemActionPtr = std::shared_ptr< ItemAction >;
}

namespace Sapphire::World::Action
{
  class ItemAction : public Action
  {
  public:
    ItemAction( Entity::CharaPtr source, uint32_t itemId, std::shared_ptr< Component::Excel::ExcelStruct< Component::Excel::ItemAction > > itemActionData,
                uint16_t itemSourceSlot, uint16_t itemSourceContainer );
    virtual ~ItemAction() = default;

    void start() override;

    void execute() override;

    void interrupt() override;

  private:
    void handleVFXItem();

  private:
    std::shared_ptr< Component::Excel::ExcelStruct< Component::Excel::ItemAction > > m_itemAction;

    uint16_t m_itemSourceSlot;
    uint16_t m_itemSourceContainer;
  };
}