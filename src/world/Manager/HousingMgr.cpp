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
#include "InventoryMgr.h"
#include "Inventory/HousingItem.h"
#include "Inventory/ItemContainer.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

extern Sapphire::Framework g_fw;

Sapphire::World::Manager::HousingMgr::HousingMgr()
{
  m_containerMap[ 0 ] = std::make_pair( InventoryType::HousingInteriorPlacedItems1, InventoryType::HousingInteriorStoreroom1 );
  m_containerMap[ 1 ] = std::make_pair( InventoryType::HousingInteriorPlacedItems1, InventoryType::HousingInteriorStoreroom1 );
  m_containerMap[ 2 ] = std::make_pair( InventoryType::HousingInteriorPlacedItems1, InventoryType::HousingInteriorStoreroom1 );
  m_containerMap[ 3 ] = std::make_pair( InventoryType::HousingInteriorPlacedItems1, InventoryType::HousingInteriorStoreroom1 );
  m_containerMap[ 4 ] = std::make_pair( InventoryType::HousingInteriorPlacedItems1, InventoryType::HousingInteriorStoreroom1 );
  m_containerMap[ 5 ] = std::make_pair( InventoryType::HousingInteriorPlacedItems1, InventoryType::HousingInteriorStoreroom1 );
  m_containerMap[ 6 ] = std::make_pair( InventoryType::HousingInteriorPlacedItems1, InventoryType::HousingInteriorStoreroom1 );
  m_containerMap[ 7 ] = std::make_pair( InventoryType::HousingInteriorPlacedItems1, InventoryType::HousingInteriorStoreroom1 );
}

Sapphire::World::Manager::HousingMgr::~HousingMgr() = default;

bool Sapphire::World::Manager::HousingMgr::init()
{
  auto log = g_fw.get< Sapphire::Logger >();

  log->info( "HousingMgr: Caching housing land init data" );
  //LAND_SEL_ALL

  // 18 wards per territory, 4 territories
  m_landCache.reserve( 18 * 4 );

  initLandCache();

  log->debug( "HousingMgr: Checking land counts" );

  uint32_t houseCount = 0;
  for( auto& landSet : m_landCache )
  {
    auto count = landSet.second.size();

    houseCount += count;

    if( landSet.second.size() != 60 )
    {
      log->fatal( "LandSet " + std::to_string( landSet.first ) + " is missing land entries. Only have " + std::to_string( count ) + " land entries." );
      return false;
    }
  }

  log->info( "HousingMgr: Cached " + std::to_string( houseCount ) + " houses" );

  /////

  if( !loadEstateInventories() )
    return false;

  return true;
}

bool Sapphire::World::Manager::HousingMgr::loadEstateInventories()
{
  auto log = g_fw.get< Sapphire::Logger >();

  log->info( "HousingMgr: Loading inventories for estates" );

  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();

  auto stmt = pDb->getPreparedStatement( Db::LAND_INV_SEL_ALL );
  auto res = pDb->query( stmt );

  uint32_t itemCount = 0;
  while( res->next() )
  {
    //uint64_t uId, uint32_t catalogId, uint64_t model1, uint64_t model2, bool isHq
    auto ident = res->getUInt64( "LandIdent" );
    auto containerId = res->getUInt16( "ContainerId" );
    auto itemId = res->getUInt64( "ItemId" );
    auto slot = res->getUInt16( "SlotId" );
    auto catalogId = res->getUInt( "catalogId" );
    auto stain = res->getUInt8( "stain" );
    auto characterId = res->getUInt64( "CharacterId" );

    auto item = Inventory::make_HousingItem( itemId, catalogId );
    item->setStain( stain );
    item->setStackSize( 1 );
    // todo: need to set the owner character id on the item

    // set world pos on item if its in an placed item container
    if( isPlacedItemsInventory( static_cast< Common::InventoryType >( containerId ) ) )
    {
      item->setPos( {
        res->getFloat( "PosX" ),
        res->getFloat( "PosY" ),
        res->getFloat( "PosZ" )
      } );

      item->setRot( res->getFloat( "Rotation" ) );
    }

    ContainerIdToContainerMap& estateInv = m_estateInventories[ ident ];

    // check if containerId exists, it always should - if it doesn't, something went wrong
    auto container = estateInv.find( containerId );
    assert( container != estateInv.end() );

    container->second->setItem( slot, item );

    itemCount++;
  }

  log->debug( "HousingMgr: Loaded " + std::to_string( itemCount ) + " inventory items" );

  return true;
}

