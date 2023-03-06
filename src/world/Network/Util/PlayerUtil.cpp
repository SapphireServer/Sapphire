#include "PlayerUtil.h"

#include <Exd/ExdData.h>

#include <Manager/MgrUtil.h>
#include <Manager/TerritoryMgr.h>

#include <Territory/Territory.h>

#include <Network/CommonActorControl.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketWrappers/ActorControlPacket.h>
#include <Network/PacketWrappers/ActorControlSelfPacket.h>
#include <Network/PacketWrappers/ActorControlTargetPacket.h>
#include <Network/PacketWrappers/HudParamPacket.h>
#include <Network/PacketWrappers/ModelEquipPacket.h>
#include <Network/PacketWrappers/ConditionPacket.h>

using namespace Sapphire;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Util::Player;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;

void Util::Player::sendConfigFlags( Entity::Player& player )
{
  auto paramPacket = makeZonePacket< FFXIVIpcConfig >( player.getId() );
  paramPacket->data().flag = player.getConfigFlags();
  server().queueForPlayers( player.getInRangePlayerIds( true ), paramPacket );
}

void Util::Player::sendOnlineStatus( Entity::Player& player )
{
  auto statusPacket = makeZonePacket< FFXIVIpcSetOnlineStatus >( player.getId() );
  statusPacket->data().onlineStatusFlags = player.getFullOnlineStatusMask();
  server().queueForPlayer( player.getCharacterId(), statusPacket );

  server().queueForPlayers( player.getInRangePlayerIds( true ),
                            makeActorControl( player.getId(), SetStatusIcon, static_cast< uint8_t >( player.getOnlineStatus() ) ) );
}

void Util::Player::sendBaseParams( Entity::Player& player )
{
  std::array< uint32_t, 50 > statParams{};
  std::fill( std::begin( statParams ), std::end( statParams ), 0 );

  auto& exd = Common::Service< Data::ExdData >::ref();
  auto idList = exd.getIdList< Excel::BaseParam >();

  for( const auto id : idList )
  {
    auto row = exd.getRow< Excel::BaseParam >( id );
    if( !row )
      continue;
    if( row->data().PacketIndex < 0 )
      continue;
    statParams[ row->data().PacketIndex ] = player.getStatValue( static_cast< Common::BaseParam >( id ) );
  }

  auto statPacket = makeZonePacket< FFXIVIpcBaseParam >( player.getId() );
  memcpy( statPacket->data().Param, statParams.data(), sizeof( uint32_t ) * statParams.size() );
  server().queueForPlayer( player.getCharacterId(), statPacket );
}

void Util::Player::sendHudParam( Entity::Player& player )
{
  auto hudParamPacket = makeHudParam( player );
  server().queueForPlayer( player.getCharacterId(), hudParamPacket );
}

void Util::Player::sendStatusUpdate( Entity::Player& player )
{
  auto playerStatusUpdate = makeZonePacket< FFXIVIpcPlayerStatusUpdate >( player.getId() );
  playerStatusUpdate->data().ClassJob = static_cast< uint8_t >( player.getClass() );
  playerStatusUpdate->data().Lv = player.getLevel();
  playerStatusUpdate->data().Lv1 = player.getLevel();
  playerStatusUpdate->data().LvSync = 0; //player.getLevelSync();
  playerStatusUpdate->data().Exp = player.getExp();

  server().queueForPlayer( player.getCharacterId(), playerStatusUpdate );
}

