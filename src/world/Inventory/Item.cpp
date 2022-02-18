#include <Common.h>
#include <Exd/ExdData.h>
#include <CommonGen.h>
#include <Service.h>

#include "Item.h"

Sapphire::Item::Item( uint64_t uId, uint32_t catalogId, bool isHq ) :
  m_id( catalogId ),
  m_uId( uId ),
  m_isHq( isHq ),
  m_stain( 0 ),
  m_durability( 30000 ),
  m_spiritBond( 0 ),
  m_reservedFlag( 0 )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto itemInfo = exdData.getRow< Excel::Item >( catalogId );

  m_delayMs = itemInfo->data().AttackInterval;
  m_physicalDmg = itemInfo->data().Damage;
  m_magicalDmg = itemInfo->data().MagicDamage;
  m_model1 = itemInfo->data().ModelId;
  m_model2 = itemInfo->data().SubModelId;
  m_weaponDmg = ( m_physicalDmg != 0 ) ? m_physicalDmg : m_magicalDmg;
  m_autoAttackDmg = static_cast< float >( m_weaponDmg * m_delayMs ) / 3000;
  m_category = static_cast< Common::ItemUICategory >( itemInfo->data().UICategory );
  m_slot = itemInfo->data().Slot;
  m_itemLevel = itemInfo->data().EquipLevel;
  m_maxStackSize = itemInfo->data().StackMax;
  // EXD TODO: Not sure what this maps to
  //m_additionalData = itemInfo->additionalData;
  m_blockRate = itemInfo->data().ShieldBlockRate;
  m_block = itemInfo->data().ShieldRate;
  m_defense = itemInfo->data().Defense;
  m_defenseMag = itemInfo->data().MagicDefense;

  for( int i = 0; i < 6; ++i )
  {
    m_baseParam[i].baseParam = itemInfo->data().BonusType[ i ];
    m_baseParam[i].value = itemInfo->data().BonusValue[ i ];
  }
}

uint16_t Sapphire::Item::getDefense() const
{
  return m_defense;
}

uint16_t Sapphire::Item::getDefenseMag() const
{
  return m_defenseMag;
}

float Sapphire::Item::getAutoAttackDmg() const
{
  return m_autoAttackDmg;
}

uint16_t Sapphire::Item::getDelay() const
{
  return m_delayMs;
}

uint16_t Sapphire::Item::getPhysicalDmg() const
{
  return m_physicalDmg;
}

uint16_t Sapphire::Item::getMagicalDmg() const
{
  return m_magicalDmg;
}

uint16_t Sapphire::Item::getItemLevel() const
{
  return m_itemLevel;
}

uint8_t Sapphire::Item::getSlot() const
{
  return m_slot;
}

uint16_t Sapphire::Item::getWeaponDmg() const
{
  return m_weaponDmg;
}

bool Sapphire::Item::isWeapon() const
{
  return ( m_weaponDmg != 0 );
}

uint32_t Sapphire::Item::getId() const
{
  return m_id;
}

void Sapphire::Item::setId( uint32_t id )
{
  m_id = id;
}

uint64_t Sapphire::Item::getUId() const
{
  return m_uId;
}

void Sapphire::Item::setUId( uint64_t id )
{
  m_uId = id;
}

void Sapphire::Item::setStackSize( uint32_t size )
{
  m_stackSize = std::min< uint32_t >( size, m_maxStackSize );
}

uint32_t Sapphire::Item::getStackSize() const
{
  return m_stackSize;
}

void Sapphire::Item::setCategory( Common::ItemUICategory categoryId )
{
  m_category = categoryId;
}

Sapphire::Common::ItemUICategory Sapphire::Item::getCategory() const
{
  return m_category;
}

void Sapphire::Item::setModelIds( uint64_t model1, uint64_t model2 )
{
  m_model1 = model1;
  m_model2 = model2;
}

uint64_t Sapphire::Item::getModelId1() const
{
  return m_model1;
}

uint64_t Sapphire::Item::getModelId2() const
{
  return m_model2;
}

bool Sapphire::Item::isHq() const
{
  return m_isHq;
}

void Sapphire::Item::setHq( bool isHq )
{
  m_isHq = isHq;
}

uint32_t Sapphire::Item::getMaxStackSize() const
{
  return m_maxStackSize;
}

uint16_t Sapphire::Item::getDurability() const
{
  return m_durability;
}

void Sapphire::Item::setDurability( uint16_t durability )
{
  m_durability = durability;
}

uint16_t Sapphire::Item::getStain() const
{
  return m_stain;
}

void Sapphire::Item::setStain( uint16_t stain )
{
  m_stain = stain;
}

uint32_t Sapphire::Item::getAdditionalData() const
{
  return m_additionalData;
}

uint16_t Sapphire::Item::getSpiritbond() const
{
  return m_spiritBond;
}

void Sapphire::Item::setSpiritbond( uint16_t spiritbond )
{
  m_spiritBond = spiritbond;
}

uint32_t Sapphire::Item::getReservedFlag() const
{
  return m_reservedFlag;
}

void Sapphire::Item::setReservedFlag( uint32_t flag )
{
  m_reservedFlag = flag;
}

Sapphire::Item::BaseParamStruct* Sapphire::Item::getBaseParams()
{
  return m_baseParam;
}
