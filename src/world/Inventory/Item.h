#ifndef _ITEM_H_
#define _ITEM_H_

#include <Common.h>
#include "ForwardsZone.h"

namespace Sapphire
{

  class Item
  {

  public:

    struct BaseParamStruct
    {
      uint8_t baseParam;
      int16_t value;
    };

    Item( uint64_t uId, uint32_t catalogId, FrameworkPtr pFw, bool isHq = false );

    virtual ~Item() = default;

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

    uint16_t getDefense() const;

    uint16_t getDefenseMag() const;

    bool isWeapon() const;

    float getAutoAttackDmg() const;

    uint16_t getItemLevel() const;

    uint32_t getMaxStackSize() const;

    uint16_t getDurability() const;
    void setDurability( uint16_t durability );

    uint16_t getStain() const;
    void setStain( uint16_t stain );

    uint32_t getAdditionalData() const;

    void setSpiritbond( uint16_t spiritbond );
    uint16_t getSpiritbond() const;

    void setReservedFlag( uint32_t flag );
    uint32_t getReservedFlag() const;

    BaseParamStruct* getBaseParams();

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
    uint16_t m_spiritBond;
    uint32_t m_reservedFlag;

    uint32_t m_blockRate;
    uint32_t m_block;
    uint32_t m_defense;
    uint32_t m_defenseMag;

    FrameworkPtr m_pFw;
    uint32_t m_additionalData;

    BaseParamStruct m_baseParam[6];

  };

}

#endif