void Util::Player::sendHuntingLog( Entity::Player& player )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  for( auto entryCount = 0; entryCount < Common::ARRSIZE_MONSTERNOTE; ++entryCount )
  {
    auto& entry = player.getHuntingLogEntry( entryCount );
    uint64_t completionFlag = 0;
    auto huntPacket = makeZonePacket< FFXIVIpcMonsterNoteCategory >( player.getId() );

    huntPacket->data().contextId = -1;
    huntPacket->data().currentRank = entry.rank;
    huntPacket->data().categoryIndex = entryCount;

    for( int i = 1; i <= 10; ++i )
    {
      auto index0 = i - 1;
      bool allComplete = true;
      auto monsterNoteId = ( entryCount + 1 ) * 10000 + entry.rank * 10 + i;

      auto monsterNote = exdData.getRow< Excel::MonsterNote >( monsterNoteId );
      if( !monsterNote )
        continue;

      const auto huntEntry = entry.entries[ index0 ];
      for( int x = 0; x < 3; ++x )
      {
        if( ( huntEntry[ x ] == monsterNote->data().NeededKills[ x ] ) && monsterNote->data().NeededKills[ x ] != 0 )
          completionFlag |= ( 1ull << ( index0 * 5 + x ) );
        else if( monsterNote->data().NeededKills[ x ] != 0 )
          allComplete = false;
      }

      if( allComplete )
        completionFlag |= ( 1ull << ( index0 * 5 + 4 ) );

    }

    memcpy( huntPacket->data().killCount, entry.entries, sizeof( entry.entries ) );
    huntPacket->data().completeFlags = completionFlag;
    server().queueForPlayer( player.getCharacterId(), huntPacket );
  }
}

void Util::Player::sendActorControlSelf( Entity::Player& player, uint16_t category, uint32_t param1, uint32_t param2, uint32_t param3,
                                         uint32_t param4, uint32_t param5 )
{
  server().queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), category, param1, param2, param3, param4, param5 ) );
}

void Util::Player::sendActorControlSelf( const std::set< uint64_t >& characterIds, Entity::Player& player, uint16_t category, uint32_t param1,
                                         uint32_t param2, uint32_t param3, uint32_t param4, uint32_t param5 )
{
  server().queueForPlayers( characterIds, makeActorControlSelf( player.getId(), category, param1, param2, param3, param4, param5 ) );
}

void Util::Player::sendActorControl( Entity::Player& player, uint16_t category, uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4 )
{
  server().queueForPlayer( player.getCharacterId(), makeActorControl( player.getId(), category, param1, param2, param3, param4 ) );
}

void Util::Player::sendActorControl( const std::set< uint64_t >& characterIds, Entity::Player& player, uint16_t category, uint32_t param1,
                                     uint32_t param2, uint32_t param3, uint32_t param4 )
{
  server().queueForPlayers( characterIds, makeActorControl( player.getId(), category, param1, param2, param3, param4 ) );
}

void Util::Player::sendTitleList( Entity::Player& player )
{
  auto titleListPacket = makeZonePacket< FFXIVIpcTitleList >( player.getId() );
  memcpy( titleListPacket->data().TitleFlagsArray, player.getTitleList().data(), sizeof( titleListPacket->data().TitleFlagsArray ) );
  server().queueForPlayer( player.getCharacterId(), titleListPacket );
}

void Util::Player::sendGrandCompany( Entity::Player& player )
{
  auto gcAffPacket = makeZonePacket< FFXIVIpcGrandCompany >( player.getId() );
  gcAffPacket->data().ActiveCompanyId = player.getGc();
  gcAffPacket->data().MaelstromRank = player.getGcRankArray()[ 0 ];
  gcAffPacket->data().TwinAdderRank = player.getGcRankArray()[ 1 ];
  gcAffPacket->data().ImmortalFlamesRank = player.getGcRankArray()[ 2 ];
  server().queueForPlayer( player.getCharacterId(), gcAffPacket );
}

void Util::Player::sendDeletePlayer( Entity::Player& player, uint32_t actorId, uint8_t spawnIndex )
{
  auto freeActorSpawnPacket = makeZonePacket< FFXIVIpcActorFreeSpawn >( player.getId() );
  freeActorSpawnPacket->data().actorId = actorId;
  freeActorSpawnPacket->data().spawnId = spawnIndex;
  server().queueForPlayer( player.getCharacterId(), freeActorSpawnPacket );
}

