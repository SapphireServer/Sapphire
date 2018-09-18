#ifndef _ITEM_H_
#define _ITEM_H_

#include <Common.h>

namespace Core {

class Item
{

public:
  Item( uint64_t uId, uint32_t catalogId, uint64_t model1, uint64_t model2, bool isHq = false );

  ~Item() = default;

  uint32_t getId() const;

  void setId( uint32_t id );

  uint64_t getUId() const;

  void setUId( uint64_t id );

  void setStackSize( uint32_t size );

  uint32_t getStackSize() const;

  void setCategory( Common::ItemUICategory categoryId );

  Common::ItemUICategory getCategory() const;

  void setModelIds( uint64_t model1, uint64_t model2 );

  uint64_t getModelId1() const;

  uint64_t getModelId2() const;

  bool isHq() const;

  void setHq( bool isHq );

  uint16_t getDelay() const;

  uint16_t getPhysicalDmg() const;

  uint16_t getMagicalDmg() const;

  uint16_t getWeaponDmg() const;

  bool isWeapon() const;

  float getAutoAttackDmg() const;

  uint16_t getItemLevel() const;

  uint32_t getMaxStackSize() const;

  uint16_t getDurability() const;
  void setDurability( uint16_t durability );

  uint16_t getStain() const;
  void setStain( uint16_t stain );


protected:
  uint32_t m_id;

  uint64_t m_uId;

  Common::ItemUICategory m_category;

  uint32_t m_stackSize;
  uint32_t m_maxStackSize;
  std::vector< uint8_t > m_classJobList;

  uint64_t m_model1;
  uint64_t m_model2;

  bool m_isHq;

  uint16_t m_delayMs;
  uint16_t m_physicalDmg;
  uint16_t m_magicalDmg;
  uint16_t m_weaponDmg;
  float m_autoAttackDmg;
  uint16_t m_itemLevel;
  uint16_t m_durability;
  uint16_t m_stain;

};

}

#endif
