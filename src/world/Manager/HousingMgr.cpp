#include "HousingMgr.h"
#include <Logging/Logger.h>
#include <Database/DatabaseDef.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/PacketContainer.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketWrappers/ActorControlPacket142.h>
#include <Network/PacketWrappers/ActorControlPacket143.h>
#include <Network/CommonActorControl.h>

#include <unordered_map>
#include <cstring>

#include "Actor/Player.h"
#include "Actor/EventObject.h"
#include "Event/EventDefs.h"

#include "TerritoryMgr.h"
#include "Territory/Zone.h"
#include "Territory/HousingZone.h"
#include "Territory/Housing/HousingInteriorTerritory.h"
#include "HousingMgr.h"
#include "Territory/Land.h"
#include "Framework.h"
#include "ServerMgr.h"
#include "Territory/House.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

extern Sapphire::Framework g_fw;

Sapphire::World::Manager::HousingMgr::HousingMgr()
{

}

Sapphire::World::Manager::HousingMgr::~HousingMgr()
{

}

bool Sapphire::World::Manager::HousingMgr::init()
{

  return true;
}

uint32_t Sapphire::World::Manager::HousingMgr::toLandSetId( uint16_t territoryTypeId, uint8_t wardId ) const
{
  return ( static_cast< uint32_t >( territoryTypeId ) << 16 ) | wardId;
}

Sapphire::Data::HousingZonePtr Sapphire::World::Manager::HousingMgr::getHousingZoneByLandSetId( uint32_t id )
{
  auto pTeriMgr = g_fw.get< TerritoryMgr >();
  return std::dynamic_pointer_cast< HousingZone >( pTeriMgr->getZoneByLandSetId( id ) );
}

Sapphire::LandPtr Sapphire::World::Manager::HousingMgr::getLandByOwnerId( uint32_t id )
{
  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto res = pDb->query( "SELECT LandSetId, LandId FROM land WHERE OwnerId = " + std::to_string( id ) );

  if( !res->next() )
    return nullptr;

  auto hZone = getHousingZoneByLandSetId( res->getUInt( 1 ) );

  if( !hZone )
    return nullptr;

  return hZone->getLand( res->getUInt( 2 ) );
}

void Sapphire::World::Manager::HousingMgr::sendLandSignOwned( Entity::Player& player, const Common::LandIdent ident )
{
  player.setActiveLand( ident.landId, ident.wardNum );

  auto landSetId = toLandSetId( ident.territoryTypeId, ident.wardNum );
  auto hZone = getHousingZoneByLandSetId( landSetId );

  if( !hZone )
    return;

  auto land = hZone->getLand( ident.landId );
  if( !land )
    return;

  auto landInfoSignPacket = makeZonePacket< Server::FFXIVIpcLandInfoSign >( player.getId() );
  landInfoSignPacket->data().houseSize = land->getSize();
  landInfoSignPacket->data().houseType = static_cast< uint8_t >( land->getLandType() );
  landInfoSignPacket->data().landIdent = ident;
  landInfoSignPacket->data().houseIconAdd = land->getSharing();
  landInfoSignPacket->data().ownerId = player.getContentId(); // todo: should be real owner contentId, not player.contentId()

  if( auto house = land->getHouse() )
  {
    std::strcpy( landInfoSignPacket->data().estateName, house->getHouseName().c_str() );
    std::strcpy( landInfoSignPacket->data().estateGreeting, house->getHouseGreeting().c_str() );
  }

  uint32_t playerId = land->getOwnerId();
  std::string playerName = g_fw.get< Sapphire::ServerMgr >()->getPlayerNameFromDb( playerId );

  memcpy( &landInfoSignPacket->data().ownerName, playerName.c_str(), playerName.size() );

  player.queuePacket( landInfoSignPacket );
}

void Sapphire::World::Manager::HousingMgr::sendLandSignFree( Entity::Player& player, const Common::LandIdent ident )
{
  player.setActiveLand( ident.landId, ident.wardNum );

  auto landSetId = toLandSetId( ident.territoryTypeId, ident.wardNum );
  auto hZone = getHousingZoneByLandSetId( landSetId );

  if( !hZone )
    return;

  auto land = hZone->getLand( ident.landId );
  auto plotPricePacket = makeZonePacket< Server::FFXIVIpcLandPriceUpdate >( player.getId() );
  plotPricePacket->data().price = land->getCurrentPrice();
  plotPricePacket->data().timeLeft = land->getDevaluationTime();
  player.queuePacket( plotPricePacket );
}

