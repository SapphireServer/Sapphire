#include <algorithm>
#include <iterator>

#include <Logging/Logger.h>
#include <Service.h>
#include <Util/Util.h>

#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketContainer.h>

#include "Actor/Player.h"
#include "BlacklistMgr.h"
#include "FriendListMgr.h"

#include "WorldServer.h"

using namespace Sapphire;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets;

bool BlacklistMgr::onAddCharacter( Entity::Player& source, const std::string& targetName )
{
  // add target to blacklist

  auto& server = Common::Service< World::WorldServer >::ref();

  auto pTarget = server.getPlayer( targetName );
  if( !pTarget )
  {
    // target doesn't exist in server player table
    sendAddResultPacket( source, pTarget, 0x7 );
    return false;
  }

  auto& target = *pTarget;

  if( source.getCharacterId() == target.getCharacterId() )
  {
    // can't add self to blacklist
    sendAddResultPacket( source, pTarget, 0x7 );
    return false;
  }
  
  if( isBlacklisted( source, target ) )
  {
    // target already added to blacklist
    sendAddResultPacket( source, pTarget, 0x7 );
    return false;
  }

  // get next available slot in blacklist
  auto sourceIdx = getEntryIndex( source, 0 );

  if( sourceIdx == -1 )
  {
    // no slots left in blacklist (max capacity)
    return false;
  }

  // add target ID to blacklist
  auto& sourceBL = source.getBlacklistID();
  sourceBL[sourceIdx] = target.getCharacterId();

  source.updateDbBlacklist();

  sendAddResultPacket( source, pTarget, 0 );

  // check if player is friends with target
  auto& flMgr = Common::Service< FriendListMgr >::ref();
  if( flMgr.isFriend( source, target ) )
    flMgr.onRemoveFriend( source, target );

  return true;
}

bool BlacklistMgr::onRemoveCharacter( Entity::Player& source, const std::string& targetName )
{
  // remove target from blacklist

  auto& server = Common::Service< World::WorldServer >::ref();

  auto pTarget = server.getPlayer( targetName );
  if( !pTarget )
  {
    // target doesn't exist in server player table
    sendRemoveResultPacket( source, pTarget, 0x7 );
    return false;
  }

  auto& target = *pTarget;

  auto sourceIdx = getEntryIndex( source, target.getCharacterId() );
  
  if( !isBlacklisted( source, target ) )
  {
    // target not in blacklist
    sendRemoveResultPacket( source, pTarget, 0x7 );
    return false;
  }

  // set target slot to 0
  auto& sourceBL = source.getBlacklistID();
  sourceBL[sourceIdx] = 0;
  source.updateDbBlacklist();

  sendRemoveResultPacket( source, pTarget, 0 );

  return true;
}

bool BlacklistMgr::onGetBlacklistPage( Entity::Player& source, uint8_t key, uint8_t nextIdx )
{
  // this function will handle client side indexing and paginate blacklist entries
  // it'll also be called multiple times sequentially until there are no more entries left (id == 0)

  auto& server = Common::Service< World::WorldServer >::ref();

  std::vector< Server::BlacklistCharacter > entries;

  // blacklist entries are sent in pages of 20
  const size_t itemsPerPage = 20;

  // get array offset/last page sent from client packet
  auto offset = nextIdx;

  auto& idVec = source.getBlacklistID();

  for( size_t i = offset; i < offset + itemsPerPage; ++i )
  {
    if( idVec.size() <= i )
    {
      break;
    }

    auto id = idVec[ i ];
    auto pPlayer = server.getPlayer( id );
      
    if( !pPlayer )
      continue;

    // build our packet entry for current iterated id
    Server::BlacklistCharacter entry{};

    entry.CharacterID = pPlayer->getCharacterId();
    strcpy( entry.CharacterName, pPlayer->getName().c_str() );

    // add to current page
    entries.emplace_back( entry );
  }

  // if the page is empty, then we've reached the last page
  bool isLast = entries.empty();

  // configure paging state for client so that it knows whether to request more entries or not
  auto blacklistPacket = makeZonePacket< Server::FFXIVIpcGetBlacklistResult >( source.getId() );
  blacklistPacket->data().Index = offset;
  blacklistPacket->data().NextIndex = isLast ? 0 : nextIdx + itemsPerPage;
  blacklistPacket->data().RequestKey = key;

  memcpy( &blacklistPacket->data().Blacklist[ 0 ], entries.data(), sizeof( Server::BlacklistCharacter ) * entries.size() );

  server.queueForPlayer( source.getCharacterId(), blacklistPacket );

  return true;
}

bool BlacklistMgr::isBlacklisted( Entity::Player& source, const Entity::Player& target ) const
{
  return getEntryIndex( source, target.getCharacterId() ) != -1;
}

ptrdiff_t BlacklistMgr::getEntryIndex( Entity::Player& source, uint64_t characterId ) const
{
  auto& sourceBL = source.getBlacklistID();
  auto sourceBlIt = std::find( std::begin( sourceBL ), std::end( sourceBL ), characterId );

  // not found
  if( sourceBlIt == sourceBL.end() )
    return -1;

  return sourceBlIt - std::begin( sourceBL );
}

void BlacklistMgr::sendAddResultPacket( Entity::Player& source, const Entity::PlayerPtr pTarget, uint32_t result )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto resultPacket = makeZonePacket< Server::FFXIVIpcBlacklistAddResult >( source.getId() );

  if( pTarget )
  {
    Server::BlacklistCharacter blChar;
    blChar.CharacterID = pTarget->getCharacterId();
    strcpy( blChar.CharacterName, pTarget->getName().c_str() );

    resultPacket->data().AddedCharacter = blChar;
    resultPacket->data().Identity = pTarget->getGender();
  }
  
  resultPacket->data().Result = result;

  server.queueForPlayer( source.getCharacterId(), resultPacket );
}

void BlacklistMgr::sendRemoveResultPacket( Entity::Player& source, const Entity::PlayerPtr pTarget, uint32_t result )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto resultPacket = makeZonePacket< Server::FFXIVIpcBlacklistRemoveResult >( source.getId() );

  if( pTarget )
  {
    Server::BlacklistCharacter blChar;
    blChar.CharacterID = pTarget->getCharacterId();
    strcpy( blChar.CharacterName, pTarget->getName().c_str() );

    resultPacket->data().RemovedCharacter = blChar;
    resultPacket->data().Identity = pTarget->getGender();
  }
  
  resultPacket->data().Result = result;

  server.queueForPlayer( source.getCharacterId(), resultPacket );
}
