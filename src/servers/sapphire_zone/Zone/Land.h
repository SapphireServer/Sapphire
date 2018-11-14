#ifndef LAND_H_
#define LAND_H_
#include <Common.h>
#include "Exd/ExdDataGenerated.h"
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
    void setLandName( const std::string& name );
    void setLandType( Common::LandType type );

    //Gerneral
    uint8_t getPlotSize() const;
    uint8_t getState() const;
    uint8_t getOwnership() const;
    uint8_t getSharing() const;
    uint32_t getLandSetId() const;
    uint8_t getWardNum() const;
    uint8_t getLandId() const;
    uint16_t getZoneId() const;
    std::string getLandName() const;
    Common::LandType getLandType() const;

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
    void UpdateLandDb();
    void Update( uint32_t currTime );

    uint32_t getMaxItems();

    uint32_t getCurrentPrice() const;
    uint32_t getDevaluationTime();

    //House tags
    void setLandTag( uint8_t slot, uint8_t tag );
    uint8_t getLandTag( uint8_t slot );

  private:
    uint16_t convertItemIdToHousingItemId( uint16_t itemId );
    void init();

    uint8_t m_wardNum;
    uint8_t m_landId;
    uint32_t m_landSetId;
    uint16_t m_zoneId;
    uint8_t m_size;
    uint8_t m_state;
    uint8_t m_iconColor;
    uint8_t m_iconAddIcon;
    uint32_t m_fcId;
    uint32_t m_fcIcon;
    uint32_t m_fcIconColor;

    Common::LandType m_type;
    uint32_t m_ownerPlayerId;
    Core::Data::HousingLandSetPtr m_landInfo;


    //item storage
    Core::ItemContainerPtr ItemsOutdoorContainer;
    uint32_t m_maxItems;

    //price
    uint32_t m_initPrice;
    uint32_t m_nextDrop;
    uint32_t m_currentPrice;
    uint32_t m_minPrice;

    //information
    char m_landName[23];
    char m_landMsg[193];
    char m_ownerName[31];
    char fcTag[7];
    uint8_t m_tag[3];
  };

}
#endif
