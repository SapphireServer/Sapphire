#include "PacketUtil.h"

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
#include <Network/PacketWrappers/RestingPacket.h>
#include <Network/PacketWrappers/PlayerSetupPacket.h>
#include <Network/PacketWrappers/InitZonePacket.h>
#include <Network/PacketWrappers/ServerNoticePacket.h>
#include <Network/PacketWrappers/ChatPacket.h>

using namespace Sapphire;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Util::Packet;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;

void Util::Packet::sendConfigFlags( Entity::Player& player )
{
  auto paramPacket = makeZonePacket< FFXIVIpcConfig >( player.getId() );
  paramPacket->data().flag = player.getConfigFlags();
  server().queueForPlayers( player.getInRangePlayerIds( true ), paramPacket );
}

void Util::Packet::sendOnlineStatus( Entity::Player& player )
{
  auto statusPacket = makeZonePacket< FFXIVIpcSetOnlineStatus >( player.getId() );
  statusPacket->data().onlineStatusFlags = player.getFullOnlineStatusMask();
  server().queueForPlayer( player.getCharacterId(), statusPacket );

  server().queueForPlayers( player.getInRangePlayerIds( true ),
                            makeActorControl( player.getId(), SetStatusIcon, static_cast< uint8_t >( player.getOnlineStatus() ) ) );
}

void Util::Packet::sendBaseParams( Entity::Player& player )
{
  std::array< uint32_t, 50 > statParams{};
  std::fill( std::begin( statParams ), std::end( statParams ), 0 );

  auto& exd = Common::Service< Data::ExdData >::ref();
  auto baseParamList = exd.getRows< Excel::BaseParam >();

  for( const auto& [ id, row ] : baseParamList )
  {
    if( !row || row->data().PacketIndex < 0 )
      continue;

    statParams[ row->data().PacketIndex ] = player.getStatValue( static_cast< Common::BaseParam >( id ) );
  }

  auto statPacket = makeZonePacket< FFXIVIpcBaseParam >( player.getId() );
  memcpy( statPacket->data().Param, statParams.data(), sizeof( uint32_t ) * statParams.size() );
  server().queueForPlayer( player.getCharacterId(), statPacket );
}

void Util::Packet::sendHudParam( Entity::Chara& source )
{
  if( source.isPlayer() )
    server().queueForPlayers( source.getInRangePlayerIds( true ), makeHudParam( *source.getAsPlayer() ) );
  else if( source.isBattleNpc() )
    server().queueForPlayers( source.getInRangePlayerIds( false ), makeHudParam( *source.getAsBNpc() ) );
  else
    server().queueForPlayers( source.getInRangePlayerIds( false ), makeHudParam( source ) );
}

void Util::Packet::sendStatusUpdate( Entity::Player& player )
{
  auto playerStatusUpdate = makeZonePacket< FFXIVIpcPlayerStatusUpdate >( player.getId() );
  playerStatusUpdate->data().ClassJob = static_cast< uint8_t >( player.getClass() );
  playerStatusUpdate->data().Lv = player.getLevel();
  playerStatusUpdate->data().Lv1 = player.getLevel();
  playerStatusUpdate->data().LvSync = 0; //player.getLevelSync();
  playerStatusUpdate->data().Exp = player.getCurrentExp();

  server().queueForPlayer( player.getCharacterId(), playerStatusUpdate );
}

void Util::Packet::sendHuntingLog( Entity::Player& player )
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

void Util::Packet::sendActorControlSelf( Entity::Player& player, uint32_t srcId, uint16_t category, uint32_t param1, uint32_t param2, uint32_t param3,
                                         uint32_t param4, uint32_t param5 )
{
  server().queueForPlayer( player.getCharacterId(), makeActorControlSelf( srcId, category, param1, param2, param3, param4, param5 ) );
}

void Util::Packet::sendActorControlSelf( const std::set< uint64_t >& characterIds, uint32_t srcId, uint16_t category, uint32_t param1,
                                         uint32_t param2, uint32_t param3, uint32_t param4, uint32_t param5 )
{
  server().queueForPlayers( characterIds, makeActorControlSelf( srcId, category, param1, param2, param3, param4, param5 ) );
}

void Util::Packet::sendActorControl( Entity::Player& player, uint32_t srcId, uint16_t category, uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4 )
{
  server().queueForPlayer( player.getCharacterId(), makeActorControl( srcId, category, param1, param2, param3, param4 ) );
}