Sapphire::LandPurchaseResult Sapphire::World::Manager::HousingMgr::purchaseLand( Entity::Player& player, uint8_t plot, uint8_t state )
{
  auto pHousing = std::dynamic_pointer_cast< HousingZone >( player.getCurrentZone() );

  auto plotPrice = pHousing->getLand( plot )->getCurrentPrice();
  auto gilAvailable = player.getCurrency( CurrencyType::Gil );
  auto pLand = pHousing->getLand( plot );

  if( !pLand )
    return LandPurchaseResult::ERR_INTERNAL;

  if( pLand->getState() != HouseState::forSale )
    return LandPurchaseResult::ERR_NOT_AVAILABLE;

  if( gilAvailable < plotPrice )
    return LandPurchaseResult::ERR_NOT_ENOUGH_GIL;


  switch( static_cast< LandPurchaseMode >( state ) )
  {
    case LandPurchaseMode::FC:
      player.sendDebug( "Free company house purchase aren't supported at this time." );
      return LandPurchaseResult::ERR_INTERNAL;

    case LandPurchaseMode::PRIVATE:
    {

      auto pOldLand = getLandByOwnerId( player.getId() );

      if( pOldLand )
        return LandPurchaseResult::ERR_NO_MORE_LANDS_FOR_CHAR;

      player.removeCurrency( CurrencyType::Gil, plotPrice );
      pLand->setOwnerId( player.getId() );
      pLand->setState( HouseState::sold );
      pLand->setLandType( Common::LandType::Private );

      player.setLandFlags( LandFlagsSlot::Private, 0x00, plot,
                                 pHousing->getWardNum(), pHousing->getTerritoryTypeId() );

      player.sendLandFlagsSlot( LandFlagsSlot::Private );

      //pLand->setLandName( "Private Estate" + std::to_string( pHousing->getWardNum() ) + "-" + std::to_string( plot )   );
      pLand->updateLandDb();

      pHousing->sendLandUpdate( plot );
      return LandPurchaseResult::SUCCESS;
    }

    default:
      return LandPurchaseResult::ERR_INTERNAL;
  }

}

bool Sapphire::World::Manager::HousingMgr::relinquishLand( Entity::Player& player, uint8_t plot )
{
  // TODO: Fix "permissions" being sent incorrectly
  // TODO: Add checks for land state before relinquishing
  auto pHousing = std::dynamic_pointer_cast< HousingZone >( player.getCurrentZone() );

  auto pLand = pHousing->getLand( plot );
  auto plotMaxPrice = pLand->getCurrentPrice();
  auto landOwnerId = pLand->getOwnerId();

  // can't relinquish when you are not the owner
  // TODO: actually use permissions here for FC houses
  if( landOwnerId != player.getId() )
  {
    auto msgPkt = makeActorControl143( player.getId(), ActorControl::LogMsg, 3304, 0 );
    player.queuePacket( msgPkt );
    return false;
  }

  // unable to relinquish if there is a house built
  // TODO: additionally check for yard items
  if( pLand->getHouse() )
  {
    auto msgPkt = makeActorControl143( player.getId(), ActorControl::LogMsg, 3315, 0 );
    player.queuePacket( msgPkt );
    return false;
  }

  pLand->setCurrentPrice( pLand->getMaxPrice() );
  pLand->setOwnerId( 0 );
  pLand->setState( HouseState::forSale );
  pLand->setLandType( Common::LandType::none );
  pLand->updateLandDb();

  player.setLandFlags( LandFlagsSlot::Private, 0x00, 0xFF, 0xFF, 0xFF );

  player.sendLandFlagsSlot( LandFlagsSlot::Private );

  auto screenMsgPkt2 = makeActorControl143( player.getId(), ActorControl::LogMsg, 3351, 0x1AA,
                                            pLand->getWardNum() + 1, plot + 1 );
  player.queuePacket( screenMsgPkt2 );
  pHousing->sendLandUpdate( plot );

  return true;
}

