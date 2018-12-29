#ifndef SAPPHIRE_HOUSINGITEM_H
#define SAPPHIRE_HOUSINGITEM_H

#include "Item.h"

namespace Sapphire::Inventory
{
  class HousingItem : public Item
  {
  public:
    HousingItem( uint64_t uId, uint32_t catalogId );
    virtual ~HousingItem() = default;

    void setRot( uint16_t rot );
    uint16_t getRot() const;

    void setPos( Common::FFXIVARR_POSITION3_U16 pos );
    Common::FFXIVARR_POSITION3_U16 getPos() const;

  private:
    Common::FFXIVARR_POSITION3_U16 m_position;
    uint16_t m_rotation;
  };
}

#endif //SAPPHIRE_HOUSINGITEM_H