void Util::Packet::sendActorControl( const std::set< uint64_t >& characterIds, uint32_t srcId, uint16_t category, uint32_t param1,
                                     uint32_t param2, uint32_t param3, uint32_t param4 )
{
  server().queueForPlayers( characterIds, makeActorControl( srcId, category, param1, param2, param3, param4 ) );
}

void Util::Packet::sendActorControlTarget( Entity::Player& player, uint32_t srcId, uint16_t category, uint32_t param1, uint32_t param2, uint32_t param3,
                                           uint32_t param4, uint32_t param5, uint32_t param6 )
{
  server().queueForPlayer( player.getCharacterId(), makeActorControlTarget( srcId, category, param1, param2, param3, param4, param5, param6 ) );
}

void Util::Packet::sendActorControlTarget( const std::set< uint64_t >& characterIds, uint32_t srcId, uint16_t category, uint32_t param1,
                                           uint32_t param2, uint32_t param3, uint32_t param4, uint32_t param5, uint32_t param6 )
{
  server().queueForPlayers( characterIds, makeActorControlTarget( srcId, category, param1, param2, param3, param4, param5, param6 ) );
}

void Util::Packet::sendTitleList( Entity::Player& player )
{
  auto titleListPacket = makeZonePacket< FFXIVIpcTitleList >( player.getId() );
  memcpy( titleListPacket->data().TitleFlagsArray, player.getTitleList().data(), sizeof( titleListPacket->data().TitleFlagsArray ) );
  server().queueForPlayer( player.getCharacterId(), titleListPacket );
}

void Util::Packet::sendGrandCompany( Entity::Player& player )
{
  auto gcAffPacket = makeZonePacket< FFXIVIpcGrandCompany >( player.getId() );
  gcAffPacket->data().ActiveCompanyId = player.getGc();
  gcAffPacket->data().MaelstromRank = player.getGcRankArray()[ 0 ];
  gcAffPacket->data().TwinAdderRank = player.getGcRankArray()[ 1 ];
  gcAffPacket->data().ImmortalFlamesRank = player.getGcRankArray()[ 2 ];
  server().queueForPlayer( player.getCharacterId(), gcAffPacket );
}

void Util::Packet::sendDeletePlayer( Entity::Player& player, uint32_t actorId, uint8_t spawnIndex )
{
  auto freeActorSpawnPacket = makeZonePacket< FFXIVIpcActorFreeSpawn >( player.getId() );
  freeActorSpawnPacket->data().actorId = actorId;
  freeActorSpawnPacket->data().spawnId = spawnIndex;
  server().queueForPlayer( player.getCharacterId(), freeActorSpawnPacket );
}

void Util::Packet::sendDeleteObject( Entity::Player& player, uint8_t spawnIndex )
{
  auto freeObjectSpawnPacket = makeZonePacket< FFXIVIpcDeleteObject >( player.getId() );
  freeObjectSpawnPacket->data().Index = spawnIndex;
  server().queueForPlayer( player.getCharacterId(), freeObjectSpawnPacket );
}

void Util::Packet::sendHateList( Entity::Player& player )
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

    auto hatePercent = ( static_cast< float >( hateValue ) / static_cast< float >( pBNpc->hateListGetHighestValue() ) ) * 100.f;

    hateListPacket->data().List[ i ].Id = player.getId();
    hateListPacket->data().List[ i ].Value = hateValue;

    hateRankPacket->data().List[ i ].Id = it->first;
    hateRankPacket->data().List[ i ].Rate = static_cast< uint8_t >( hatePercent );
  }

  server().queueForPlayer( player.getCharacterId(), { hateListPacket, hateRankPacket } );
}

void Util::Packet::sendMount( Entity::Player& player )
{
  auto mountId = player.getCurrentMount();
  auto inRangePlayerIds = player.getInRangePlayerIds( true );
  if( mountId != 0 )
  {
    Network::Util::Packet::sendActorControl( inRangePlayerIds, player.getId(), SetStatus, static_cast< uint8_t >( Common::ActorStatus::Mounted ) );
    Network::Util::Packet::sendActorControlSelf( inRangePlayerIds, player.getId(), 0x39e, 12 );
  }
  else
  {
    Network::Util::Packet::sendActorControl( inRangePlayerIds, player.getId(), SetStatus, static_cast< uint8_t >( Common::ActorStatus::Idle ) );
    Network::Util::Packet::sendActorControlSelf( inRangePlayerIds, player.getId(), Dismount, 1 );
  }
  auto mountPacket = makeZonePacket< FFXIVIpcMount >( player.getId() );
  mountPacket->data().id = mountId;
  server().queueForPlayers( inRangePlayerIds, mountPacket );
}

