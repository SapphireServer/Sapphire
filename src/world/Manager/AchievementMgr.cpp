#include <Exd/ExdData.h>
#include <Util/Util.h>

#include "AchievementMgr.h"
#include <Network/Util/PacketUtil.h>
#include <Network/CommonActorControl.h>

using namespace Sapphire;
using namespace Sapphire::Network;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::World::Manager;

bool AchievementMgr::cacheAchievements()
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto idList = exdData.getIdList< Excel::Achievement >();

  for( auto id : idList )
  {
    auto achvExdData = exdData.getRow< Excel::Achievement >( id );

    uint32_t key = achvExdData->data().ConditionType;
    auto achvType = static_cast< Common::Achievement::Type >( key );

    if( achvType == Common::Achievement::Type::None )
      continue;

    // verify if achievement type has subtype
    if( achvType == Common::Achievement::Type::General ||
        achvType == Common::Achievement::Type::Classjob ||
        achvType == Common::Achievement::Type::InstanceContent )
    {
      int32_t subtype = achvExdData->data().ConditionArg[ 0 ];
      if( subtype != 0 )
        key = ( getKeyFromType( achvType, subtype ) ).u32;
      else
        continue; // ignore key types with no subtype
    }

    // map achievement IDs to achv data
    m_achievementKeyCacheMap[ key ].emplace_back( id );
    // map achievement keys (either type or union key:subtype) to achievement IDs
    m_achievementDetailCacheMap[ id ] = std::move( achvExdData );
  }

  return true;
}

void AchievementMgr::unlockAchievement( Entity::Player& player, uint32_t achievementId )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto achvExd = exdData.getRow< Excel::Achievement >( achievementId );

  // set flag on mask format expected by client
  uint16_t index;
  uint8_t value;
  Common::Util::valueToFlagByteIndexValue( achievementId, value, index );

  auto achvData = player.getAchievementData();
  achvData.unlockList[ index ] |= value;
  player.setAchievementData( achvData );

  // handle player achievement history
  // todo: verify retail behavior due to client copying the last achievement unlocked

  std::rotate( achvData.history.rbegin(), achvData.history.rbegin() + 1, achvData.history.rend() );
  achvData.history[ 0 ] = achievementId;

  // fire packets
  player.setAchievementData( achvData );
  Network::Util::Packet::sendAchievementList( player );
  Network::Util::Packet::sendActorControl( player, AchievementComplete, achievementId );
  Network::Util::Packet::sendActorControl( player, AchievementObtainMsg, achievementId );

  // check and add title to player
  auto achvTitleId = achvExd->data().Title;
  if( achvTitleId != 0 )
  {
    player.addTitle( achvTitleId );
  }

  handleLinkedAchievementsForId( player, achievementId );
}

bool AchievementMgr::hasAchievementUnlocked( Entity::Player& player, uint32_t achievementId )
{
  uint16_t index;
  uint8_t value;
  Common::Util::valueToFlagByteIndexValue( achievementId, value, index );

  return ( player.getAchievementData().unlockList[ index ] & value ) != 0;
}

std::pair< uint32_t, uint32_t > AchievementMgr::getAchievementDataById( Entity::Player& player, uint32_t achievementId )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto achvDataList = player.getAchievementData().progressData;
  auto achvExd = exdData.getRow< Excel::Achievement >( achievementId )->data();
  auto achvType = static_cast< Common::Achievement::Type >( achvExd.ConditionType );

  // get paired type:subtype key for stored data
  auto dataKey = getKeyFromType( achvType, achvExd.ConditionArg[ 0 ] );

  // get achievement progress data, if it exists (otherwise pass 0)
  uint32_t currProg = 0;
  if( achvDataList.count( dataKey.u32 ) )
    currProg = achvDataList[ dataKey.u32 ];

  // get maximum progress for given achievement, as required by client
  uint32_t maxProg = static_cast< uint32_t >( achvExd.ConditionArg[ 1 ] );

  // cap maximum progress display to maximum progress
  return { std::min( currProg, maxProg ), maxProg };
}

void AchievementMgr::handleLinkedAchievementsForId( Entity::Player& player, uint32_t achievementId )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();

  const auto& linkedAchievementIdList = getAchievementIdByType( Common::Achievement::Type::LinkedAchievement );

  for( auto& achvId : linkedAchievementIdList )
  {
    // skip if achievement already unlocked
    if( hasAchievementUnlocked( player, achvId ) )
      continue;

    auto pAchv = getAchievementDetail( achvId );
    if( !pAchv )
      continue;

    auto achvExdData = pAchv->data();

    // if achievement has other achievements linked to it
    if( achvExdData.ConditionType == static_cast< uint8_t >( Common::Achievement::Type::LinkedAchievement ) )
    {
      // get all linked achievements needed to unlock
      std::set< int32_t > linkedAchv{ std::make_move_iterator( std::begin( achvExdData.ConditionArg ) ),
                                      std::make_move_iterator( std::end( achvExdData.ConditionArg ) ) };

      // clear empty achievement links
      linkedAchv.erase( 0 );

      // check if passed achievement ID is tied to this linked achievement
      if( !linkedAchv.count( achievementId ) )
        continue;

      // verify if player has all the required achievements unlocked
      bool hasAllAchievements = true;
      for( const auto linkedAchvId : linkedAchv )
      {
        if( !hasAchievementUnlocked( player, linkedAchvId ) )
        {
          hasAllAchievements = false;
          break;
        }
      }

      // unlock achievement if linked achievement conditions are met
      if( hasAllAchievements )
        unlockAchievement( player, achvId );
    }
  }
}

Common::AchievementDataKey AchievementMgr::getKeyFromType( Common::Achievement::Type achvType, int32_t argument )
{
  Common::AchievementDataKey dataKey{ 0 };

  dataKey.key.type = static_cast< uint8_t >( achvType );
  dataKey.key.subtype = static_cast< uint16_t >( argument );

  return dataKey;
}

std::vector< uint32_t > AchievementMgr::getAchievementIdByType( Common::Achievement::Type type ) const
{
  return getAchievementIdByType( static_cast< uint32_t >( type ) );
}

std::vector< uint32_t > AchievementMgr::getAchievementIdByType( uint32_t type ) const
{
  auto it = m_achievementKeyCacheMap.find( type );

  if( it != std::end( m_achievementKeyCacheMap ) )
    return it->second;
  else
    return {};
}

std::shared_ptr< Excel::ExcelStruct< Excel::Achievement > > AchievementMgr::getAchievementDetail( uint32_t achvId ) const
{
  auto it = m_achievementDetailCacheMap.find( achvId );

  if( it != std::end( m_achievementDetailCacheMap ) )
    return it->second;
  else
    return nullptr;
}

