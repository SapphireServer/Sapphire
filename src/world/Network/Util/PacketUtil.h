#pragma once

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Actor/Player.h>
#include "Forwards.h"
#include <Common.h>

namespace Sapphire::Network::Util::Packet
{
  void sendConfigFlags( Entity::Player& player );
  void sendOnlineStatus( Entity::Player& player );
  void sendBaseParams( Entity::Player& player );
  void sendHudParam( Entity::Chara& player );
  void sendStatusUpdate( Entity::Player& player );

  void sendHuntingLog( Entity::Player& player );
  void sendTitleList( Entity::Player& player );

  void sendGrandCompany( Entity::Player& player );

  void sendDeletePlayer( Entity::Player& player, uint32_t actorId, uint8_t spawnIndex );
  void sendDeleteObject( Entity::Player& player, uint8_t spawnIndex );

  void sendHateList( Entity::Player& player );

  void sendMount( Entity::Player& player );

  /* Inventory packets */

  /*! send the ItemOperation packet to client with src attributes */
  void sendItemOperation( Entity::Player& player, uint32_t id, ItemPtr item, uint16_t invType, int16_t type, Common::ITEM_OPERATION_TYPE opType, uint32_t seq );

  /*! send the ItemOperation packet to client with dst attributes */
  void sendItemOperationDst( Entity::Player& player, uint32_t id,  ItemPtr item, uint32_t storageId, int16_t slotId, Common::ITEM_OPERATION_TYPE opType, uint32_t seq );

  /*! send the ItemOperationBatch packet to client */
  void sendItemOperationBatch( Entity::Player& player, uint32_t id, uint32_t seq, Common::ITEM_OPERATION_TYPE opType );

  /************/

  void sendEquip( Entity::Player& player );

  void sendCondition( Entity::Player& player );

  void sendRecastGroups( Entity::Player& player );

  void sendAchievementList( Entity::Player& player );

  void sendRestingUpdate( Entity::Player& player );

  void sendLogin( Entity::Player& player );

  void sendPlayerSetup( Entity::Player& player );

  void sendChangeClass( Entity::Player& player );

  void sendContentAttainFlags( Entity::Player& player );

  void sendInitZone( Entity::Player& player );

  void sendDailyQuests( Entity::Player& player );
  void sendQuestRepeatFlags( Entity::Player& player );

  void sendServerNotice( Entity::Player& player, const std::string& message );

  void sendChat( Entity::Player& player, Common::ChatType chatType, const std::string& message );

  void sendActorControlSelf( Entity::Player& player, uint32_t srcId, uint16_t category, uint32_t param1 = 0, uint32_t param2 = 0, uint32_t param3 = 0,
                             uint32_t param4 = 0, uint32_t param5 = 0 );

  void sendActorControlSelf( const std::set< uint64_t >& characterIds, uint32_t srcId, uint16_t category, uint32_t param1 = 0,
                             uint32_t param2 = 0, uint32_t param3 = 0, uint32_t param4 = 0, uint32_t param5 = 0 );

  void sendActorControl( Entity::Player& player, uint32_t srcId, uint16_t category, uint32_t param1 = 0, uint32_t param2 = 0, uint32_t param3 = 0, uint32_t param4 = 0 );

  void sendActorControl( const std::set< uint64_t >& characterIds, uint32_t srcId, uint16_t category, uint32_t param1 = 0, uint32_t param2 = 0,
                         uint32_t param3 = 0, uint32_t param4 = 0 );

  void sendActorControlTarget( Entity::Player& player, uint32_t srcId, uint16_t category, uint32_t param1 = 0, uint32_t param2 = 0, uint32_t param3 = 0,
                               uint32_t param4 = 0, uint32_t param5 = 0, uint32_t param6 = 0 );

  void sendActorControlTarget( const std::set< uint64_t >& characterIds, uint32_t srcId, uint16_t category, uint32_t param1 = 0,
                               uint32_t param2 = 0, uint32_t param3 = 0, uint32_t param4 = 0, uint32_t param5 = 0, uint32_t param6 = 0 );

  void sendBattleTalk( Sapphire::Entity::Player& player, uint32_t battleTalkId, uint32_t handlerId,
                       uint32_t kind, uint32_t nameId, uint32_t talkerId, uint32_t time,
                       uint32_t param1 = 0, uint32_t param2= 0, uint32_t param3 = 0, uint32_t param4 = 0,
                       uint32_t param5 = 0, uint32_t param6= 0, uint32_t param7 = 0, uint32_t param8 = 0 );
}