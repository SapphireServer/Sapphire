#pragma once

#include <unordered_map>
#include <vector>
#include <algorithm>
#include <type_traits>

#include <Service.h>
#include <Common.h>

#include "Actor/Player.h"
#include "Manager/PlayerMgr.h"

namespace Sapphire::World::Manager
{
  class AchievementMgr
  {
  public:
    AchievementMgr() = default;
    ~AchievementMgr() = default;

    bool cacheAchievements();

    /// <summary>
    /// progress an achievement by its given properties
    /// each type has a specific logic for progress, attention should be given to the type being passed
    /// optional parameter for overriding the amount to increment a given progress by
    /// 
    /// example usage for Achievement::Type::General:
    ///
    /// To Crush Your Enemies I
    /// Defeat 100 enemies.
    ///
    /// type (col[7]): 1 -> Common::Achievement::Type::General
    /// subtype (col[8]): 11 -> Common::Achievement::GeneralSubtype::EnemyDefeatCount
    ///
    /// progressAchievementByType< Common::Achievement::Type::General >( player, GeneralSubtype::EnemyDefeatCount );
    ///
    /// example usage for Achievement::Type::ClassJob:
    ///
    /// progressAchievementByType< Common::Achievement::Type::Classjob >( player, static_cast< uint32_t >( player.getClass() ) );
    /// 
    /// </summary>
    /// <typeparam name="AchievementType"></typeparam>
    /// <param name="player"></param>
    /// <param name="argument"></param>
    /// <param name="progressCount"></param>
    template < auto AchievementType >
    void progressAchievementByType( Entity::Player& player, int32_t argument, uint32_t progressCount = 1 )
    {
      progressAchievement< decltype( AchievementType ), AchievementType >( player, argument, progressCount );
    }

    // Similar to progressAchievementByType but update player's m_achievementData with the actual achievement value.
    // Used to return the value of packet ACHIEVEMENT_REQUEST_RATE in case of player.getAchievementData().progressData empty
    template< auto AchievementType >
    void retrieveProgressAchievementByType( Entity::Player& player, int32_t argument, uint32_t progressCount = 1 )
    {
      retrieveProgressAchievement< decltype( AchievementType ), AchievementType >( player, argument, progressCount );
    }

    /// <summary>
    /// check if player has an achievement by its given id
    /// </summary>
    /// <param name="player"></param>
    /// <param name="achievementId"></param>
    /// <returns>true/false</returns>
    bool hasAchievementUnlocked( Entity::Player& player, uint32_t achievementId );

    /// <summary>
    /// get a pair of current progress and maximum count for a given achievement id
    /// </summary>
    /// <param name="player"></param>
    /// <param name="achievementId"></param>
    /// <returns>pair of current and maximum progress</returns>
    std::pair< uint32_t, uint32_t > getAchievementDataById( Entity::Player& player, uint32_t achievementId );
  private:
    // map achievement IDs to achv data
    using AchievementDetailCache = std::unordered_map< uint32_t, std::shared_ptr< Excel::ExcelStruct< Excel::Achievement > > >;
    // map achievement keys (either type or union key:subtype) to achievement IDs
    using AchievementKeyCache = std::unordered_map< uint32_t, std::vector< uint32_t > >;

    AchievementDetailCache m_achievementDetailCacheMap;
    AchievementKeyCache m_achievementKeyCacheMap;

    // cache fetch functions
    std::shared_ptr< Excel::ExcelStruct< Excel::Achievement > > getAchievementDetail( uint32_t achvId ) const;
    std::vector< uint32_t > getAchievementIdByType( Common::Achievement::Type type ) const;
    std::vector< uint32_t > getAchievementIdByType( uint32_t type ) const;

    /// <summary>
    /// get a key for merged achievements (type:subtype) that have progress data
    /// </summary>
    /// <param name="achvType"></param>
    /// <param name="argument"></param>
    /// <returns>data key for given type:subtype</returns>
    Common::AchievementDataKey getKeyFromType( Common::Achievement::Type achvType, int32_t argument );

