#include <Common.h>
#include <Exd/ExdData.h>
#include <Util/Util.h>
#include <Service.h>

#include "WorldServer.h"

#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Exd/ExdData.h>
#include <Network/PacketContainer.h>

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/Notice2Packet.h"

#include "QuestMgr.h"

#include "Actor/Player.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

void Sapphire::World::Manager::QuestMgr::onUpdateQuest( Entity::Player& player, uint8_t questIndex )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto quests = player.getQuestArrayRef();
  auto questUpdatePacket = makeZonePacket< FFXIVIpcQuest >( player.getId() );
  questUpdatePacket->data().index = questIndex;
  questUpdatePacket->data().questInfo = quests[ questIndex ].getQuestData();
  server.queueForPlayer( player.getCharacterId(), questUpdatePacket );

  sendQuestTracker( player );
}

void Sapphire::World::Manager::QuestMgr::onCompleteQuest( Entity::Player& player, uint16_t questId )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto questFinishPacket = makeZonePacket< FFXIVIpcQuestFinish >( player.getId() );
  questFinishPacket->data().questId = questId;
  questFinishPacket->data().flag1 = 1;
  questFinishPacket->data().flag2 = 1;
  server.queueForPlayer( player.getCharacterId(), questFinishPacket );
}

void Sapphire::World::Manager::QuestMgr::onRemoveQuest( Sapphire::Entity::Player &player, uint8_t questIndex )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto questUpdatePacket = makeZonePacket< FFXIVIpcQuest >( player.getId() );
  questUpdatePacket->data().index = static_cast< uint8_t >( questIndex );
  questUpdatePacket->data().questInfo.c.questId = 0;
  questUpdatePacket->data().questInfo.c.sequence = 0xFF;
  server.queueForPlayer( player.getCharacterId(), questUpdatePacket );

  sendQuestTracker( player );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void Sapphire::World::Manager::QuestMgr::sendQuestTracker( Entity::Player& player )
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

void Sapphire::World::Manager::QuestMgr::sendQuestsInfo( Sapphire::Entity::Player &player )
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

