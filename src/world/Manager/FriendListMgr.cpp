#include <algorithm>
#include <iterator>

#include <Logging/Logger.h>
#include <Service.h>
#include <Util/Util.h>

#include "Actor/Player.h"
#include "FriendListMgr.h"

bool Sapphire::World::Manager::FriendListMgr::onInviteCreate( Entity::Player& source, Entity::Player& target )
{
  auto& sourceFL = source.getFriendListID();
  auto& targetFL = target.getFriendListID();

  // check if player already has been invited or friends
  if( isFriend( source, target ) )
  {
    // already invited/friends
    return false;
  }

  // check if there are slots available to allocate and get idx
  auto sourceIdx = getEntryIndex( source, 0 );
  auto targetIdx = getEntryIndex( target, 0 );

  if( sourceIdx == -1 || targetIdx == -1 )
  {
    // todo: complain about having too many friends
    return false;
  }

  auto& sourceFLData = source.getFriendListData();
  auto& targetFLData = target.getFriendListData();

  // add ID and data to arrays of both players
  sourceFL[ sourceIdx ] = target.getCharacterId();
  targetFL[ targetIdx ] = source.getCharacterId();


  Common::HierarchyData hierarchy;
  hierarchy.data.dateAdded = Common::Util::getTimeSeconds();
  hierarchy.data.group = 0;
  hierarchy.data.type = Common::HierarchyType::FRIENDLIST;

  // set hierarchy status for invite sender
  hierarchy.data.status = Common::HierarchyStatus::SentRequest;
  sourceFLData[ sourceIdx ] = hierarchy;

  // set hierarchy status for invite receiver
  hierarchy.data.status = Common::HierarchyStatus::ReceivedRequest;
  targetFLData[ targetIdx ] = hierarchy;

  // force db update for friendlist
  source.updateDbFriendList();
  target.updateDbFriendList();

  return true;
}
 
bool Sapphire::World::Manager::FriendListMgr::onInviteAccept( Entity::Player& source, Entity::Player& target )
{
  // accept friend invite
  auto sourceIdx = getEntryIndex( source, target.getCharacterId() );
  auto targetIdx = getEntryIndex( target, source.getCharacterId() );

  if( sourceIdx == -1 || targetIdx == -1 )
  {
    // currently not friends
    return false;
  }

  auto& sourceFLData = source.getFriendListData();
  auto& targetFLData = target.getFriendListData();

  // currently, type on hierarchy indicates invite type - since it is no longer an invite, set type to NONE
  sourceFLData[ sourceIdx ].data.status = Common::HierarchyStatus::Added;
  sourceFLData[ sourceIdx ].data.type   = Common::HierarchyType::NONE_2;
  targetFLData[ targetIdx ].data.status = Common::HierarchyStatus::Added;
  targetFLData[ targetIdx ].data.type   = Common::HierarchyType::NONE_2;
  
  source.updateDbFriendList();
  target.updateDbFriendList();
  return true;
}

bool Sapphire::World::Manager::FriendListMgr::onInviteDecline( Entity::Player& source, Entity::Player& target )
{
  // decline friend invite
  auto sourceIdx = getEntryIndex( source, target.getCharacterId() );
  auto targetIdx = getEntryIndex( target, source.getCharacterId() );

  if( sourceIdx == -1 || targetIdx == -1 )
  {
    // currently not friends
    return false;
  }

  auto& sourceFL = source.getFriendListID();
  auto& targetFL = target.getFriendListID();

  auto& sourceFLData = source.getFriendListData();
  auto& targetFLData = target.getFriendListData();

  sourceFL[ sourceIdx ] = 0;
  targetFL[ targetIdx ] = 0;

  sourceFLData[ sourceIdx ].u64 = 0;
  targetFLData[ targetIdx ].u64 = 0;

  source.updateDbFriendList();
  target.updateDbFriendList();
  return true;
}

bool Sapphire::World::Manager::FriendListMgr::onRemoveFriend( Entity::Player& source, Entity::Player& target )
{
  // remove friend
  // this not retail accurate - retail only removes source friendlist, but that also makes it more complicated for readding friend
  // this will simply remove the entry from both players

  return onInviteDecline( source, target );
}

bool Sapphire::World::Manager::FriendListMgr::onAssignGroup( Entity::Player& source, Entity::Player& target, uint8_t group )
{
  // assign group to friend entry (to source only)
  auto sourceIdx = getEntryIndex( source, target.getCharacterId() );

  if( sourceIdx == -1 )
  {
    // currently not friends
    return false;
  }

  auto& sourceFLData = source.getFriendListData();

  sourceFLData[ sourceIdx ].data.group = group;

  source.updateDbFriendList();

  return true;
}

bool Sapphire::World::Manager::FriendListMgr::isFriend( Entity::Player& source, Entity::Player& target ) const
{
  return getEntryIndex( source, target.getCharacterId() ) != -1;
}

ptrdiff_t Sapphire::World::Manager::FriendListMgr::getEntryIndex( Entity::Player& source, uint64_t characterId ) const
{
  auto& sourceFL = source.getFriendListID();
  auto sourceInvIt = std::find( std::begin( sourceFL ), std::end( sourceFL ), characterId );

  // not found
  if( sourceInvIt == sourceFL.end() )
    return -1;

  return sourceInvIt - std::begin( sourceFL );
}
