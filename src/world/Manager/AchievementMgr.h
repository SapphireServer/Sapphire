#pragma once

#include <unordered_map>
#include <vector>
#include <algorithm>
#include <type_traits>

#include <Service.h>
#include <Common.h>

#include "Actor/Player.h"

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

    /// <summary>
    /// check if player has an achievement by its given id
    /// </summary>
    /// <param name="player"></param>
    /// <param name="achievementId"></param>
    /// <returns>true/false</returns>
    bool hasAchievementUnlocked( Entity::Player& player, uint32_t achievementId );

    void unlockAchievement( Entity::Player& player, uint32_t achievementId );

    /// <summary>
    /// get a pair of current progress and maximum count for a given achievement ID
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

    std::shared_ptr< Excel::ExcelStruct< Excel::Achievement > > getAchievementDetail( uint32_t achvId ) const;
    const std::vector< uint32_t >& getAchievementIdByType( Common::Achievement::Type type ) const;
    const std::vector< uint32_t >& getAchievementIdByType( uint32_t type ) const;

    /// <summary>
    /// get a key for merged achievements (type:subtype) that have progress data
    /// </summary>
    /// <param name="achvType"></param>
    /// <param name="argument"></param>
    /// <returns>data key for given type:subtype</returns>
    Common::AchievementDataKey getKeyFromType( Common::Achievement::Type achvType, int32_t argument );

    /// <summary>
    /// parse and unlock achievements linked to a given achievement Id
    /// </summary>
    /// <param name="player"></param>
    /// <param name="achievementId"></param>
    void handleLinkedAchievementsForId( Entity::Player& player, uint32_t achievementId );

    template< typename AchievementTypeT, AchievementTypeT achievementType >
    inline void progressAchievement( Entity::Player& player, int32_t argument, uint32_t progressCount );
  };

  
  template<>
  inline void AchievementMgr::progressAchievement< Common::Achievement::Type, Common::Achievement::Type::General >( Entity::Player& player, int32_t subtype, uint32_t progressCount )
  {
    auto& achvDataList = player.getAchievementDataList();

    auto dataKey = getKeyFromType( Common::Achievement::Type::General, subtype );

    if( !achvDataList.count( dataKey.u32 ) )
      achvDataList[ dataKey.u32 ] = 0;

    achvDataList[ dataKey.u32 ] += progressCount;

    const auto achvIdList = getAchievementIdByType( dataKey.u32 );

    for( auto achvId : achvIdList )
    {
      if( hasAchievementUnlocked( player, achvId ) )
        continue;

      auto pAchv = getAchievementDetail( achvId );
      if( !pAchv )
        continue;

      auto achvExdData = pAchv->data();

      if( achvExdData.ConditionArg[ 1 ] <= achvDataList[ dataKey.u32 ] )
        unlockAchievement( player, achvId );
    }
  }

  template<>
  inline void AchievementMgr::progressAchievement< Common::Achievement::Type, Common::Achievement::Type::Classjob >( Entity::Player& player, int32_t classJob, uint32_t unused )
  {
    auto& achvDataList = player.getAchievementDataList();

    auto dataKey = getKeyFromType( Common::Achievement::Type::Classjob, classJob );

    if( !achvDataList.count( dataKey.u32 ) )
      achvDataList[ dataKey.u32 ] = 0;

    auto level = player.getLevelForClass( static_cast< Common::ClassJob >( classJob ) );

    achvDataList[ dataKey.u32 ] = level;

    const auto achvIdList = getAchievementIdByType( dataKey.u32 );

    for( auto achvId : achvIdList )
    {
      if( hasAchievementUnlocked( player, achvId ) )
        continue;

      auto pAchv = getAchievementDetail( achvId );
      if( !pAchv )
        continue;

      auto achvExdData = pAchv->data();

      if( achvExdData.ConditionArg[ 1 ] <= achvDataList[ dataKey.u32 ] )
        unlockAchievement( player, achvId );
      
    }
  }
}