void Sapphire::World::Manager::HousingMgr::sendWardLandInfo( Entity::Player& player, uint8_t wardId, uint16_t territoryTypeId )
{
  auto landSetId = toLandSetId( territoryTypeId, wardId );
  auto hZone = getHousingZoneByLandSetId( landSetId );

  if( !hZone )
    return;

  auto wardInfoPacket = makeZonePacket< Server::FFXIVIpcHousingWardInfo >( player.getId() );
  wardInfoPacket->data().landIdent.wardNum = wardId;
  wardInfoPacket->data().landIdent.territoryTypeId = territoryTypeId;

  // todo: properly get worldId
  wardInfoPacket->data().landIdent.worldId = 67;

  for( int i = 0; i < 60; i++ )
  {
    auto land = hZone->getLand( i );
    assert( land );

    auto& entry = wardInfoPacket->data().houseInfoEntry[ i ];

    // retail always sends the house price in this packet, even after the house has been sold
    // so I guess we do the same
    entry.housePrice = land->getCurrentPrice();

    if( land->getState() == Common::HouseState::forSale )
      continue;

    if( auto house = land->getHouse() )
    {
      if( !house->getHouseGreeting().empty() )
        entry.infoFlags |= WardlandFlags::HasEstateGreeting;
    }

    switch( land->getLandType() )
    {
      case LandType::FreeCompany:
        entry.infoFlags |= Common::WardlandFlags::IsEstateOwned | Common::WardlandFlags::IsFreeCompanyEstate;

        // todo: send FC name

        break;

      case LandType::Private:
        entry.infoFlags |= Common::WardlandFlags::IsEstateOwned;

        auto owner = land->getOwnerId();
        auto playerName = g_fw.get< Sapphire::ServerMgr >()->getPlayerNameFromDb( owner );
        memcpy( &entry.estateOwnerName, playerName.c_str(), playerName.size() );

        break;
    }

    // todo: check we have an estate message and set the flag
    // todo: check if estate allows public entry
  }

  player.queuePacket( wardInfoPacket );
}

void Sapphire::World::Manager::HousingMgr::sendEstateGreeting( Entity::Player& player, const Common::LandIdent ident )
{
  auto landSetId = toLandSetId( ident.territoryTypeId, ident.wardNum );
  auto hZone = getHousingZoneByLandSetId( landSetId );

  if( !hZone )
    return;

  auto land = hZone->getLand( ident.landId );
  if( !land )
    return;

  auto house = land->getHouse();
  if( !house )
    return;

  auto greetingPacket = makeZonePacket< FFXIVIpcHousingEstateGreeting >( player.getId() );

  greetingPacket->data().landIdent = ident;

  auto greeting = house->getHouseGreeting();
  memcpy( &greetingPacket->data().message, greeting.c_str(), greeting.size() );

  player.queuePacket( greetingPacket );
}

void Sapphire::World::Manager::HousingMgr::buildPresetEstate( Entity::Player& player, uint8_t plotNum, uint32_t presetItem )
{
  auto hZone = std::dynamic_pointer_cast< HousingZone >( player.getCurrentZone() );

  if( !hZone )
    return;

  auto pLand = hZone->getLand( plotNum );
  if( !pLand )
    return;

  // todo: when doing FC houses, look up the type from the original purchase and check perms from FC and set state accordingly
  if( pLand->getOwnerId() != player.getId() )
    return;

  // todo: check if permit is in inventory and remove one

  if( !pLand->setPreset( presetItem ) )
    return;

  pLand->setState( HouseState::privateHouse );
  pLand->setLandType( LandType::Private );
  hZone->sendLandUpdate( plotNum );

  auto pSuccessBuildingPacket = makeActorControl142( player.getId(), ActorControl::BuildPresetResponse, plotNum );

  player.queuePacket( pSuccessBuildingPacket );

  pLand->updateLandDb();

  // start house built event
  // CmnDefHousingBuildHouse_00149
  player.eventStart( player.getId(), 0x000B0095, Event::EventHandler::EventType::Housing, 1, 1 );
  player.playScene( 0x000B0095, 0, SET_BASE | HIDE_HOTBAR , 0, 1, plotNum, nullptr );

  player.setLandFlags( LandFlagsSlot::Private, EstateBuilt, pLand->getLandId(), pLand->getWardNum(), pLand->getTerritoryTypeId() );
  player.sendLandFlagsSlot( LandFlagsSlot::Private );

  hZone->registerHouseEntranceEObj( plotNum );
}

void Sapphire::World::Manager::HousingMgr::requestEstateRename( Entity::Player& player, const Common::LandIdent ident )
{
  auto landSetId = toLandSetId( ident.territoryTypeId, ident.wardNum );
  auto hZone = getHousingZoneByLandSetId( landSetId );

  if( !hZone )
    return;

  auto land = hZone->getLand( ident.landId );

  auto house = land->getHouse();
  if( !house )
    return;

  auto landRenamePacket = makeZonePacket< Server::FFXIVIpcLandRename >( player.getId() );

  landRenamePacket->data().landIdent = ident;
  memcpy( &landRenamePacket->data().houseName, house->getHouseName().c_str(), 20 );

  player.queuePacket( landRenamePacket );
}

