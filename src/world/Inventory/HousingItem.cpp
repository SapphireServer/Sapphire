#include "HousingItem.h"

Sapphire::Inventory::HousingItem::HousingItem( uint64_t uId, uint32_t catalogId ) :
  Sapphire::Item( uId, catalogId, false )
{ }

float Sapphire::Inventory::HousingItem::getRot() const
{
  return m_rotation;
}

void Sapphire::Inventory::HousingItem::setRot( float rot )
{
  m_rotation = rot;
}

Sapphire::Common::FFXIVARR_POSITION3 Sapphire::Inventory::HousingItem::getPos() const
{
  return m_position;
}

void Sapphire::Inventory::HousingItem::setPos( Sapphire::Common::FFXIVARR_POSITION3 pos )
{
  m_position = pos;
}