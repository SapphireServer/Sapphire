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

    template < auto AchievementType >
    void progressAchievementByType( Entity::Player& player, int32_t argument, uint32_t progressCount = 1 )
    {
      progressAchievement< decltype( AchievementType ), AchievementType >( std::move( player ), argument, progressCount );
    }

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

    Common::AchievementDataKey getKeyFromType( Common::Achievement::Type achvType, int32_t argument );

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
  inline void AchievementMgr::progressAchievement< Common::Achievement::Type, Common::Achievement::Type::Classjob >( Entity::Player& player, int32_t classJob, uint32_t level )
  {
    auto& achvDataList = player.getAchievementDataList();

    auto dataKey = getKeyFromType( Common::Achievement::Type::Classjob, classJob );

    if( !achvDataList.count( dataKey.u32 ) )
      achvDataList[ dataKey.u32 ] = 0;

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