void Sapphire::World::Manager::HousingMgr::requestEstateEditGreeting( Entity::Player& player, const Common::LandIdent ident )
{
  auto landSetId = toLandSetId( ident.territoryTypeId, ident.wardNum );
  auto hZone = getHousingZoneByLandSetId( landSetId );

  if( !hZone )
    return;

  auto land = hZone->getLand( ident.landId );
  if( !land )
    return;

  auto house = land->getHouse();
  if( !house )
    return;

  auto estateGreetingPacket = makeZonePacket< Server::FFXIVIpcHousingEstateGreeting >( player.getId() );

  estateGreetingPacket->data().landIdent = ident;
  memcpy( &estateGreetingPacket->data().message, house->getHouseGreeting().c_str(), sizeof( estateGreetingPacket->data().message ) );

  player.queuePacket( estateGreetingPacket );
}

void Sapphire::World::Manager::HousingMgr::updateEstateGreeting( Entity::Player& player, const Common::LandIdent ident, const std::string& greeting )
{
  auto landSetId = toLandSetId( ident.territoryTypeId, ident.wardNum );
  auto zone = getHousingZoneByLandSetId( landSetId );

  if( !zone )
    return;

  auto land = zone->getLand( ident.landId );
  if( !land )
    return;

  // todo: implement proper permissions checks
  if( land->getOwnerId() != player.getId() )
    return;

  auto house = land->getHouse();
  if( !house )
    return;

  house->setHouseGreeting( greeting );

  // Greeting updated.
  player.sendLogMessage( 3381 );
}

void Sapphire::World::Manager::HousingMgr::requestEstateEditGuestAccess( Entity::Player& player, const Common::LandIdent ident )
{
  auto landSetId = toLandSetId( ident.territoryTypeId, ident.wardNum );
  auto hZone = getHousingZoneByLandSetId( landSetId );

  if( !hZone )
    return;

  auto land = hZone->getLand( ident.landId );
  if( !land )
    return;

  // todo: add proper permission check
  if( land->getOwnerId() != player.getId() )
    return;

  auto packet = makeZonePacket< FFXIVIpcHousingShowEstateGuestAccess >( player.getId() );
  packet->data().ident = ident;

  player.queuePacket( packet );
}

Sapphire::Common::LandIdent Sapphire::World::Manager::HousingMgr::clientTriggerParamsToLandIdent( uint32_t param11, uint32_t param12, bool use16bits ) const
{
  Common::LandIdent ident;
  ident.worldId = param11 >> 16;
  ident.territoryTypeId = param11 & 0xFFFF;

  if( use16bits )
  {
    ident.wardNum = param12 >> 16;
    ident.landId = param12 & 0xFFFF;
  }
  else
  {
    ident.wardNum = (param12 >> 8) & 0xFF;
    ident.landId = param12 & 0xFF;
  }

  return ident;
}

void Sapphire::World::Manager::HousingMgr::sendHousingInventory( Entity::Player& player, uint16_t inventoryType, uint8_t plotNum )
{
  Sapphire::LandPtr targetLand;

  // plotNum will be 255 in the event that it's an internal zone
  // and we have to switch up our way of getting the LandPtr
  if( plotNum == 255 )
  {
    auto internalZone = std::dynamic_pointer_cast< Territory::Housing::HousingInteriorTerritory >( player.getCurrentZone() );
    if( !internalZone )
      return;

    auto ident = internalZone->getIdent();

    auto landSetId = toLandSetId( ident.territoryTypeId, ident.wardNum );
    auto exteriorZone = getHousingZoneByLandSetId( landSetId );

    if( !exteriorZone )
      return;

    targetLand = exteriorZone->getLand( ident.landId );
  }
  else
  {
    auto zone = std::dynamic_pointer_cast< HousingZone >( player.getCurrentZone() );
    if( !zone )
      return;

    targetLand = zone->getLand( plotNum );
  }

  if( !targetLand )
    return;

  // todo: add proper permissions checks
  if( targetLand->getOwnerId() != player.getId() )
    return;

  player.sendDebug( "got inventory for plot: " + targetLand->getHouse()->getHouseName() );
}