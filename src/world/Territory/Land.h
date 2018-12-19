#ifndef LAND_H_
#define LAND_H_
#include <Common.h>
#include "Exd/ExdDataGenerated.h"
#include "ForwardsZone.h"

namespace Sapphire
{
  namespace Data
  {
     using HousingLandSetPtr = std::shared_ptr< HousingLandSet >;
  }

  class Land
  {
  public:

    Land( uint16_t zoneId, uint8_t wardNum, uint8_t landId, uint32_t landSetId, Sapphire::Data::HousingLandSetPtr info );
    virtual ~Land();

    using LandInventoryMap = std::unordered_map< uint16_t, ItemContainerPtr >;

    //Primary state
    void setSize( uint8_t size );
    void setState( uint8_t state );
    void setSharing( uint8_t state );
    void setLandType( Common::LandType type );

    //Gerneral
    uint8_t getSize() const;
    uint8_t getState() const;
    uint8_t getSharing() const;
    uint32_t getLandSetId() const;
    uint8_t getWardNum() const;
    uint8_t getLandId() const;
    uint16_t getTerritoryTypeId() const;
    Common::LandType getLandType() const;
    Sapphire::HousePtr getHouse() const;
    Common::FFXIVARR_POSITION3 getMapMarkerPosition();

    //Free Comapny
    void setFreeCompany( uint32_t id, uint32_t icon, uint32_t color );
    uint32_t getFcId();
    uint32_t getFcIcon();
    uint32_t getFcColor();

    //Player
    void setPlayerOwner( uint64_t id );
    uint64_t getPlayerOwner();
    //Housing Functions
    void setCurrentPrice( uint32_t currentPrice );
    bool setPreset( uint32_t itemId );
    void updateLandDb();
    void update( uint32_t currTime );

    uint32_t getCurrentPrice() const;
    uint32_t getMaxPrice() const;
    uint32_t getDevaluationTime();

    //House tags
    void setLandTag( uint8_t slot, uint8_t tag );
    uint8_t getLandTag( uint8_t slot );

    ItemContainerPtr getItemContainer( uint16_t inventoryType ) const;

  private:
    uint32_t convertItemIdToHousingItemId( uint32_t itemId );
    void init();
    uint32_t getNextHouseId();

    uint8_t m_wardNum;
    uint8_t m_landId;
    uint32_t m_landSetId;
    uint16_t m_territoryTypeId;
    uint8_t m_size;
    uint8_t m_state;
    Common::LandType m_type;
    uint8_t m_iconAddIcon;
    uint32_t m_fcId; // unclear, may be wrong
    uint32_t m_fcIcon;
    uint32_t m_fcIconColor;

    Common::FFXIVARR_POSITION3 m_mapMarkerPosition;

    uint64_t m_ownerPlayerId;
    Sapphire::Data::HousingLandSetPtr m_landInfo;

    Sapphire::HousePtr m_pHouse;

    //item storage
    LandInventoryMap m_landInventoryMap;
    uint32_t m_maxPlacedExternalItems;
    uint32_t m_maxPlacedInternalItems;

    //price
    uint32_t m_initPrice;
    uint32_t m_nextDrop;
    uint32_t m_currentPrice;
    uint32_t m_minPrice;
    uint32_t m_maxPrice;

    //information
    char fcTag[7];
    uint8_t m_tag[3];
  };

}
#endif