void Sapphire::World::Manager::HousingMgr::initLandCache()
{
  auto log = g_fw.get< Sapphire::Logger >();
  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();

  auto stmt = pDb->getPreparedStatement( Db::LAND_SEL_ALL );
  auto res = pDb->query( stmt );

  while( res->next() )
  {
    LandCacheEntry entry;

    // land stuff
    entry.m_landSetId = res->getUInt64( "LandSetId" );
    entry.m_landId = res->getUInt( "LandId" );

    entry.m_type = static_cast< Common::LandType >( res->getUInt( "Type" ) );
    entry.m_size = res->getUInt8( "Size" );
    entry.m_status = res->getUInt8( "Status" );
    entry.m_currentPrice = res->getUInt64( "LandPrice" );
    entry.m_updateTime = res->getUInt64( "UpdateTime" );
    entry.m_ownerId = res->getUInt64( "OwnerId" );

    entry.m_houseId = res->getUInt64( "HouseId" );

    // house stuff
    entry.m_estateWelcome = res->getString( "Welcome" );
    entry.m_estateComment = res->getString( "Comment" );
    entry.m_estateName = res->getString( "HouseName" );
    entry.m_buildTime = res->getUInt64( "BuildTime" );
    entry.m_endorsements = res->getUInt64( "Endorsements" );

    m_landCache[ entry.m_landSetId ].push_back( entry );

    uint16_t maxExternalItems = 0;
    uint16_t maxInternalItems = 0;

    // init inventory containers
    switch( entry.m_size )
    {
      case HouseSize::Cottage:
        entry.m_maxPlacedExternalItems = 20;
        entry.m_maxPlacedInternalItems = 200;
        break;
      case HouseSize::House:
        entry.m_maxPlacedExternalItems = 30;
        entry.m_maxPlacedInternalItems = 300;
        break;
      case HouseSize::Mansion:
        entry.m_maxPlacedExternalItems = 40;
        entry.m_maxPlacedInternalItems = 400;
        break;
      default:
        // this should never ever happen, if it does the db is fucked
        log->error( "HousingMgr: Plot " + std::to_string( entry.m_landId ) + " in landset " + std::to_string( entry.m_landSetId ) +
                    " has an invalid land size, defaulting to cottage." );
        entry.m_maxPlacedExternalItems = 20;
        entry.m_maxPlacedInternalItems = 200;
        break;
    }

    // setup containers
    // todo: this is pretty garbage
    Common::LandIdent ident;
    ident.territoryTypeId = entry.m_landSetId >> 16;
    ident.wardNum = entry.m_landSetId & 0xFFFF;
    ident.landId = entry.m_landId;
    ident.worldId = 67;

    auto& containers = getEstateInventory( ident );

    auto makeContainer = [ &containers ]( Common::InventoryType type, uint16_t size )
    {
      containers[ type ] = make_ItemContainer( type, size, "houseiteminventory", true );
    };

    uint16_t count = 0;
    for( int i = 0; i < 8; ++i )
    {
      if( count >= entry.m_maxPlacedInternalItems )
        break;

      auto& pair = m_containerMap[ i ];

      makeContainer( pair.first, 50 );
      makeContainer( pair.second, 50 );

      count += 50;
    }

    // exterior
    makeContainer( InventoryType::HousingExteriorPlacedItems, entry.m_maxPlacedExternalItems );
    makeContainer( InventoryType::HousingExteriorStoreroom, entry.m_maxPlacedExternalItems );

    // fixed containers
    makeContainer( InventoryType::HousingInteriorAppearance, 10 );
    makeContainer( InventoryType::HousingExteriorAppearance, 8 );

  }
}

