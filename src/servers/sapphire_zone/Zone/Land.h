#ifndef LAND_H_
#define LAND_H_
#include <Common.h>
#include "ForwardsZone.h"

namespace Core
{
  class Land
  {
  public:
    enum HouseSizeType : uint8_t
    {
      //noneHouse,
      smallHouse,
      mediumHouse,
      bigHouse
    };

    enum HouseStateType : uint8_t
    {
      none,
      forSale,
      sold,
      fcHouse,
      privateHouse
    };

    enum HouseIconAdd : uint8_t
    {
      heart = 0x06
    };

    Land( uint16_t zoneId, uint8_t wardNum, uint8_t landId );
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
    void setRoof( uint16_t itemId );
    void setFacade( uint16_t itemId );
    void setWindow( uint16_t itemId );
    void setDoor( uint16_t itemId );
    void setFloorWall( uint16_t itemId );
    void setFloorFlooring( uint16_t itemId );
    void setWall( uint16_t itemId );
    void setSign( uint16_t itemId );
    void setBasementWall( uint16_t itemId );

    uint16_t getRoof();
    uint16_t getFacade();
    uint16_t getWindow();
    uint16_t getDoor();
    uint16_t getFloorWall();
    uint16_t getFloorFlooring();
    uint16_t getWall();
    uint16_t getSign();
    uint16_t getBasememtWall();

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
    uint32_t getLandKey();

    Common::LandStruct getLand();
    uint32_t getMaxItems();

  private:
    uint32_t convertItemIdToHousingItemId( uint32_t itemId );
    void Init();

    uint32_t m_landKey;
    uint8_t m_wardNum;
    uint8_t m_landId;
    uint16_t m_zoneId;
    Common::LandStruct m_land;
    uint32_t m_ownerPlayerId;


    //item storage
    Core::ItemContainerPtr ItemsOutdoorContainer;
    uint32_t m_maxItems;

    //price
    uint32_t m_initPrice;
    uint32_t m_nextDrop;
    uint32_t m_currentPrice;
  };

}
#endif