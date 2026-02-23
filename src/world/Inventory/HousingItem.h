#pragma once

#include "Item.h"

namespace Sapphire::Inventory
{
  class HousingItem : public Item
  {
  public:
    HousingItem( uint64_t uId, uint32_t catalogId );
    virtual ~HousingItem() = default;

    void setRot( float rot );
    float getRot() const;

    void setPos( Common::Vector3 pos );
    Common::Vector3 getPos() const;

  private:
    Common::Vector3 m_position;
    float m_rotation;
  };
}