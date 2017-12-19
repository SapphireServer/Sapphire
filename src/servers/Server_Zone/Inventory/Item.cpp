#include <Server_Common/Common.h>
#include <Server_Common/Exd/ExdData.h>
#include "Item.h"

extern Core::Data::ExdData g_exdData;

Core::Item::Item()
{

}

Core::Item::Item( uint32_t catalogId ) :
   m_id( catalogId ),
   m_isHq( false )
{

}

Core::Item::Item( uint64_t uId, uint32_t catalogId, uint64_t model1, uint64_t model2, Common::ItemUICategory categoryId, bool isHq ) :
   m_id( catalogId ),
   m_uId( uId ),
   m_category( static_cast< Common::ItemUICategory >( categoryId ) ),
   m_model1( model1 ),
   m_model2( model2 ),
   m_isHq( isHq )
{
   auto itemInfo = g_exdData.getItemInfo( catalogId );
   m_delayMs = itemInfo->delayMs;
   m_physicalDmg = itemInfo->physical_damage;
   m_magicalDmg = itemInfo->magical_damage;
   m_weaponDmg = ( m_physicalDmg != 0 ) ? m_physicalDmg : m_magicalDmg;
   m_autoAttackDmg = static_cast< float >( m_weaponDmg * m_delayMs ) / 3000;
   m_itemLevel = itemInfo->item_level;
}

Core::Item::~Item()
{

}

float Core::Item::getAutoAttackDmg() const
{
   return m_autoAttackDmg;
}

uint16_t Core::Item::getDelay() const
{
   return m_delayMs;
}

uint16_t Core::Item::getPhysicalDmg() const
{
   return m_physicalDmg;
}

uint16_t Core::Item::getMagicalDmg() const
{
   return m_magicalDmg;
}

uint16_t Core::Item::getItemLevel() const
{
   return m_itemLevel;
}

uint16_t Core::Item::getWeaponDmg() const
{
   return m_weaponDmg;
}

bool Core::Item::isWeapon() const
{
   return (m_weaponDmg != 0);
}

uint32_t Core::Item::getId() const
{
   return m_id;
}

void Core::Item::setId( uint32_t id )
{
   m_id = id;
}

uint64_t Core::Item::getUId() const
{
   return m_uId;
}

void Core::Item::setUId( uint64_t id )
{
   m_uId = id;
}

void Core::Item::setStackSize( uint32_t size )
{
   m_stackSize = size;
}

uint32_t Core::Item::getStackSize() const
{
   return m_stackSize;
}

void Core::Item::setCategory( Common::ItemUICategory categoryId )
{
   m_category = categoryId;
}

Core::Common::ItemUICategory Core::Item::getCategory() const
{
   return m_category;
}

void Core::Item::setModelIds( uint64_t model1, uint64_t model2 )
{
   m_model1 = model1;
   m_model2 = model2;
}

uint64_t Core::Item::getModelId1() const
{
   return m_model1;
}

uint64_t Core::Item::getModelId2() const
{
   return m_model2;
}

bool Core::Item::isHq() const
{
   return m_isHq;
}

void Core::Item::setHq( bool isHq )
{
   m_isHq = isHq;
}
