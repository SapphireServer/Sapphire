#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Network/CommonActorControl.h>
#include <Network/PacketContainer.h>
#include <datReader/DatCategories/bg/LgbTypes.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>

#include <Service.h>

#include "Network/GameConnection.h"

#include "Territory/HousingZone.h"
#include "Territory/Land.h"
#include "Territory/House.h"

#include "Network/PacketWrappers/PlayerSetupPacket.h"

#include "Manager/HousingMgr.h"
#include "Manager/TerritoryMgr.h"

#include "Action/Action.h"

#include "Session.h"
#include "WorldServer.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::Packets::WorldPackets::Client;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Manager;


void Sapphire::Network::GameConnection::landRenameHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                           Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcHousingHouseName >( inPacket );

  auto& housingMgr = Common::Service< HousingMgr >::ref();
  auto& teriMgr = Common::Service< TerritoryMgr >::ref();

  auto landSetId = housingMgr.toLandSetId( packet.data().landId.territoryTypeId, static_cast< int8_t >( packet.data().landId.wardNum ) );

  auto pTeri = teriMgr.getTerritoryByGuId( landSetId );
  auto hZone = std::dynamic_pointer_cast< HousingZone >( pTeri );

  if( !hZone )
    return;

  auto pLand = hZone->getLand( static_cast< uint8_t >( packet.data().landId.landId ) );
  if( !pLand )
    return;

  // todo: check perms for fc houses and shit
  if( pLand->getOwnerId() != player.getCharacterId() )
    return;

  auto pHouse = pLand->getHouse();
  if( pHouse )
    pHouse->setHouseName( packet.data().houseName );

  // todo: this packet is weird, retail sends it with some unknown shit at the start but it doesn't seem to do anything
  auto nameUpdatePacket = makeZonePacket< WorldPackets::Server::FFXIVIpcHousingHouseName >( player.getId() );
  memcpy( &nameUpdatePacket->data().Name, &packet.data().houseName, sizeof( packet.data().houseName ) );

  auto& server = Common::Service< World::WorldServer >::ref();
  // todo: who does this get sent to? just the person who renamed it?
  server.queueForPlayer( player.getCharacterId(), nameUpdatePacket );
}

void Sapphire::Network::GameConnection::buildPresetHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                           Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcBuildPresetHandler >( inPacket );

  auto& housingMgr = Common::Service< HousingMgr >::ref();
  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  auto pTeri = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
  auto hZone = std::dynamic_pointer_cast< HousingZone >( pTeri );
  housingMgr.buildPresetEstate( player, *hZone, packet.data().plotNum, packet.data().itemId );
}

void Sapphire::Network::GameConnection::housingUpdateGreetingHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                     Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcHousingGreeting >( inPacket );

  auto& housingMgr = Common::Service< HousingMgr >::ref();

  housingMgr.updateEstateGreeting( player, packet.data().landId, std::string( packet.data().greeting ) );
}

void Sapphire::Network::GameConnection::reqPlaceHousingItem( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  auto& housingMgr = Common::Service< HousingMgr >::ref();
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcHousingPlaceYardItem >( inPacket );
  const auto& data = packet.data();

  Logger::debug(
          "Dump:\n{0}",
          Util::binaryToHexDump( const_cast< uint8_t* >( &inPacket.data[ 0 ] ),
                                 static_cast< uint16_t >( inPacket.segHdr.size - 0x10 ) )
  );

  if( data.UserData == 1 )
  {
    housingMgr.reqPlaceHousingItem( player, data.landIdOrIndex.landId, data.StorageId, static_cast< uint8_t >( data.ContainerIndex ),
    data.Pos, data.Rotation );
  }
  else
   housingMgr.reqPlaceItemInStore( player, data.landIdOrIndex.landId, data.StorageId, static_cast< uint8_t >( data.ContainerIndex ) );

}

void Sapphire::Network::GameConnection::reqMoveHousingItem( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  /*
  auto& housingMgr = Common::Service< HousingMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcHousingUpdateObjectPosition >( inPacket );
  const auto& data = packet.data();

  housingMgr.reqMoveHousingItem( player, data.ident, data.slot, data.pos, data.rotation );
  */
}
