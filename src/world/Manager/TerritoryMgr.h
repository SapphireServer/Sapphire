#ifndef SAPPHIRE_TERRITORYMGR_H
#define SAPPHIRE_TERRITORYMGR_H

#include "ForwardsZone.h"
#include <set>
#include <unordered_map>

namespace Sapphire::Data
{
  // TODO: this should actually not be here but should be generated in exdData aswell
  struct PlaceName;
  struct TerritoryType;
  struct InstanceContent;

  using PlaceNamePtr = std::shared_ptr< PlaceName >;
  using TerritoryTypePtr = std::shared_ptr< TerritoryType >;
  using InstanceContentPtr = std::shared_ptr< InstanceContent >;
}

namespace Sapphire::World::Manager
{
  /*!
     \class TerritoryMgr_c
     \brief A class managing zones

     This class manages persistent and temporary instances alike.

  */
  class TerritoryMgr
  {

  public:
    enum TerritoryIntendedUse : uint8_t //TODO: Add the rest of the territory types and have better names for them
    {
      Town = 0,
      OpenWorld = 1,
      Inn = 2,
      Dungeon = 3,
      JailArea = 5,
      OpeningArea = 6,
      BeforeTrialDung = 7,
      AllianceRaid = 8,
      OpenWorldInstanceBattle = 9,
      Trial = 10,
      RaidPublicArea = 12,
      HousingArea = 13,
      HousingPrivateArea = 14,
      MSQPrivateArea = 15,
      Raids = 16,
      RaidFights = 17,
      ChocoboSquare = 19,
      ChocoboTutorial = 21,
      Wedding = 22,
      GoldSaucer = 23,
      DiademV1 = 26,
      BeginnerTutorial = 27,
      PvPTheFeast = 28,
      MSQEventArea = 29,
      FreeCompanyGarrison = 30,
      PalaceOfTheDead = 31,
      TreasureMapInstance = 33,
      EventTrial = 36,
      TheFeastArea = 37, //custom match?
      DiademV2 = 38,
      PrivateEventArea = 40,
      Eureka = 41, // wat
      TheFeastCrystalTower = 42,
      LeapOfFaith = 44,
      MaskedCarnival = 45,
      OceanFishing = 46,
      DiademV3 = 47,
      Bozja = 48,
    };

    TerritoryMgr();

    /*! initializes the territoryMgr */
    bool init();

    bool createDefaultTerritories();

    bool createHousingTerritories();

    /*! caches TerritoryType details into m_territoryTypeMap */
    void loadTerritoryTypeDetailCache();

    /*! List of positions for zonelines */
    void loadTerritoryPositionMap();

    /*! returns true if the given territoryTypeId is in fact a valid zone
        based on informations in the dats ( checks if an entry in the dats exists trhough cache )  */
    bool isValidTerritory( uint32_t territoryTypeId ) const;

    /*! returns the next available instanceId */
    uint32_t getNextInstanceId();

    /*! returns true if the territoryType in question is not a persistant zone */
    bool isInstanceContentTerritory( uint32_t territoryTypeId ) const;

    /*! returns true if the territoryType in question is not a private zone */
    bool isPrivateTerritory( uint32_t territoryTypeId ) const;

    /*!
     * @brief Checks if a territory type is an internal housing area
     * @param territoryTypeId The territory to test
     * @return true if it is a housing area, false if not
     */
    bool isInternalEstateTerritory( uint32_t territoryTypeId ) const;

    /*! returns true if the territoryType is a default non-instanced zone */
    bool isDefaultTerritory( uint32_t territoryTypeId ) const;

    /*! returns true if the territoryType is a housing zone */
    bool isHousingTerritory( uint32_t territoryTypeId ) const;

    /*! creates a new instance for a given territoryTypeId */
    TerritoryPtr createTerritoryInstance( uint32_t territoryTypeId );

    TerritoryPtr createInstanceContent( uint32_t contentFinderConditionId );

    TerritoryPtr createQuestBattle( uint32_t contentFinderConditionId );

    TerritoryPtr createPublicContent( uint32_t contentFinderConditionId );
    TerritoryPtr createPublicContent( uint16_t contentId, uint16_t territoryId );

    void createAndJoinQuestBattle( Entity::Player& player, uint16_t contentFinderConditionId );

    TerritoryPtr findOrCreateHousingInterior( const Common::LandIdent landIdent );

    /*! removes instance by instanceId, return true if successful */
    bool removeTerritoryInstance( uint32_t guId );

    /*! returns a TerritoryPtr to the instance or nullptr if not found */
    TerritoryPtr getTerritoryByGuId( uint32_t guId ) const;

    /*! returns the cached detail of a territory, nullptr if not found */
    Data::TerritoryTypePtr getTerritoryDetail( uint32_t territoryTypeId ) const;

    /*! loop for processing territory logic, iterating all existing instances */
    void updateTerritoryInstances( uint64_t tickCount );

