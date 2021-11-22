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

    Land( uint16_t zoneId, uint8_t wardNum, uint8_t landId, uint32_t landSetId,
          Sapphire::Data::HousingLandSetPtr info );
    virtual ~Land();
    void init( Common::LandType type, Common::HouseSize size, Common::HouseStatus state, uint32_t currentPrice, uint64_t ownerId, uint64_t houseId );

    using LandInventoryMap = std::unordered_map< uint16_t, ItemContainerPtr >;
    using InvMaxItemsPair = std::pair< uint16_t, uint16_t >;

    //Primary state
    void setSize( Common::HouseSize size );
    void setStatus( Common::HouseStatus state );
    void setSharing( uint8_t state );
    void setLandType( Common::LandType type );

    //Gerneral
    Common::HouseSize getSize() const;
    Common::HouseStatus getStatus() const;
    uint8_t getSharing() const;
    uint32_t getLandSetId() const;
    Common::LandType getLandType() const;
    void setHouse( Sapphire::HousePtr );
    Sapphire::HousePtr getHouse() const;
    Common::FFXIVARR_POSITION3 getMapMarkerPosition();
    Common::LandIdent getLandIdent() const;

    //Free Comapny
    void setFreeCompany( uint32_t id, uint32_t icon, uint32_t color );
    uint32_t getFcId();
    uint32_t getFcIcon();
    uint32_t getFcColor();

    //Player
    void setOwnerId( uint64_t id );
    uint64_t getOwnerId();
    //Housing Functions
    void setCurrentPrice( uint32_t currentPrice );
    bool setPreset( uint32_t itemId );
    void updateLandDb();
    void update( uint64_t tickCount );

    uint32_t getCurrentPrice() const;
    uint32_t getMaxPrice() const;
    uint32_t getDevaluationTime();

    //House tags
    void setLandTag( uint8_t slot, uint8_t tag );
    uint8_t getLandTag( uint8_t slot );

    InvMaxItemsPair getInventoryItemMax() const;

  private:
    uint32_t getNextHouseId();

    Common::LandIdent m_landIdent;

    uint32_t m_landSetId;
    Common::HouseSize m_size;
    Common::HouseStatus m_state;
    Common::LandType m_type;
    uint8_t m_iconAddIcon;
    uint32_t m_fcId; // unclear, may be wrong
    uint32_t m_fcIcon;
    uint32_t m_fcIconColor;

    Common::FFXIVARR_POSITION3 m_mapMarkerPosition;

    uint64_t m_ownerId;
    Sapphire::Data::HousingLandSetPtr m_landInfo;

    Sapphire::HousePtr m_pHouse;

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
