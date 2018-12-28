#include "HousingItem.h"

Sapphire::Inventory::HousingItem::HousingItem( uint64_t uId, uint32_t catalogId ) :
  Sapphire::Item( uId, catalogId, false )
{
  m_stackSize = 1;
  m_spiritBond = 1;
}

uint16_t Sapphire::Inventory::HousingItem::getRot() const
{
  return m_rotation;
}

void Sapphire::Inventory::HousingItem::setRot( uint16_t rot )
{
  m_rotation = rot;
}

Sapphire::Common::FFXIVARR_POSITION3_U16 Sapphire::Inventory::HousingItem::getPos() const
{
  return m_position;
}

void Sapphire::Inventory::HousingItem::setPos( Sapphire::Common::FFXIVARR_POSITION3_U16 pos )
{
  m_position = pos;
}