void Util::Packet::sendEquip( Entity::Player& player )
{
  server().queueForPlayers( player.getInRangePlayerIds( true ), std::make_shared< ModelEquipPacket >( player ) );
}

void Util::Packet::sendCondition( Entity::Player& player )
{
  server().queueForPlayer( player.getCharacterId(), std::make_shared< ConditionPacket >( player ) );
}

void Util::Packet::sendRecastGroups( Entity::Player& player )
{
  const auto& recastGroups = player.getRecastGroups();
  const auto& recastGroupsMax = player.getRecastGroupsMax();
  auto recastGroupPaket = makeZonePacket< FFXIVIpcRecastGroup >( player.getId() );
  memcpy( &recastGroupPaket->data().Recast, recastGroups.data(), recastGroups.size() * sizeof( float ) );
  memcpy( &recastGroupPaket->data().RecastMax, recastGroupsMax.data(), recastGroupsMax.size() * sizeof( float ) );
  server().queueForPlayer( player.getCharacterId(), recastGroupPaket );
}

void Util::Packet::sendAchievementList( Entity::Player& player )
{
  auto achvData = player.getAchievementData();
  auto achvPacket = makeZonePacket< FFXIVIpcAchievement >( player.getId() );
  std::memcpy( &achvPacket->data().complete[ 0 ], &achvData.unlockList[ 0 ], sizeof( achvPacket->data().complete ) );
  std::memcpy( &achvPacket->data().history[ 0 ], &achvData.history[ 0 ], sizeof( achvPacket->data().history ) );
  server().queueForPlayer( player.getCharacterId(), achvPacket );
}

void Util::Packet::sendRestingUpdate( Entity::Player& player )
{
  server().queueForPlayers( player.getInRangePlayerIds( true ), std::make_shared< RestingPacket >( player ) );
}

void Util::Packet::sendLogin( Entity::Player& player )
{
  auto initPacket = makeZonePacket< FFXIVIpcLogin >( player.getId() );
  initPacket->data().playerActorId = player.getId();
  server().queueForPlayer( player.getCharacterId(), initPacket );
}

void Util::Packet::sendPlayerSetup( Entity::Player& player )
{
  server().queueForPlayer( player.getCharacterId(), makePlayerSetup( player ) );
}

void Util::Packet::sendChangeClass( Entity::Player& player )
{
  auto classInfo = makeZonePacket< FFXIVIpcChangeClass >( player.getId() );
  auto& borrowAction = player.getBorrowAction();
  classInfo->data().ClassJob = static_cast< uint8_t >( player.getClass() );
  classInfo->data().Lv = player.getLevel();
  classInfo->data().Lv1 = player.getLevel();
  classInfo->data().Login = player.isLogin() ? 1 : 0;
  memcpy( &classInfo->data().BorrowAction[ 0 ], borrowAction.data(), borrowAction.size() * 4 );
  server().queueForPlayer( player.getCharacterId(), classInfo );
}

void Util::Packet::sendContentAttainFlags( Entity::Player& player )
{
  // todo - fill with actual data from player
  auto contentFinderList = makeZonePacket< FFXIVIpcContentAttainFlags >( player.getId() );
  std::memset( &contentFinderList->data(), 0xFF, sizeof( contentFinderList->data() ) );
  server().queueForPlayer( player.getCharacterId(), contentFinderList );
}

void Util::Packet::sendInitZone( Entity::Player& player )
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
  if( !pZone )
  {
    Logger::error( "Territory GuID#{} not found!", player.getTerritoryId() );
    return;
  }
  auto& teri = *pZone;
  server().queueForPlayer( player.getCharacterId(), makeInitZone( player, teri ) );
}

void Util::Packet::sendDailyQuests( Entity::Player& player )
{
  server().queueForPlayer( player.getCharacterId(), makeZonePacket< FFXIVIpcDailyQuests >( player.getId() ) );
}

void Util::Packet::sendQuestRepeatFlags( Entity::Player& player )
{
  server().queueForPlayer( player.getCharacterId(), makeZonePacket< FFXIVIpcQuestRepeatFlags >( player.getId() ) );
}

void Util::Packet::sendServerNotice( Entity::Player& player, const std::string& message )
{
  server().queueForPlayer( player.getCharacterId(), std::make_shared< ServerNoticePacket >( player.getId(), message ) );
}

void Util::Packet::sendChat( Entity::Player& player, Common::ChatType chatType, const std::string& message )
{
  server().queueForPlayer( player.getCharacterId(), std::make_shared< ChatPacket >( player, chatType, message ) );
}