    /// <summary>
    /// parse and unlock achievements linked to a given achievement id
    /// </summary>
    /// <param name="player"></param>
    /// <param name="achievementId"></param>
    void handleLinkedAchievementsForId( Entity::Player& player, uint32_t achievementId );

    /// <summary>
    /// internal use: unlock achievement in the player achievement unlock flagmask, from a given id
    /// progressAchievement should be used instead, due to certain achievements using progress data
    /// </summary>
    /// <param name="player"></param>
    /// <param name="achievementId"></param>
    void unlockAchievement( Entity::Player& player, uint32_t achievementId );

    template< typename AchievementTypeT, AchievementTypeT achievementType >
    inline void progressAchievement( Entity::Player& player, int32_t argument, uint32_t progressCount );
    template< typename AchievementTypeT, AchievementTypeT achievementType >
    inline void retrieveProgressAchievement( Entity::Player& player, int32_t argument, uint32_t progressCount );
  };

  
  template<>
  inline void AchievementMgr::progressAchievement< Common::Achievement::Type, Common::Achievement::Type::General >( Entity::Player& player, int32_t subtype, uint32_t progressCount )
  {
    auto achvData = player.getAchievementData();

    auto dataKey = getKeyFromType( Common::Achievement::Type::General, subtype );

    if( !achvData.progressData.count( dataKey.u32 ) )
      achvData.progressData[ dataKey.u32 ] = 0;

    achvData.progressData[ dataKey.u32 ] += progressCount;

    player.setAchievementData( achvData );

    const auto achvIdList = getAchievementIdByType( dataKey.u32 );

    for( auto achvId : achvIdList )
    {
      if( hasAchievementUnlocked( player, achvId ) )
        continue;

      auto pAchv = getAchievementDetail( achvId );
      if( !pAchv )
        continue;

      auto& achvExdData = pAchv->data();

      if( achvExdData.ConditionArg[ 1 ] <= static_cast< int32_t >( achvData.progressData[ dataKey.u32 ] ) )
        unlockAchievement( player, achvId );
    }
  }

  template<>
  inline void AchievementMgr::progressAchievement< Common::Achievement::Type, Common::Achievement::Type::Classjob >( Entity::Player& player, int32_t classJob, uint32_t unused )
  {
    auto achvData = player.getAchievementData();

    auto dataKey = getKeyFromType( Common::Achievement::Type::Classjob, classJob );

    if( !achvData.progressData.count( dataKey.u32 ) )
      achvData.progressData[ dataKey.u32 ] = 0;

    auto level = player.getLevelForClass( static_cast< Common::ClassJob >( classJob ) );

    achvData.progressData[ dataKey.u32 ] = level;

    const auto achvIdList = getAchievementIdByType( dataKey.u32 );

    for( auto achvId : achvIdList )
    {
      if( hasAchievementUnlocked( player, achvId ) )
        continue;

      auto pAchv = getAchievementDetail( achvId );
      if( !pAchv )
        continue;

      auto& achvExdData = pAchv->data();

      if( achvExdData.ConditionArg[ 1 ] <= static_cast< int32_t >( achvData.progressData[ dataKey.u32 ] ) )
        unlockAchievement( player, achvId );
    }
  }

  template<>
  inline void AchievementMgr::retrieveProgressAchievement< Common::Achievement::Type, Common::Achievement::Type::Classjob >( Entity::Player& player, int32_t classJob, uint32_t unused )
  {
    auto achvData = player.getAchievementData();

    auto dataKey = getKeyFromType( Common::Achievement::Type::Classjob, classJob );

    auto level = player.getLevelForClass( static_cast< Common::ClassJob >( classJob ) );

    achvData.progressData[ dataKey.u32 ] = level;

    player.setAchievementData( achvData );
  }