void Util::Player::sendDeleteObject( Entity::Player& player, uint8_t spawnIndex )
{
  auto freeObjectSpawnPacket = makeZonePacket< FFXIVIpcDeleteObject >( player.getId() );
  freeObjectSpawnPacket->data().Index = spawnIndex;
  server().queueForPlayer( player.getCharacterId(), freeObjectSpawnPacket );
}

void Util::Player::sendHateList( Entity::Player& player )
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();

  auto hateListPacket = makeZonePacket< FFXIVIpcHateList >( player.getId() );
  auto hateRankPacket = makeZonePacket< FFXIVIpcHaterList >( player.getId() );

  auto actorIdToHateSlotMap = player.getActorIdToHateSlotMap();

  hateListPacket->data().Count = static_cast< uint8_t >( actorIdToHateSlotMap.size() );

  hateRankPacket->data().Count = static_cast< uint8_t >( actorIdToHateSlotMap.size() );
  auto it = actorIdToHateSlotMap.begin();

  auto zone = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
  if( !zone )
    return;

  for( int32_t i = 0; it != actorIdToHateSlotMap.end(); ++it, ++i )
  {
    auto pBNpc = zone->getActiveBNpcByEntityId( it->first );
    if( !pBNpc )
      continue;

    auto hateValue = pBNpc->hateListGetValue( player.getAsChara() );
    if( hateValue == 0 )
      continue;

    auto hatePercent = ( hateValue / static_cast< float >( pBNpc->hateListGetHighestValue() ) ) * 100.f;

    hateListPacket->data().List[ i ].Id = player.getId();
    hateListPacket->data().List[ i ].Value = hateValue;

    hateRankPacket->data().List[ i ].Id = it->first;
    hateRankPacket->data().List[ i ].Rate = static_cast< uint8_t >( hatePercent );
  }

  server().queueForPlayer( player.getCharacterId(), { hateListPacket, hateRankPacket } );
}

void Util::Player::sendMount( Entity::Player& player )
{
  auto mountId = player.getCurrentMount();
  auto inRangePlayerIds = player.getInRangePlayerIds( true );
  if( mountId != 0 )
  {
    Network::Util::Player::sendActorControl( inRangePlayerIds, player, SetStatus, static_cast< uint8_t >( Common::ActorStatus::Mounted ) );
    Network::Util::Player::sendActorControlSelf( inRangePlayerIds, player, 0x39e, 12 );
  }
  else
  {
    Network::Util::Player::sendActorControl( inRangePlayerIds, player, SetStatus, static_cast< uint8_t >( Common::ActorStatus::Idle ) );
    Network::Util::Player::sendActorControlSelf( inRangePlayerIds, player, Dismount, 1 );
  }
  auto mountPacket = makeZonePacket< FFXIVIpcMount >( player.getId() );
  mountPacket->data().id = mountId;
  server().queueForPlayers( inRangePlayerIds, mountPacket );
}

void Util::Player::sendEquip( Entity::Player& player )
{
  server().queueForPlayers( player.getInRangePlayerIds( true ), std::make_shared< ModelEquipPacket >( player ) );
}

void Util::Player::sendCondition( Entity::Player& player )
{
  server().queueForPlayer( player.getCharacterId(), std::make_shared< ConditionPacket >( player ) );
}

void Util::Player::sendRecastGroups( Entity::Player& player )
{
  const auto& recastGroups = player.getRecastGroups();
  const auto& recastGroupsMax = player.getRecastGroupsMax();
  auto recastGroupPaket = makeZonePacket< FFXIVIpcRecastGroup >( player.getId() );
  memcpy( &recastGroupPaket->data().Recast, recastGroups.data(), recastGroups.size() * sizeof( float ) );
  memcpy( &recastGroupPaket->data().RecastMax, recastGroupsMax.data(), recastGroupsMax.size() * sizeof( float ) );
  server().queueForPlayer( player.getCharacterId(), recastGroupPaket );
}