uint64_t Sapphire::World::Manager::HousingMgr::getNextHouseId()
{
  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto pQR = pDb->query( "SELECT MAX( HouseId ) FROM house" );

  if( !pQR->next() )
    return 0;

  return pQR->getUInt64( 1 ) + 1;
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

      player.setLandFlags( LandFlagsSlot::Private, 0x00, pLand->getLandIdent() );

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

  Common::LandIdent ident { 0xFF, 0xFF, 0xFF, 0xFF };

  player.setLandFlags( LandFlagsSlot::Private, 0x00, ident );

  player.sendLandFlagsSlot( LandFlagsSlot::Private );

  auto screenMsgPkt2 = makeActorControl143( player.getId(), ActorControl::LogMsg, 3351, 0x1AA,
                                            pLand->getLandIdent().wardNum + 1, plot + 1 );
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

bool Sapphire::World::Manager::HousingMgr::initHouseModels( Entity::Player& player, LandPtr land, uint32_t presetCatalogId )
{
  auto house = land->getHouse();
  assert( house );

  auto itemMax = land->getInventoryItemMax();

  // type, maxSize, tableName, isMultiStorage
  auto intContainer = make_ItemContainer( InventoryType::HousingInteriorAppearance, itemMax.second, "houseiteminventory", true );
  auto extContainer = make_ItemContainer( InventoryType::HousingExteriorAppearance, itemMax.first, "houseiteminventory", true );

  // add containers to inv collection
  auto& houseInventory = getEstateInventory( house->getLandIdent() );
  houseInventory[ InventoryType::HousingInteriorAppearance ] = intContainer;
  houseInventory[ InventoryType::HousingExteriorAppearance ] = extContainer;

  auto exdData = g_fw.get< Sapphire::Data::ExdDataGenerated >();
  auto preset = exdData->get< Sapphire::Data::HousingPreset >( getItemAdditionalData( presetCatalogId ) );
  if( !preset )
    return false;

  // high iq shit
  auto invMap = std::map< uint16_t, std::map< uint32_t, int32_t > >
  {
    // external
    {
      InventoryType::HousingExteriorAppearance,
      {
        { HouseExteriorSlot::ExteriorRoof, preset->exteriorRoof },
        { HouseExteriorSlot::ExteriorWall, preset->exteriorWall },
        { HouseExteriorSlot::ExteriorWindow, preset->exteriorWindow },
        { HouseExteriorSlot::ExteriorDoor, preset->exteriorDoor }
      }
    },

    // internal
    {
      InventoryType::HousingInteriorAppearance,
      {
        // lobby/middle floor
        { HousingInteriorSlot::InteriorWall, preset->interiorWall },
        { HousingInteriorSlot::InteriorFloor, preset->interiorFlooring },
        { HousingInteriorSlot::InteriorLight, preset->interiorLighting },

        // attic
        { HousingInteriorSlot::InteriorWall_Attic, preset->otherFloorWall },
        { HousingInteriorSlot::InteriorFloor_Attic, preset->otherFloorFlooring },
        { HousingInteriorSlot::InteriorLight_Attic, preset->otherFloorLighting },

        // basement
        { HousingInteriorSlot::InteriorWall_Basement, preset->basementWall },
        { HousingInteriorSlot::InteriorFloor_Basement, preset->basementFlooring },
        { HousingInteriorSlot::InteriorLight_Basement, preset->basementLighting },
      }
    }
  };

  auto invMgr = g_fw.get< InventoryMgr >();

  // create and link items
  for( auto& destContainer : invMap )
  {
    auto container = houseInventory[ destContainer.first ];

    for( auto& item : destContainer.second )
    {
      // small houses attic is just 0, ignore them
      if( item.second == 0 )
        continue;

      auto pItem = invMgr->createItem( player, item.second );

      container->setItem( item.first, pItem );
    }

    invMgr->saveHousingContainer( land->getLandIdent(), container );
  }

  // lift off
  updateHouseModels( house );

  return true;
}

void Sapphire::World::Manager::HousingMgr::createHouse( Sapphire::HousePtr house ) const
{
  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();

  auto stmt = pDb->getPreparedStatement( Db::HOUSING_HOUSE_INS );
  // LandSetId, HouseId, HouseName

  stmt->setUInt( 1, house->getLandSetId() );
  stmt->setUInt( 2, house->getId() );
  stmt->setString( 3, house->getHouseName() );

  pDb->execute( stmt );
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

  // create house
  auto ident = pLand->getLandIdent();
  auto house = make_House( getNextHouseId(), pLand->getLandSetId(), ident,
                           "Estate #" + std::to_string( ident.landId + 1 ), "" );

  pLand->setHouse( house );

  // create inventory items
  if( !initHouseModels( player, pLand, presetItem ) )
    return;

  createHouse( house );

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

  player.setLandFlags( LandFlagsSlot::Private, EstateBuilt, ident );
  player.sendLandFlagsSlot( LandFlagsSlot::Private );

  hZone->registerEstateEntranceEObj( plotNum );
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

void Sapphire::World::Manager::HousingMgr::sendEstateInventory( Entity::Player& player, uint16_t inventoryType,
                                                                uint8_t plotNum )
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

  auto& containers = getEstateInventory( targetLand->getLandIdent() );

  auto invMgr = g_fw.get< Manager::InventoryMgr >();
  invMgr->sendInventoryContainer( player, containers[ inventoryType ] );
}

const Sapphire::World::Manager::HousingMgr::LandSetLandCacheMap&
  Sapphire::World::Manager::HousingMgr::getLandCacheMap()
{
  return m_landCache;
}

Sapphire::World::Manager::HousingMgr::LandIdentToInventoryContainerMap&
  Sapphire::World::Manager::HousingMgr::getEstateInventories()
{
  return m_estateInventories;
}

Sapphire::World::Manager::HousingMgr::ContainerIdToContainerMap&
  Sapphire::World::Manager::HousingMgr::getEstateInventory( uint64_t ident )
{
  return m_estateInventories[ ident ];
}

Sapphire::World::Manager::HousingMgr::ContainerIdToContainerMap&
  Sapphire::World::Manager::HousingMgr::getEstateInventory( Sapphire::Common::LandIdent ident )
{
  auto u64ident = *reinterpret_cast< uint64_t* >( &ident );

  return getEstateInventory( u64ident );
}

void Sapphire::World::Manager::HousingMgr::updateHouseModels( Sapphire::HousePtr house )
{
  assert( house );

  auto& containers = getEstateInventory( house->getLandIdent() );

  auto extContainer = containers.find( static_cast< uint16_t >( InventoryType::HousingExteriorAppearance ) );
  if( extContainer != containers.end() )
  {
    for( auto& item : extContainer->second->getItemMap() )
    {
      house->setExteriorModel( static_cast< Common::HouseExteriorSlot >( item.first ),
                               getItemAdditionalData( item.second->getId() ), item.second->getStain() );
    }
  }
  else
  {
    g_fw.get< Logger >()->error( "Plot " + std::to_string( house->getLandIdent().landId ) + " has an invalid inventory configuration for outdoor appearance." );
  }

  auto intContainer = containers.find( static_cast< uint16_t >( InventoryType::HousingInteriorAppearance ) );
  if( intContainer != containers.end() )
  {
    for( auto& item : intContainer->second->getItemMap() )
    {
      house->setInteriorModel( static_cast< Common::HousingInteriorSlot >( item.first ),
                               getItemAdditionalData( item.second->getId() ) );
    }
  }
  else
  {
    g_fw.get< Logger >()->error( "Plot " + std::to_string( house->getLandIdent().landId ) + " has an invalid inventory configuration for indoor appearance." );
  }
}

uint32_t Sapphire::World::Manager::HousingMgr::getItemAdditionalData( uint32_t catalogId )
{
  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  auto info = pExdData->get< Sapphire::Data::Item >( catalogId );
  return info->additionalData;
}

bool Sapphire::World::Manager::HousingMgr::isPlacedItemsInventory( Sapphire::Common::InventoryType type )
{
  return type == InventoryType::HousingExteriorPlacedItems   ||
         type == InventoryType::HousingInteriorPlacedItems1 ||
         type == InventoryType::HousingInteriorPlacedItems2 ||
         type == InventoryType::HousingInteriorPlacedItems3 ||
         type == InventoryType::HousingInteriorPlacedItems4 ||
         type == InventoryType::HousingInteriorPlacedItems5 ||
         type == InventoryType::HousingInteriorPlacedItems6;
}