    /*! returns a ZonePositionPtr if found, else nullptr */
    ZonePositionPtr getTerritoryPosition( uint32_t territoryPositionId ) const;

    /*! returns a default Zone by territoryTypeId
        TODO: Mind multiple instances?! */
    TerritoryPtr getZoneByTerritoryTypeId( uint32_t territoryTypeId ) const;

    /*! returns a Zone by landSetId */
    TerritoryPtr getZoneByLandSetId( uint32_t landSetId ) const;

    bool movePlayer( uint32_t territoryTypeId, Entity::PlayerPtr pPlayer );

    bool movePlayer( TerritoryPtr, Entity::PlayerPtr pPlayer );

    /*! returns an instancePtr if the player is still bound to an isntance */
    TerritoryPtr getLinkedInstance( uint32_t playerId ) const;

    /*!
     * @brief Sets the current festival for every zone
     * @param festivalId A valid festival id from festival.exd
     * @param additionalFestival A valid festival id from festival.exd, this is shown in addition to the first festival
     */
    void setCurrentFestival( uint16_t festivalId, uint16_t additionalFestival = 0 );

    /*!
     * @brief Disables the current festival(s) in every zone
     */
    void disableCurrentFestival();

    /*!
     * @brief Gets the current festival set on the server
     * @return a pair with the 2 festivals currently active
     */
    const std::pair< uint16_t, uint16_t >& getCurrentFestival() const;

    float getInRangeDistance() const;

  private:
    using TerritoryTypeDetailCache = std::unordered_map< uint16_t, Data::TerritoryTypePtr >;
    using InstanceIdToTerritoryPtrMap = std::unordered_map< uint32_t, TerritoryPtr >;
    using LandSetIdToTerritoryPtrMap = std::unordered_map< uint32_t, TerritoryPtr >;
    using TerritoryTypeIdToInstanceMap = std::unordered_map< uint16_t, InstanceIdToTerritoryPtrMap >;
    using InstanceContentIdToInstanceMap = std::unordered_map< uint16_t, InstanceIdToTerritoryPtrMap >;
    using QuestBattleIdToInstanceMap = std::unordered_map< uint16_t, InstanceIdToTerritoryPtrMap >;
    using QuestBattleIdToContentFinderCondMap = std::unordered_map< uint16_t, uint16_t >;
    using PublicContentIdToInstanceMap = std::unordered_map< uint16_t, InstanceIdToTerritoryPtrMap >;
    using PlayerIdToInstanceIdMap = std::unordered_map< uint32_t, uint32_t >;
    using PositionMap = std::unordered_map< int32_t, ZonePositionPtr >;
    using InstanceIdList = std::vector< uint32_t >;
    using LandIdentToTerritoryPtrMap = std::unordered_map< uint64_t, TerritoryPtr >;

    /*! map holding details for territory templates */
    TerritoryTypeDetailCache m_territoryTypeDetailCacheMap;

    /*! map holding actual instances of default territories */
    TerritoryTypeIdToInstanceMap m_territoryTypeIdToInstanceGuidMap;

    /*! map holding actual instances of default territories */
    LandSetIdToTerritoryPtrMap m_landSetIdToTerritoryPtrMap;

    /*! map holding actual instances of InstanceContent */
    InstanceContentIdToInstanceMap m_instanceContentIdToInstanceMap;

    /*! map holding actual instances of QuestBattle */
    QuestBattleIdToInstanceMap m_questBattleIdToInstanceMap;

    /*! map holding actual instances of PublicContent */
    PublicContentIdToInstanceMap m_publicContentIdToInstanceMap;

    /*! flat map for easier lookup of instances by guid */
    InstanceIdToTerritoryPtrMap m_guIdToTerritoryPtrMap;

    /*! map holding positions for zonelines */
    PositionMap m_territoryPositionMap;

    /*! map storing playerIds to instanceIds, used for instanceContent */
    PlayerIdToInstanceIdMap m_playerIdToInstanceMap;

    /*! map for storing landident to zones, used for internal housing zones */
    LandIdentToTerritoryPtrMap m_landIdentToTerritoryPtrMap;

    /*! internal counter for instanceIds */
    uint32_t m_lastInstanceId;

    /*! set of TerritoryPtrs for quick iteration*/
    std::set< TerritoryPtr > m_territorySet;

    /*! set of TerritoryPtrs for quick iteration*/
    std::set< TerritoryPtr > m_instanceZoneSet;

    /*! current festival(s) to set for public zones from festival.exd */
    std::pair< uint16_t, uint16_t > m_currentFestival;

    /*! Max distance at which actors in range of a player are sent */
    float m_inRangeDistance;

    /*! Map used to find a contentFinderConditionID to a questBattle */
    QuestBattleIdToContentFinderCondMap m_questBattleToContentFinderMap;

  public:
    /*! returns a list of instanceContent InstanceIds currently active */
    InstanceIdList getInstanceContentIdList( uint16_t instanceContentId ) const;

  };

}

#endif // SAPPHIRE_TERRITORYMGR_H