  template<>
  inline void AchievementMgr::progressAchievement< Common::Achievement::Type, Common::Achievement::Type::Quest >( Entity::Player& player, int32_t questId, uint32_t unused )
  {
    auto& achvDataList = player.getAchievementData().progressData;

    // get achievements that need all achv in args completed
    const auto questAchvAllList = getAchievementIdByType( Common::Achievement::Type::Quest );
    // get achievements that need any of the achvs in args completed
    const auto questAchvAnyList = getAchievementIdByType( Common::Achievement::Type::QuestAny );

    // handle achv type for all quests in args completed
    for( auto achvId : questAchvAllList )
    {
      if( hasAchievementUnlocked( player, achvId ) )
        continue;

      auto pAchv = getAchievementDetail( achvId );

      auto achvExdData = pAchv->data();

      std::set< uint16_t > linkedQuests{ std::make_move_iterator( std::begin( achvExdData.ConditionArg ) ),
                                      std::make_move_iterator( std::end( achvExdData.ConditionArg ) ) };

      // clear empty achievement links
      linkedQuests.erase( 0 );

      // check if passed quest ID is tied to this achievement
      if( !linkedQuests.count( questId ) )
        continue;

      // verify if player has all the required quests completed
      bool hasAllAchievements = true;
      for( const auto questId : linkedQuests )
      {
        if( !player.isQuestCompleted( questId ) )
        {
          hasAllAchievements = false;
          break;
        }
      }

      // unlock achievement if all required quests are completed
      if( hasAllAchievements )
        unlockAchievement( player, achvId );
    }

    // handle achv type for all quests in args completed
    for( auto achvId : questAchvAnyList )
    {
      if( hasAchievementUnlocked( player, achvId ) )
        continue;

      auto pAchv = getAchievementDetail( achvId );

      auto achvExdData = pAchv->data();

      std::set< int32_t > linkedQuests{ std::make_move_iterator( std::begin( achvExdData.ConditionArg ) ),
                                      std::make_move_iterator( std::end( achvExdData.ConditionArg ) ) };

      // clear empty quest ids
      linkedQuests.erase( 0 );

      // check if passed quest ID is tied to this achievement
      if( !linkedQuests.count( questId ) )
        continue;

      // verify if player has any of the required quests completed
      bool hasAllAchievements = true;
      for( const auto questId : linkedQuests )
      {
        if( player.isQuestCompleted( questId ) )
        {
          unlockAchievement( player, achvId );
          break;
        }
      }
    }
  }

  template<>
  inline void AchievementMgr::retrieveProgressAchievement< Common::Achievement::Type, Common::Achievement::Type::Quest >( Entity::Player& player, int32_t classJob, uint32_t unused )
  {
    auto achvData = player.getAchievementData();

    auto dataKey = getKeyFromType( Common::Achievement::Type::Classjob, classJob );

    auto level = player.getLevelForClass( static_cast< Common::ClassJob >( classJob ) );

    achvData.progressData[ dataKey.u32 ] = level;

    player.setAchievementData( achvData );
  }

  template<>
  inline void AchievementMgr::progressAchievement< Common::Achievement::Type, Common::Achievement::Type::MapDiscovery >( Entity::Player& player, int32_t mapId, uint32_t allDiscovered )
  {
    auto achvData = player.getAchievementData();

    auto dataKey = getKeyFromType( Common::Achievement::Type::MapDiscovery, mapId );

    if( !achvData.progressData.count( dataKey.u32 ) )
      achvData.progressData[ dataKey.u32 ] = 0;

    achvData.progressData[ dataKey.u32 ] = allDiscovered;

    const auto achvIdList = getAchievementIdByType( Common::Achievement::Type::MapDiscovery );

    for( auto achvId : achvIdList )
    {

      if( hasAchievementUnlocked( player, achvId ) )
        continue;

      auto pAchv = getAchievementDetail( achvId );
      if( !pAchv || pAchv->_data.ConditionArg[0] != mapId )
        continue;

      if( allDiscovered )
        unlockAchievement( player, achvId );
    }
  }

  template<>
  inline void AchievementMgr::retrieveProgressAchievement< Common::Achievement::Type, Common::Achievement::Type::MapDiscovery >( Entity::Player& player, int32_t mapId, uint32_t unused )
  {
    auto achvData = player.getAchievementData();

    auto dataKey = getKeyFromType( Common::Achievement::Type::MapDiscovery, mapId );

    bool discovered = playerMgr().isAllAreaDiscovered( player, mapId );

    achvData.progressData[ dataKey.u32 ] = discovered;

    player.setAchievementData( achvData );
  }
}
