#ifndef SAPPHIRE_TERRITORYMGR_H
#define SAPPHIRE_TERRITORYMGR_H

#include "Forwards.h"
#include <set>
#include <unordered_map>

namespace Core
{
   namespace Data
   {
      // TODO: this should actually not be here but should be generated in exdData aswell
      struct PlaceName;
      struct TerritoryType;
      struct InstanceContent;

      using PlaceNamePtr = boost::shared_ptr< PlaceName >;
      using TerritoryTypePtr = boost::shared_ptr< TerritoryType >;
      using InstanceContentPtr = boost::shared_ptr< InstanceContent >;
   }

   /*!
      \class TerritoryMgr_c
      \brief A class managing zones

      This class manages persistent and temporary instances alike.

   */
   class TerritoryMgr
   {

   public:
      enum TerritoryIntendedUse : uint8_t //ToDo: Add The Rest of The Territory Types and Have Better Names For Them
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
         ChocoboTutorial = 21,
         Wedding = 22,
         BeginnerTutorial = 27,
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

      /*! returns true if the territoryType is a default non-instanced zone */
      bool isDefaultTerritory( uint32_t territoryTypeId ) const;

      /*! creates a new instance for a given territoryTypeId */
      ZonePtr createTerritoryInstance( uint32_t territoryTypeId );

      ZonePtr createInstanceContent( uint32_t instanceContentId );

      /*! removes instance by instanceId, return true if successful */
      bool removeTerritoryInstance( uint32_t territoryTypeId );

      /*! returns a ZonePtr to the instance or nullptr if not found */
      ZonePtr getInstanceZonePtr( uint32_t instanceId ) const;

      /*! returns the cached detail of a territory, nullptr if not found */
      Data::TerritoryTypePtr getTerritoryDetail( uint32_t territoryTypeId ) const;

      /*! loop for processing territory logic, iterating all existing instances */
      void updateTerritoryInstances( uint32_t currentTime );

      /*! returns a ZonePositionPtr if found, else nullptr */
      ZonePositionPtr getTerritoryPosition( uint32_t territoryPositionId ) const;

      /*! returns a default Zone by territoryId
          TODO: Mind multiple instances?! */
      ZonePtr getZoneByTerriId( uint32_t territoryId ) const;

      bool movePlayer( uint32_t territoryId, Entity::PlayerPtr pPlayer );
      bool movePlayer( ZonePtr, Entity::PlayerPtr pPlayer );

      /*! returns an instancePtr if the player is still bound to an isntance */
      ZonePtr getLinkedInstance( uint32_t playerId ) const;

      void setCurrentFestival( uint16_t festivalId );
      void disableCurrentFestival();
      const uint16_t getCurrentFestival() const;

   private:
      using TerritoryTypeDetailCache = std::unordered_map< uint16_t, Data::TerritoryTypePtr >;
      using InstanceIdToZonePtrMap = std::unordered_map< uint32_t, ZonePtr >;
      using TerritoryIdToInstanceMap = std::unordered_map< uint16_t, InstanceIdToZonePtrMap >;
      using InstanceContentIdToInstanceMap = std::unordered_map< uint16_t, InstanceIdToZonePtrMap >;
      using PlayerIdToInstanceIdMap = std::unordered_map< uint32_t, uint32_t >;
      using PositionMap = std::unordered_map< int32_t, ZonePositionPtr >;
      using InstanceIdList = std::vector< uint32_t >;

      /*! map holding details for territory templates */
      TerritoryTypeDetailCache m_territoryTypeDetailCacheMap;

      /*! map holding actual instances of default territories */
      TerritoryIdToInstanceMap m_territoryInstanceMap;

      /*! map holding actual instances of InstanceContent */
      InstanceContentIdToInstanceMap m_instanceContentToInstanceMap;

      /*! flat map for easier lookup of instances by guid */
      InstanceIdToZonePtrMap m_instanceIdToZonePtrMap;

      /*! map holding positions for zonelines */
      PositionMap m_territoryPositionMap;

      /*! map storing playerIds to instanceIds, used for instanceContent */
      PlayerIdToInstanceIdMap m_playerIdToInstanceMap;

      /*! internal counter for instanceIds */
      uint32_t m_lastInstanceId;

      /*! set of ZonePtrs for quick iteration*/
      std::set< ZonePtr > m_zoneSet;

      /*! set of ZonePtrs for quick iteration*/
      std::set< ZonePtr > m_instanceZoneSet;

      /*! id of current festival to set for public zones from festival.exd */
      uint16_t m_currentFestival;

   public:
      /*! returns a list of instanceContent InstanceIds currently active */
      InstanceIdList getInstanceContentIdList( uint16_t instanceContentId ) const;

   };

}

#endif // SAPPHIRE_TERRITORYMGR_H
