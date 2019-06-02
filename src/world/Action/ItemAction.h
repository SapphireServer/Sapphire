#ifndef SAPPHIRE_ITEMACTION_H
#define SAPPHIRE_ITEMACTION_H

#include "Action.h"

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
    ItemAction( Entity::CharaPtr source, uint32_t itemId, Data::ItemActionPtr itemActionData,
                uint16_t itemSourceSlot, uint16_t itemSourceContainer, FrameworkPtr fw );
    virtual ~ItemAction() = default;

    void start() override;

    void execute() override;

    void interrupt() override;

  private:
    void handleVFXItem();

  private:
    Sapphire::Data::ItemActionPtr m_itemAction;

    uint16_t m_itemSourceSlot;
    uint16_t m_itemSourceContainer;
  };
}

#endif //SAPPHIRE_ITEMACTION_H
