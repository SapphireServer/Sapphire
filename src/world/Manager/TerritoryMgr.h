#pragma once
#include "ForwardsZone.h"
#include <set>
#include <unordered_map>
#include <Exd/Structs.h>

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

namespace Sapphire
{
  class Territory;
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
      TheFeastArea = 37,
      PrivateEventArea = 40,
      //Eureka = 41, // wat
    };

    TerritoryMgr();

    /*! initializes the territoryMgr */
    bool init();

    bool createDefaultTerritories();

    bool createHousingTerritories();

    /*! caches TerritoryType details into m_territoryTypeMap */
    void loadTerritoryTypeDetailCache();

    bool joinWorld( Entity::Player& player );

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

    /*! returns the index of the housing area */
    uint8_t getHousingIndex( uint32_t territoryTypeId ) const;

    uint32_t getInstanceContentId( uint32_t territoryTypeId ) const;

    /*! creates a new instance for a given territoryTypeId */
    TerritoryPtr createTerritoryInstance( uint32_t territoryTypeId );

    TerritoryPtr createInstanceContent( uint32_t contentFinderId );

    TerritoryPtr createQuestBattle( uint32_t contentFinderConditionId );

    void createAndJoinQuestBattle( Entity::Player& player, uint16_t contentFinderConditionId );

    TerritoryPtr findOrCreateHousingInterior( const Common::LandIdent landIdent );

    /*! removes instance by instanceId, return true if successful */
    bool removeTerritoryInstance( uint32_t guId );

    /*! returns a TerritoryPtr to the instance or nullptr if not found */
    TerritoryPtr getTerritoryByGuId( uint32_t guId ) const;

    /*! returns the cached detail of a territory, nullptr if not found */
    Excel::ExcelStructPtr< Excel::TerritoryType > getTerritoryDetail( uint32_t territoryTypeId ) const;

    /*! loop for processing territory logic, iterating all existing instances */
    void updateTerritoryInstances( uint64_t tickCount );

    /*! returns a default Zone by territoryTypeId
        TODO: Mind multiple instances?! */
    TerritoryPtr getTerritoryByTypeId( uint32_t territoryTypeId ) const;

    bool movePlayer( Sapphire::Territory& teri, Entity::Player& player );

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

  private:
    using TerritoryTypeDetailCache = std::unordered_map< uint16_t, std::shared_ptr< Excel::ExcelStruct< Excel::TerritoryType > > >;
    using InstanceIdToTerritoryPtrMap = std::unordered_map< uint32_t, TerritoryPtr >;
    using TerritoryTypeIdToInstanceMap = std::unordered_map< uint16_t, InstanceIdToTerritoryPtrMap >;
    using InstanceContentIdToInstanceMap = std::unordered_map< uint16_t, InstanceIdToTerritoryPtrMap >;
    using QuestBattleIdToInstanceMap = std::unordered_map< uint16_t, InstanceIdToTerritoryPtrMap >;
    using QuestBattleIdToContentFinderCondMap = std::unordered_map< uint16_t, uint16_t >;
    using PlayerIdToInstanceIdMap = std::unordered_map< uint32_t, uint32_t >;
    using InstanceIdList = std::vector< uint32_t >;
    using LandIdentToTerritoryPtrMap = std::unordered_map< uint64_t, TerritoryPtr >;

    /*! map holding details for territory templates */
    TerritoryTypeDetailCache m_territoryTypeDetailCacheMap;

    /*! map holding actual instances of default territories */
    TerritoryTypeIdToInstanceMap m_territoryTypeIdToInstanceGuidMap;

    /*! map holding actual instances of InstanceContent */
    InstanceContentIdToInstanceMap m_instanceContentIdToInstanceMap;

    /*! map holding actual instances of InstanceContent */
    QuestBattleIdToInstanceMap m_questBattleIdToInstanceMap;

    /*! flat map for easier lookup of instances by guid */
    InstanceIdToTerritoryPtrMap m_guIdToTerritoryPtrMap;

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

    /*! Map used to find a contentFinderConditionID to a questBattle */
    QuestBattleIdToContentFinderCondMap m_questBattleToContentFinderMap;

  public:
    /*! returns a list of instanceContent InstanceIds currently active */
    InstanceIdList getInstanceContentIdList( uint16_t instanceContentId ) const;

  };

}

