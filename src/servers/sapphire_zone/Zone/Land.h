#ifndef LAND_H_
#define LAND_H_
#include <Common.h>
#include "ForwardsZone.h"

namespace Core
{
  namespace Data
  {
     using HousingLandSetPtr = std::shared_ptr< HousingLandSet >;
  }

  class Land
  {
  public:

    Land( uint16_t zoneId, uint8_t wardNum, uint8_t landId, uint32_t landSetId, Core::Data::HousingLandSetPtr info );
    virtual ~Land();

    void load();

    //Primary state
    void setHouseSize( uint8_t size );
    void setState( uint8_t state );
    void setOwnership( uint8_t state );
    void setSharing( uint8_t state );

    //Gerneral
    uint8_t getHouseSize();
    uint8_t getState();
    uint8_t getOwnership();
    uint8_t getSharing();

    //Free Comapny
    void setFreeCompany( uint32_t id, uint32_t icon, uint32_t color );
    uint32_t getFcId();
    uint32_t getFcIcon();
    uint32_t getFcColor();

    //House data
    void setHousePart( Common::HousePartSlot slot, uint16_t itemId );

    uint16_t getHousePart( Common::HousePartSlot slot );

    //Color
    void setColor( uint8_t slot, uint8_t color );
    uint8_t getColor( uint8_t slot );
    //Player
    void setPlayerOwner( uint32_t id );
    uint32_t getPlayerOwner();
    //Housing Functions
    void setPreset( uint32_t itemId );
    void UpdateDatabase();
    void Update( uint32_t currTime );
    void onUpdate();

    const Common::LandStruct& getLand();
    uint32_t getMaxItems();

    uint32_t getCurrentPrice() const;
    uint32_t getDevaluationTime();

  private:
    uint16_t convertItemIdToHousingItemId( uint16_t itemId );
    void init();

    uint8_t m_wardNum;
    uint8_t m_landId;
    uint32_t m_landSetId;
    uint16_t m_zoneId;
    Common::LandStruct m_land;
    uint32_t m_ownerPlayerId;
    Core::Data::HousingLandSetPtr m_landInfo;


    //item storage
    Core::ItemContainerPtr ItemsOutdoorContainer;
    uint32_t m_maxItems;

    //price
    uint32_t m_initPrice;
    uint32_t m_nextDrop;
    uint32_t m_devaluationTime;
    uint32_t m_currentPrice;
  };

}
#endif