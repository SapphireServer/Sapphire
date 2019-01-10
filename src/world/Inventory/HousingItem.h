#ifndef SAPPHIRE_HOUSINGITEM_H
#define SAPPHIRE_HOUSINGITEM_H

#include "Item.h"

namespace Sapphire::Inventory
{
  class HousingItem : public Item
  {
  public:
    HousingItem( uint64_t uId, uint32_t catalogId, FrameworkPtr pFw );
    virtual ~HousingItem() = default;

    void setRot( float rot );
    float getRot() const;

    void setPos( Common::FFXIVARR_POSITION3 pos );
    Common::FFXIVARR_POSITION3 getPos() const;

  private:
    Common::FFXIVARR_POSITION3 m_position;
    float m_rotation;
  };
}

#endif //SAPPHIRE_HOUSINGITEM_H
