#include <Common.h>
#include <Exd/ExdData.h>
#include <Service.h>

#include "WorldServer.h"

#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketContainer.h>

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/Notice2Packet.h"

#include "QuestMgr.h"
#include "AchievementMgr.h"

#include "Actor/Player.h"

using namespace Sapphire::Common;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

void QuestMgr::onUpdateQuest( Entity::Player& player, uint8_t questIndex )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto quests = player.getQuestArrayRef();
  auto questUpdatePacket = makeZonePacket< FFXIVIpcQuest >( player.getId() );
  questUpdatePacket->data().index = questIndex;
  questUpdatePacket->data().questInfo = quests[ questIndex ].getQuestData();
  server.queueForPlayer( player.getCharacterId(), questUpdatePacket );

  sendQuestTracker( player );
}

void QuestMgr::onCompleteQuest( Entity::Player& player, uint16_t questId, uint32_t optionalChoice )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto questFinishPacket = makeZonePacket< FFXIVIpcQuestFinish >( player.getId() );
  questFinishPacket->data().questId = questId;
  questFinishPacket->data().flag1 = 1;
  questFinishPacket->data().flag2 = 1;
  server.queueForPlayer( player.getCharacterId(), questFinishPacket );

  giveQuestRewards( player, questId, optionalChoice );

  auto& achvMgr = Common::Service< World::Manager::AchievementMgr >::ref();
  achvMgr.progressAchievementByType< Common::Achievement::Type::Quest >( player, questId );
}

void QuestMgr::onRemoveQuest( Entity::Player &player, uint8_t questIndex )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto questUpdatePacket = makeZonePacket< FFXIVIpcQuest >( player.getId() );
  questUpdatePacket->data().index = static_cast< uint8_t >( questIndex );
  questUpdatePacket->data().questInfo.c.questId = 0;
  questUpdatePacket->data().questInfo.c.sequence = 0xFF;
  server.queueForPlayer( player.getCharacterId(), questUpdatePacket );

  sendQuestTracker( player );
}

bool QuestMgr::giveQuestRewards( Entity::Player& player, uint16_t questId, uint32_t optionalChoice )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto questInfo = exdData.getRow< Excel::Quest >( static_cast< uint32_t >( Event::EventHandler::EventHandlerType::Quest ) << 16 | questId );

  if( !questInfo )
    return false;
  auto paramGrowth = exdData.getRow< Excel::ParamGrow >( questInfo->data().ClassLevel );
  uint32_t exp = ( questInfo->data().Reward.ExpBonus * paramGrowth->data().BaseExp * paramGrowth->data().EventExpRate ) / 100;
  uint32_t gilReward = questInfo->data().Reward.Gil;

  // TODO: check if there is room in inventory, else return false;
  if( exp > 0 )
    player.gainExp( exp );

  for( uint32_t i = 0; i < 6; i++ )
  {
    if( questInfo->data().Reward.Item[ i ] != 0 )
      player.addItem( questInfo->data().Reward.Item[ i ], questInfo->data().Reward.ItemNum[ i ] );
  }

  for( uint32_t i = 0; i < 5; i++ )
  {
    auto itemId = questInfo->data().Reward.OptionalItem[ i ];
    if( itemId == optionalChoice )
    {
      player.addItem( itemId, questInfo->data().Reward.OptionalItemNum[ i ] );
      break;
    }
  }

  if( gilReward > 0 )
    player.addCurrency( CurrencyType::Gil, gilReward );

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void QuestMgr::sendQuestTracker( Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto trackerPacket = makeZonePacket< FFXIVIpcQuestTracker >( player.getId() );

  for( int32_t ii = 0; ii < 5; ii++ )
  {
    auto tracked = player.getQuestTracking( ii );
    if( tracked >= 0 )
    {
      trackerPacket->data().entry[ ii ].active = 1;
      trackerPacket->data().entry[ ii ].questIndex = static_cast< uint8_t >( tracked );
    }
  }
  server.queueForPlayer( player.getCharacterId(), trackerPacket );
}

void QuestMgr::sendQuestsInfo( Entity::Player &player )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto activeQuestListPacket = makeZonePacket< FFXIVIpcQuests >( player.getId() );

  auto& quests = player.getQuestArrayRef();
  for( int32_t i = 0; i < 30; i++ )
  {
    if( quests[ i ].getId() != 0 )
      activeQuestListPacket->data().activeQuests[ i ] = quests[ i ].getQuestData();
  }

  server.queueForPlayer( player.getCharacterId(), activeQuestListPacket );

  auto questCompleteFlags = player.getQuestCompleteFlags();
  auto completeQuestListPacket = makeZonePacket< FFXIVIpcQuestCompleteList >( player.getId() );
  memcpy( completeQuestListPacket->data().questCompleteMask, questCompleteFlags.data(), questCompleteFlags.size() );
  server.queueForPlayer( player.getCharacterId(), completeQuestListPacket );

  sendQuestTracker( player );
}

