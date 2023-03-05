#pragma once

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Actor/Player.h>
#include "Forwards.h"

namespace Sapphire::Network::Util::Player
{
  void sendConfigFlags( Entity::Player& player );
  void sendOnlineStatus( Entity::Player& player );
  void sendBaseParams( Entity::Player& player );
  void sendHudParam( Entity::Player& player );
  void sendStatusUpdate( Entity::Player& player );

  void sendHuntingLog( Entity::Player& player );
  void sendTitleList( Entity::Player& player );

  void sendGrandCompany( Entity::Player& player );

  void sendActorControlSelf( Entity::Player& player, uint16_t category, uint32_t param1 = 0, uint32_t param2 = 0, uint32_t param3 = 0,
                             uint32_t param4 = 0, uint32_t param5 = 0 );

  void sendActorControlSelf( const std::set< uint64_t >& characterIds, Entity::Player& player, uint16_t category, uint32_t param1 = 0,
                             uint32_t param2 = 0, uint32_t param3 = 0, uint32_t param4 = 0, uint32_t param5 = 0 );

  void sendActorControl( Entity::Player& player, uint16_t category, uint32_t param1 = 0, uint32_t param2 = 0, uint32_t param3 = 0, uint32_t param4 = 0 );

  void sendActorControl( const std::set< uint64_t >& characterIds, Entity::Player& player, uint16_t category, uint32_t param1 = 0, uint32_t param2 = 0,
                         uint32_t param3 = 0, uint32_t param4 = 0 );

}