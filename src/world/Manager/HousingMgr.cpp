#include "HousingMgr.h"
#include <Logging/Logger.h>
#include <Database/DatabaseDef.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/PacketContainer.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketWrappers/ActorControlPacket.h>
#include <Network/PacketWrappers/ActorControlSelfPacket.h>
#include <Network/CommonActorControl.h>

#include <unordered_map>
#include <cstring>
#include <Service.h>

#include "Actor/Player.h"
#include "Actor/EventObject.h"
#include "Event/EventDefs.h"

#include "TerritoryMgr.h"
#include "Territory/Territory.h"
#include "Territory/HousingZone.h"
#include "Territory/Housing/HousingInteriorTerritory.h"
#include "HousingMgr.h"
#include "Territory/Land.h"
#include "ServerMgr.h"
#include "Territory/House.h"
#include "InventoryMgr.h"
#include "Inventory/HousingItem.h"
#include "Inventory/ItemContainer.h"
#include "Util/UtilMath.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

Sapphire::World::Manager::HousingMgr::HousingMgr()
{
  m_containerMap[ 0 ] = std::make_pair( InventoryType::HousingInteriorPlacedItems1, InventoryType::HousingInteriorStoreroom1 );
  m_containerMap[ 1 ] = std::make_pair( InventoryType::HousingInteriorPlacedItems2, InventoryType::HousingInteriorStoreroom2 );
  m_containerMap[ 2 ] = std::make_pair( InventoryType::HousingInteriorPlacedItems3, InventoryType::HousingInteriorStoreroom3 );
  m_containerMap[ 3 ] = std::make_pair( InventoryType::HousingInteriorPlacedItems4, InventoryType::HousingInteriorStoreroom4 );
  m_containerMap[ 4 ] = std::make_pair( InventoryType::HousingInteriorPlacedItems5, InventoryType::HousingInteriorStoreroom5 );
  m_containerMap[ 5 ] = std::make_pair( InventoryType::HousingInteriorPlacedItems6, InventoryType::HousingInteriorStoreroom6 );
  m_containerMap[ 6 ] = std::make_pair( InventoryType::HousingInteriorPlacedItems7, InventoryType::HousingInteriorStoreroom7 );
  m_containerMap[ 7 ] = std::make_pair( InventoryType::HousingInteriorPlacedItems8, InventoryType::HousingInteriorStoreroom8 );

  m_internalPlacedItemContainers =
  {
    InventoryType::HousingInteriorPlacedItems1,
    InventoryType::HousingInteriorPlacedItems2,
    InventoryType::HousingInteriorPlacedItems3,
    InventoryType::HousingInteriorPlacedItems4,
    InventoryType::HousingInteriorPlacedItems5,
    InventoryType::HousingInteriorPlacedItems6,
    InventoryType::HousingInteriorPlacedItems7,
    InventoryType::HousingInteriorPlacedItems8,
  };

  m_internalStoreroomContainers =
  {
    InventoryType::HousingInteriorStoreroom1,
    InventoryType::HousingInteriorStoreroom2,
    InventoryType::HousingInteriorStoreroom3,
    InventoryType::HousingInteriorStoreroom4,
    InventoryType::HousingInteriorStoreroom5,
    InventoryType::HousingInteriorStoreroom6,
    InventoryType::HousingInteriorStoreroom7,
    InventoryType::HousingInteriorStoreroom8,
  };
}

Sapphire::World::Manager::HousingMgr::~HousingMgr() = default;

bool Sapphire::World::Manager::HousingMgr::init()
{
  Logger::info( "HousingMgr: Caching housing land init data" );
  //LAND_SEL_ALL

  // 18 wards per territory, 4 territories
  m_landCache.reserve( 18 * 4 );

  initLandCache();

  Logger::debug( "HousingMgr: Checking land counts" );

  uint32_t houseCount = 0;
  for( auto& landSet : m_landCache )
  {
    auto count = landSet.second.size();

    houseCount += count;

    if( landSet.second.size() != 60 )
    {
      Logger::fatal( "LandSet {0} is missing land entries. Only have {1} land entries.", landSet.first, count );
      return false;
    }
  }

  Logger::info( "HousingMgr: Cached {0} houses", houseCount );

  /////

  if( !loadEstateInventories() )
    return false;

  return true;
}

bool Sapphire::World::Manager::HousingMgr::loadEstateInventories()
{
  Logger::info( "HousingMgr: Loading inventories for estates" );

  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();

  auto stmt = db.getPreparedStatement( Db::LAND_INV_SEL_ALL );
  auto res = db.query( stmt );

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
    if( container == estateInv.end() )
    {
      Logger::warn( "Skipping item#{0} for ident#{1} - container#{2} doesn't exist for estate.",
                    itemId, ident, containerId );

      continue;
    }

    container->second->setItem( static_cast< uint8_t >( slot ), item );

    itemCount++;
  }

  Logger::debug( "HousingMgr: Loaded {0} inventory items", itemCount );

  return true;
}

void Sapphire::World::Manager::HousingMgr::initLandCache()
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();

  auto stmt = db.getPreparedStatement( Db::LAND_SEL_ALL );
  auto res = db.query( stmt );

  while( res->next() )
  {
    LandCacheEntry entry;

    // land stuff
    entry.m_landSetId = res->getUInt64( "LandSetId" );
    entry.m_landId = static_cast< uint16_t >( res->getUInt( "LandId" ) );

    entry.m_type = static_cast< Common::LandType >( res->getUInt( "Type" ) );
    entry.m_size = static_cast< Common::HouseSize >( res->getUInt8( "Size" ) );
    entry.m_status = static_cast< Common::HouseStatus >( res->getUInt8( "Status" ) );
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
    entry.m_hasAetheryte = res->getBoolean( "Aetheryte" );

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
        Logger::error( "HousingMgr: Plot {0} in landset {1} has an invalid land size, defaulting to cottage.",
                       entry.m_landId, entry.m_landSetId );
        entry.m_maxPlacedExternalItems = 20;
        entry.m_maxPlacedInternalItems = 200;
        break;
    }

    // setup containers
    // todo: this is pretty garbage
    Common::LandIdent ident;
    ident.territoryTypeId = static_cast< int16_t >( entry.m_landSetId >> 16 );
    ident.wardNum = static_cast< int16_t >( entry.m_landSetId & 0xFFFF );
    ident.landId = static_cast< int16_t >( entry.m_landId );
    ident.worldId = 67;

    auto& containers = getEstateInventory( ident );

    auto makeContainer = [ &containers, this ]( Common::InventoryType type, uint16_t size )
    {
      containers[ type ] = make_ItemContainer( type, size, "houseiteminventory", false, false );
    };

    uint16_t count = 0;
    for( int i = 0; i < 8; ++i )
    {
      if( count > entry.m_maxPlacedInternalItems )
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
    makeContainer( InventoryType::HousingExteriorAppearance, 9 );

  }
}

uint64_t Sapphire::World::Manager::HousingMgr::getNextHouseId()
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto pQR = db.query( "SELECT MAX( HouseId ) FROM house" );

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
  auto& terriMgr = Common::Service< TerritoryMgr >::ref();
  return std::dynamic_pointer_cast< HousingZone >( terriMgr.getZoneByLandSetId( id ) );
}

Sapphire::LandPtr Sapphire::World::Manager::HousingMgr::getLandByOwnerId( uint32_t id )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto res = db.query( "SELECT LandSetId, LandId FROM land WHERE OwnerId = " + std::to_string( id ) );

  if( !res->next() )
    return nullptr;

  auto hZone = getHousingZoneByLandSetId( res->getUInt( 1 ) );

  if( !hZone )
    return nullptr;

  return hZone->getLand( static_cast< uint8_t >( res->getUInt( 2 ) ) );
}

void Sapphire::World::Manager::HousingMgr::sendLandSignOwned( Entity::Player& player, const Common::LandIdent ident )
{
  auto& serverMgr = Common::Service< World::ServerMgr >::ref();

  player.setActiveLand( static_cast< uint8_t >( ident.landId ), static_cast< uint8_t >( ident.wardNum ) );

  auto landSetId = toLandSetId( static_cast< uint16_t >( ident.territoryTypeId ), static_cast< uint8_t >( ident.wardNum ) );
  auto hZone = getHousingZoneByLandSetId( landSetId );

  if( !hZone )
    return;

  auto land = hZone->getLand( static_cast< uint8_t >( ident.landId ) );
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

  uint32_t playerId = static_cast< uint32_t >( land->getOwnerId() );

  std::string playerName = serverMgr.getPlayerNameFromDb( playerId );

  memcpy( &landInfoSignPacket->data().ownerName, playerName.c_str(), playerName.size() );

  player.queuePacket( landInfoSignPacket );
}

void Sapphire::World::Manager::HousingMgr::sendLandSignFree( Entity::Player& player, const Common::LandIdent ident )
{
  player.setActiveLand( static_cast< uint8_t >( ident.landId ), static_cast< uint8_t >( ident.wardNum ) );

  auto landSetId = toLandSetId( static_cast< uint16_t >( ident.territoryTypeId ), static_cast< uint8_t >( ident.wardNum ) );
  auto hZone = getHousingZoneByLandSetId( landSetId );

  if( !hZone )
    return;

  auto land = hZone->getLand( static_cast< uint8_t >( ident.landId ) );
  auto plotPricePacket = makeZonePacket< Server::FFXIVIpcLandPriceUpdate >( player.getId() );
  plotPricePacket->data().price = land->getCurrentPrice();
  plotPricePacket->data().timeLeft = land->getDevaluationTime();
  player.queuePacket( plotPricePacket );
}

Sapphire::LandPurchaseResult Sapphire::World::Manager::HousingMgr::purchaseLand( Entity::Player& player, uint8_t plot, uint8_t state )
{
  auto pHousing = std::dynamic_pointer_cast< HousingZone >( player.getCurrentTerritory() );

  auto plotPrice = pHousing->getLand( plot )->getCurrentPrice();
  auto gilAvailable = player.getCurrency( CurrencyType::Gil );
  auto pLand = pHousing->getLand( plot );

  if( !pLand )
    return LandPurchaseResult::ERR_INTERNAL;

  if( pLand->getStatus() != HouseStatus::ForSale )
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
      pLand->setStatus( HouseStatus::Sold );
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
  auto pHousing = std::dynamic_pointer_cast< HousingZone >( player.getCurrentTerritory() );

  auto pLand = pHousing->getLand( plot );
  auto plotMaxPrice = pLand->getCurrentPrice();

  // can't relinquish when you are not the owner
  // TODO: actually use permissions here for FC houses
  if( !hasPermission( player, *pLand, 0 ) )
  {
    auto msgPkt = makeActorControlSelf( player.getId(), ActorControl::LogMsg, 3304, 0 );
    player.queuePacket( msgPkt );
    return false;
  }

  // unable to relinquish if there is a house built
  // TODO: additionally check for yard items
  if( pLand->getHouse() )
  {
    auto msgPkt = makeActorControlSelf( player.getId(), ActorControl::LogMsg, 3315, 0 );
    player.queuePacket( msgPkt );
    return false;
  }

  pLand->setCurrentPrice( pLand->getMaxPrice() );
  pLand->setOwnerId( 0 );
  pLand->setStatus( HouseStatus::ForSale );
  pLand->setLandType( Common::LandType::none );
  pLand->updateLandDb();

  Common::LandIdent ident { 0xFF, 0xFF, 0xFF, 0xFF };

  player.setLandFlags( LandFlagsSlot::Private, 0x00, ident );

  player.sendLandFlagsSlot( LandFlagsSlot::Private );

  auto screenMsgPkt2 = makeActorControlSelf( player.getId(), ActorControl::LogMsg, 3351, 0x1AA,
                                             pLand->getLandIdent().wardNum + 1, plot + 1 );
  player.queuePacket( screenMsgPkt2 );
  pHousing->sendLandUpdate( plot );

  return true;
}

void Sapphire::World::Manager::HousingMgr::sendWardLandInfo( Entity::Player& player, uint8_t wardId, uint16_t territoryTypeId )
{
  auto& serverMgr = Common::Service< World::ServerMgr >::ref();

  auto landSetId = toLandSetId( territoryTypeId, wardId );
  auto hZone = getHousingZoneByLandSetId( landSetId );

  if( !hZone )
    return;

  auto wardInfoPacket = makeZonePacket< Server::FFXIVIpcHousingWardInfo >( player.getId() );
  wardInfoPacket->data().landIdent.wardNum = wardId;
  wardInfoPacket->data().landIdent.territoryTypeId = static_cast< int16_t >( territoryTypeId );

  // todo: properly get worldId
  wardInfoPacket->data().landIdent.worldId = 67;

  for( int i = 0; i < 60; i++ )
  {
    auto land = hZone->getLand( i );
    assert( land );

    auto& entry = wardInfoPacket->data().houseInfoEntry[ i ];

    // retail always sends the house price in this packet, even after the house has been Sold
    // so I guess we do the same
    entry.housePrice = land->getCurrentPrice();

    if( land->getStatus() == Common::HouseStatus::ForSale )
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
        auto playerName = serverMgr.getPlayerNameFromDb( static_cast< uint32_t >( owner ) );
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
  auto landSetId = toLandSetId( static_cast< uint16_t >( ident.territoryTypeId ), static_cast< uint8_t >( ident.wardNum ) );
  auto hZone = getHousingZoneByLandSetId( landSetId );

  if( !hZone )
    return;

  auto land = hZone->getLand( static_cast< uint8_t >( ident.landId ) );
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

  auto& exdData = Common::Service< Sapphire::Data::ExdDataGenerated >::ref();
  auto preset = exdData.get< Sapphire::Data::HousingPreset >( getItemAdditionalData( presetCatalogId ) );
  if( !preset )
    return false;

  // remove preset item
  Inventory::InventoryContainerPair foundItem;
  if( !player.findFirstItemWithId( presetCatalogId, foundItem ) )
    return false;

  auto item = getHousingItemFromPlayer( player, foundItem.first, foundItem.second );
  if( !item )
    return false;

  // move preset item into ext appearance container
  houseInventory[ InventoryType::HousingExteriorAppearance ]->setItem( HouseExteriorSlot::HousePermit, item );

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
        { HouseInteriorSlot::InteriorWall, preset->interiorWall },
        { HouseInteriorSlot::InteriorFloor, preset->interiorFlooring },
        { HouseInteriorSlot::InteriorLight, preset->interiorLighting },

        // attic
        { HouseInteriorSlot::InteriorWall_Attic, preset->otherFloorWall },
        { HouseInteriorSlot::InteriorFloor_Attic, preset->otherFloorFlooring },
        { HouseInteriorSlot::InteriorLight_Attic, preset->otherFloorLighting },

        // basement
        { HouseInteriorSlot::InteriorWall_Basement, preset->basementWall },
        { HouseInteriorSlot::InteriorFloor_Basement, preset->basementFlooring },
        { HouseInteriorSlot::InteriorLight_Basement, preset->basementLighting },
      }
    }
  };

  auto& invMgr = Service< InventoryMgr >::ref();

  // create and link items
  for( auto& destContainer : invMap )
  {
    auto& container = houseInventory[ destContainer.first ];

    for( auto& item : destContainer.second )
    {
      // small houses attic is just 0, ignore them
      if( item.second == 0 )
        continue;

      auto pItem = invMgr.createItem( player, static_cast< uint32_t >( item.second ) );

      container->setItem( static_cast< uint8_t >( item.first ), pItem );
    }

    invMgr.saveHousingContainer( land->getLandIdent(), container );
  }

  // lift off
  updateHouseModels( house );

  return true;
}

void Sapphire::World::Manager::HousingMgr::createHouse( Sapphire::HousePtr house ) const
{
  auto& db = Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();

  auto stmt = db.getPreparedStatement( Db::HOUSING_HOUSE_INS );
  // LandSetId, HouseId, HouseName

  stmt->setUInt( 1, house->getLandSetId() );
  stmt->setUInt( 2, house->getId() );
  stmt->setString( 3, house->getHouseName() );

  db.execute( stmt );
}

void Sapphire::World::Manager::HousingMgr::deleteHouse( Sapphire::HousePtr house ) const
{
  auto& db = Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto stmt = db.getPreparedStatement( Db::HOUSING_HOUSE_DEL );
  stmt->setUInt( 1, house->getId() );
  db.execute( stmt );
}

void Sapphire::World::Manager::HousingMgr::buildPresetEstate( Entity::Player& player, uint8_t plotNum, uint32_t presetCatalogId )
{
  auto hZone = std::dynamic_pointer_cast< HousingZone >( player.getCurrentTerritory() );

  if( !hZone )
    return;

  auto pLand = hZone->getLand( plotNum );
  if( !pLand )
    return;

  if( !hasPermission( player, *pLand, 0 ) )
    return;

  // create house
  auto ident = pLand->getLandIdent();
  auto house = make_House( getNextHouseId(), pLand->getLandSetId(), ident,
                           "Estate #" + std::to_string( ident.landId + 1 ), "" );

  pLand->setHouse( house );

  // create inventory items
  if( !initHouseModels( player, pLand, presetCatalogId ) )
  {
    pLand->setHouse( nullptr );
    return;
  }

  createHouse( house );

  pLand->setStatus( HouseStatus::PrivateEstate );
  pLand->setLandType( LandType::Private );
  hZone->sendLandUpdate( plotNum );

  auto pSuccessBuildingPacket = makeActorControl( player.getId(), ActorControl::BuildPresetResponse, plotNum );

  player.queuePacket( pSuccessBuildingPacket );

  pLand->updateLandDb();

  // start house built event
  // CmnDefHousingBuildHouse_00149
  player.eventStart( player.getId(), 0x000B0095, Event::EventHandler::EventType::Housing, 1, 1 );
  player.playScene( 0x000B0095, 0, static_cast< uint32_t >( SET_BASE | HIDE_HOTBAR ) , 0, 1, plotNum, nullptr );

  player.setLandFlags( LandFlagsSlot::Private, EstateBuilt, ident );
  player.sendLandFlagsSlot( LandFlagsSlot::Private );

  hZone->registerEstateEntranceEObj( plotNum );
}

void Sapphire::World::Manager::HousingMgr::requestEstateRename( Entity::Player& player, const Common::LandIdent ident )
{
  auto landSetId = toLandSetId( static_cast< uint16_t >( ident.territoryTypeId ), static_cast< uint8_t >( ident.wardNum ) );
  auto hZone = getHousingZoneByLandSetId( landSetId );

  if( !hZone )
    return;

  auto land = hZone->getLand( static_cast< uint8_t >( ident.landId ) );

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
  auto landSetId = toLandSetId( static_cast< uint16_t >( ident.territoryTypeId ), static_cast< uint8_t >( ident.wardNum ) );
  auto hZone = getHousingZoneByLandSetId( landSetId );

  if( !hZone )
    return;

  auto land = hZone->getLand( static_cast< uint8_t >( ident.landId ) );
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
  auto landSetId = toLandSetId( static_cast< uint16_t >( ident.territoryTypeId ), static_cast< uint8_t >( ident.wardNum ) );
  auto zone = getHousingZoneByLandSetId( landSetId );

  if( !zone )
    return;

  auto land = zone->getLand( static_cast< uint8_t >( ident.landId ) );
  if( !land )
    return;

  if( !hasPermission( player, *land, 0 ) )
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
  auto landSetId = toLandSetId( static_cast< uint16_t >( ident.territoryTypeId ), static_cast< uint8_t >( ident.wardNum ) );
  auto hZone = getHousingZoneByLandSetId( landSetId );

  if( !hZone )
    return;

  auto land = hZone->getLand( ident.landId );
  if( !land )
    return;

  if( !hasPermission( player, *land, 0 ) )
    return;

  auto packet = makeZonePacket< Server::FFXIVIpcHousingShowEstateGuestAccess >( player.getId() );
  packet->data().ident = ident;

  player.queuePacket( packet );
}

Sapphire::Common::LandIdent Sapphire::World::Manager::HousingMgr::clientTriggerParamsToLandIdent( uint32_t param11, uint32_t param12, bool use16bits ) const
{
  Common::LandIdent ident;
  ident.worldId = static_cast< int16_t >( param11 >> 16 );
  ident.territoryTypeId = static_cast< int16_t >( param11 & 0xFFFF );

  if( use16bits )
  {
    ident.wardNum = static_cast< int16_t >( param12 >> 16 );
    ident.landId = static_cast< int16_t >( param12 & 0xFFFF );
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
    auto internalZone = std::dynamic_pointer_cast< Territory::Housing::HousingInteriorTerritory >(
      player.getCurrentTerritory() );
    if( !internalZone )
      return;

    auto ident = internalZone->getLandIdent();

    auto landSetId = toLandSetId( static_cast< uint16_t >( ident.territoryTypeId ), static_cast< uint8_t >( ident.wardNum ) );
    auto exteriorZone = getHousingZoneByLandSetId( landSetId );

    if( !exteriorZone )
      return;

    targetLand = exteriorZone->getLand( static_cast< uint8_t >( ident.landId ) );
  }
  else
  {
    auto zone = std::dynamic_pointer_cast< HousingZone >( player.getCurrentTerritory() );
    if( !zone )
      return;

    targetLand = zone->getLand( plotNum );
  }

  if( !targetLand )
    return;

  if( !hasPermission( player, *targetLand, 0 ) )
    return;

  auto& containers = getEstateInventory( targetLand->getLandIdent() );
  auto it = containers.find( inventoryType );
  if( it == containers.end() )
    return;

  auto& invMgr = Common::Service< Manager::InventoryMgr >::ref();
  invMgr.sendInventoryContainer( player, it->second );
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

  house->clearModelCache();

  auto& containers = getEstateInventory( house->getLandIdent() );

  auto extContainer = containers.find( static_cast< uint16_t >( InventoryType::HousingExteriorAppearance ) );
  if( extContainer != containers.end() )
  {
    for( auto& item : extContainer->second->getItemMap() )
    {
      // in the Slot array, the first slot is actually the permit
      // but the models array starts from the 2nd entry of the enum
      // so we skip the first one, and then any subsequent entries is slotid - 1

      auto slotId = item.first - 1;
      if( slotId < 0 )
        continue;

      house->setExteriorModel( static_cast< Common::HouseExteriorSlot >( slotId ),
                               getItemAdditionalData( item.second->getId() ), item.second->getStain() );
    }
  }
  else
  {
    Logger::error( "Plot {0} has an invalid inventory configuration for outdoor appearance.", house->getLandIdent().landId );
  }

  auto intContainer = containers.find( static_cast< uint16_t >( InventoryType::HousingInteriorAppearance ) );
  if( intContainer != containers.end() )
  {
    for( auto& item : intContainer->second->getItemMap() )
    {
      house->setInteriorModel( static_cast< Common::HouseInteriorSlot >( item.first ),
                               getItemAdditionalData( item.second->getId() ) );
    }
  }
  else
  {
    Logger::error( "Plot {0} has an invalid inventory configuration for indoor appearance.", house->getLandIdent().landId );
  }
}

uint32_t Sapphire::World::Manager::HousingMgr::getItemAdditionalData( uint32_t catalogId )
{
  auto& pExdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto info = pExdData.get< Sapphire::Data::Item >( catalogId );
  return info->additionalData;
}

bool Sapphire::World::Manager::HousingMgr::isPlacedItemsInventory( Sapphire::Common::InventoryType type )
{
  return type == InventoryType::HousingExteriorPlacedItems  ||
         type == InventoryType::HousingInteriorPlacedItems1 ||
         type == InventoryType::HousingInteriorPlacedItems2 ||
         type == InventoryType::HousingInteriorPlacedItems3 ||
         type == InventoryType::HousingInteriorPlacedItems4 ||
         type == InventoryType::HousingInteriorPlacedItems5 ||
         type == InventoryType::HousingInteriorPlacedItems6;
}

void Sapphire::World::Manager::HousingMgr::reqPlaceHousingItem( Sapphire::Entity::Player& player, uint16_t landId,
                                                                uint16_t containerId, uint8_t slotId,
                                                                Sapphire::Common::FFXIVARR_POSITION3 pos,
                                                                float rotation )
{
  // retail process is:
  //  - unlink item from current container
  //  - add it to destination container
  //  - resend container
  //  - send spawn packet
  //  - send actrl 3f3, all params are 0

  LandPtr land;
  bool isOutside = false;

  // inside housing territory
  if( auto zone = std::dynamic_pointer_cast< HousingZone >( player.getCurrentTerritory() ) )
  {
    land = zone->getLand( static_cast< uint8_t >( landId ) );

    isOutside = true;
  }
  // otherwise, inside a house. landId is 0 when inside a plot
  else if( auto zone = std::dynamic_pointer_cast< Territory::Housing::HousingInteriorTerritory >(
    player.getCurrentTerritory() ) )
  {
    // todo: this whole process is retarded and needs to be fixed
    // perhaps maintain a list of estates by ident inside housingmgr?
    auto ident = zone->getLandIdent();
    auto landSet = toLandSetId( static_cast< uint16_t >( ident.territoryTypeId ), static_cast< uint8_t >( ident.wardNum ) );

    land = getHousingZoneByLandSetId( landSet )->getLand( static_cast< uint8_t >( ident.landId ) );
  }
  // wtf?
  else
    return;

  if( !land )
    return;

  if( !hasPermission( player, *land, 0 ) )
    return;

  // todo: check item position and make sure it's not outside the plot
  // anecdotal evidence on reddit seems to imply retail uses a radius based check

  // unlink item
  Inventory::HousingItemPtr item;

  if( containerId == InventoryType::Bag0 ||
      containerId == InventoryType::Bag1 ||
      containerId == InventoryType::Bag2 ||
      containerId == InventoryType::Bag3 )
  {
    item = getHousingItemFromPlayer( player, static_cast< Common::InventoryType >( containerId ), slotId );
    if( !item )
      return;

    // set params
    item->setPos( pos );
    item->setRot( rotation );
  }
  else
  {
    player.sendUrgent( "The inventory you are using to place an item is not supported." );
    return;
  }

  auto ident = land->getLandIdent();

  bool status = false;

  if( isOutside )
    status = placeExternalItem( player, item, ident );
  else
    status = placeInteriorItem( player, item );

  if( status )
    player.queuePacket( Server::makeActorControlSelf( player.getId(), 0x3f3 ) );
  else
    player.sendUrgent( "An internal error occurred when placing the item." );
}

void Sapphire::World::Manager::HousingMgr::reqPlaceItemInStore( Sapphire::Entity::Player& player, uint16_t landId,
                                                                uint16_t containerId, uint8_t slotId )
{
  LandPtr land;
  bool isOutside = false;

  if( auto zone = std::dynamic_pointer_cast< HousingZone >( player.getCurrentTerritory() ) )
  {
    land = zone->getLand( static_cast< uint8_t >( landId ) );
    isOutside = true;
  }
  else if( auto zone = std::dynamic_pointer_cast< Territory::Housing::HousingInteriorTerritory >(
    player.getCurrentTerritory() ) )
  {
    // todo: this whole process is retarded and needs to be fixed
    // perhaps maintain a list of estates by ident inside housingmgr?
    auto ident = zone->getLandIdent();
    auto landSet = toLandSetId( static_cast< uint16_t >( ident.territoryTypeId ), static_cast< uint8_t >( ident.wardNum ) );

    land = getHousingZoneByLandSetId( landSet )->getLand( static_cast< uint8_t >( ident.landId ) );
  }

  if( !hasPermission( player, *land, 0 ) )
    return;

  auto& invMgr = Common::Service< InventoryMgr >::ref();
  auto ident = land->getLandIdent();
  auto& containers = getEstateInventory( ident );

  if( isOutside )
  {
    auto& container = containers[ InventoryType::HousingExteriorStoreroom ];

    auto freeSlot = container->getFreeSlot();
    if( freeSlot == -1 )
      return;

    auto item = getHousingItemFromPlayer( player, static_cast< Common::InventoryType >( containerId ), slotId );
    if( !item )
      return;

    container->setItem( static_cast< uint8_t >( freeSlot ), item );
    invMgr.sendInventoryContainer( player, container );
    invMgr.saveHousingContainer( ident, container );
  }
  else
  {
    for( auto houseContainer : m_internalStoreroomContainers )
    {
      auto it = containers.find( houseContainer );
      if( it == containers.end() )
        continue;

      auto container = it->second;
      auto freeSlot = container->getFreeSlot();
      if( freeSlot == -1 )
      {
        continue;
      }

      auto item = getHousingItemFromPlayer( player, static_cast< Common::InventoryType >( containerId ), slotId );
      if( !item )
        return;

      container->setItem( static_cast< uint8_t >( freeSlot ), item );
      invMgr.sendInventoryContainer( player, container );
      invMgr.saveHousingContainer( ident, container );
    }
  }
}

bool Sapphire::World::Manager::HousingMgr::placeExternalItem( Entity::Player& player,
                                                              Inventory::HousingItemPtr item,
                                                              Common::LandIdent ident )
{
  auto& invMgr = Service< InventoryMgr >::ref();

  auto& container = getEstateInventory( ident )[ InventoryType::HousingExteriorPlacedItems ];

  auto freeSlot = container->getFreeSlot();

  // todo: what happens when this fails? at the moment the player will just lose the item
  if( freeSlot == -1 )
    return false;

  // add item to inv
  container->setItem( static_cast< uint8_t >( freeSlot ), item );

  // we need to save the item again as removing it from the container on the player will remove it from charaglobalitem
  // todo: this needs to be handled a bit better as it might be possible to overwrite another item that is created in the meantime
  invMgr.saveItem( player, item );

  invMgr.sendInventoryContainer( player, container );
  invMgr.saveHousingContainer( ident, container );
  invMgr.updateHousingItemPosition( item );

  // add to zone and spawn
  auto zone = std::dynamic_pointer_cast< HousingZone >( player.getCurrentTerritory() );
  assert( zone );

  zone->spawnYardObject( static_cast< uint8_t >( ident.landId ), static_cast< uint16_t >( freeSlot ), *item );

  return true;
}

bool Sapphire::World::Manager::HousingMgr::placeInteriorItem( Entity::Player& player,
                                                              Inventory::HousingItemPtr item )
{
  auto& invMgr = Service< InventoryMgr >::ref();

  auto zone = std::dynamic_pointer_cast< Territory::Housing::HousingInteriorTerritory >( player.getCurrentTerritory() );
  assert( zone );

  auto ident = zone->getLandIdent();

  auto& containers = getEstateInventory( ident );

  // find first free container
  uint8_t containerIdx = 0;
  for( auto containerId : m_internalPlacedItemContainers )
  {
    auto it = containers.find( containerId );
    if( it == containers.end() )
      continue;

    auto container = it->second;
    auto freeSlot = container->getFreeSlot();
    if( freeSlot == -1 )
    {
      containerIdx++;
      continue;
    }

    // have a free slot
    container->setItem( static_cast< uint8_t >( freeSlot ), item );

    // resend container
    invMgr.sendInventoryContainer( player, container );
    invMgr.saveHousingContainer( ident, container );
    invMgr.updateHousingItemPosition( item );

    auto zone = std::dynamic_pointer_cast< Territory::Housing::HousingInteriorTerritory >( player.getCurrentTerritory() );
    assert( zone );

    zone->spawnHousingObject( containerIdx, static_cast< uint16_t >( freeSlot ), containerId, item );

    return true;
  }

  return false;
}

Sapphire::Common::HousingObject Sapphire::World::Manager::HousingMgr::getYardObjectForItem( Inventory::HousingItemPtr item ) const
{
  Sapphire::Common::HousingObject obj {};

  obj.pos = item->getPos();
  obj.rotation = item->getRot();
  obj.itemId = item->getAdditionalData();

  return obj;
}

void Sapphire::World::Manager::HousingMgr::sendInternalEstateInventoryBatch( Sapphire::Entity::Player& player,
                                                                             bool storeroom )
{
  auto zone = std::dynamic_pointer_cast< Territory::Housing::HousingInteriorTerritory >( player.getCurrentTerritory() );
  if( !zone )
    return;

  // todo: perms check

  Inventory::InventoryTypeList containerIds;

  if( storeroom )
    containerIds = m_internalStoreroomContainers;
  else
    containerIds = m_internalPlacedItemContainers;

  auto& invMgr = Service< InventoryMgr >::ref();
  auto& containers = getEstateInventory( zone->getLandIdent() );

  for( auto containerId : containerIds )
  {
    auto container = containers.find( containerId );
    if( container == containers.end() )
      break;

    invMgr.sendInventoryContainer( player, container->second );
  }
}

void Sapphire::World::Manager::HousingMgr::reqMoveHousingItem( Entity::Player& player,
                                                               Common::LandIdent ident, uint8_t slot,
                                                               Common::FFXIVARR_POSITION3 pos, float rot )
{
  auto landSet = toLandSetId( static_cast< uint16_t >( ident.territoryTypeId ), static_cast< uint8_t >( ident.wardNum ) );
  auto land = getHousingZoneByLandSetId( landSet )->getLand( static_cast< uint8_t >( ident.landId ) );

  if( !land )
    return;

  if( !hasPermission( player, *land, 0 ) )
    return;

  // todo: what happens when either of these fail? how does the server let the client know that the moment failed
  // as is, if it does fail, the client will be locked and unable to move any item until reentering the territory
  if( auto terri = std::dynamic_pointer_cast< Territory::Housing::HousingInteriorTerritory >(
    player.getCurrentTerritory() ) )
  {
    moveInternalItem( player, ident, *terri, slot, pos, rot );
  }
  else if( auto terri = std::dynamic_pointer_cast< HousingZone >( player.getCurrentTerritory() ) )
  {
    moveExternalItem( player, ident, slot, *terri, pos, rot );
  }
}

bool Sapphire::World::Manager::HousingMgr::moveInternalItem( Entity::Player& player, Common::LandIdent ident,
                                                             Territory::Housing::HousingInteriorTerritory& terri, uint8_t slot,
                                                             Common::FFXIVARR_POSITION3 pos, float rot )
{
  auto containerIdx = static_cast< uint16_t >( slot / 50 );
  auto slotIdx = slot % 50;

  uint16_t containerId = 0;
  try
  {
    containerId = m_internalPlacedItemContainers.at( containerIdx );
  }
  catch( const std::out_of_range& ex )
  {
    return false;
  }

  auto& containers = getEstateInventory( ident );

  auto it = containers.find( containerId );
  if( it == containers.end() )
    return false;

  auto container = it->second;

  auto item = std::dynamic_pointer_cast< Inventory::HousingItem >( container->getItem( static_cast< uint8_t >( slotIdx ) ) );
  if( !item )
    return false;

  item->setPos( pos );
  item->setRot( rot );

  // save
  auto& invMgr = Service< InventoryMgr >::ref();
  invMgr.updateHousingItemPosition( item );

  terri.updateHousingObjectPosition( player, slot, item->getPos(), static_cast< uint16_t >( item->getRot() ) );

  // send confirmation to player
  uint32_t param1 = static_cast< uint32_t >( ( ident.landId << 16 ) | containerId );

  player.queuePacket(
    Server::makeActorControlSelf( player.getId(), ActorControl::HousingItemMoveConfirm, param1, slotIdx ) );

  return true;
}

bool Sapphire::World::Manager::HousingMgr::moveExternalItem( Entity::Player& player,
                                                             Common::LandIdent ident, uint8_t slot,
                                                             Sapphire::HousingZone& terri, Common::FFXIVARR_POSITION3 pos,
                                                             float rot )
{
  auto land = terri.getLand( static_cast< uint8_t >( ident.landId ) );

  if( !hasPermission( player, *land, 0 ) )
    return false;

  auto& containers = getEstateInventory( ident );
  auto it = containers.find( InventoryType::HousingExteriorPlacedItems );
  if( it == containers.end() )
    return false;

  auto container = it->second;

  auto item = std::dynamic_pointer_cast< Inventory::HousingItem >( container->getItem( slot ) );
  if( !item )
    return false;

  item->setPos( pos );
  item->setRot( rot );

  auto& invMgr = Service< InventoryMgr >::ref();
  invMgr.updateHousingItemPosition( item );

  terri.updateYardObjectPos( player, slot, static_cast< uint16_t >( ident.landId ), *item );

  uint32_t param1 = static_cast< uint32_t >( ( ident.landId << 16 ) | InventoryType::HousingExteriorPlacedItems );
  player.queuePacket( Server::makeActorControlSelf( player.getId(), ActorControl::HousingItemMoveConfirm, param1, slot ) );


  return true;
}

void Sapphire::World::Manager::HousingMgr::reqRemoveHousingItem( Sapphire::Entity::Player& player, uint16_t plot,
                                                                 uint16_t containerId, uint8_t slot,
                                                                 bool sendToStoreroom )
{
  if( auto terri = std::dynamic_pointer_cast< Territory::Housing::HousingInteriorTerritory >(
    player.getCurrentTerritory() ) )
  {
    auto ident = terri->getLandIdent();
    auto landSet = toLandSetId( static_cast< uint16_t >( ident.territoryTypeId ), static_cast< uint8_t >( ident.wardNum ) );
    auto land = getHousingZoneByLandSetId( landSet )->getLand( static_cast< uint8_t >( ident.landId ) );

    if( !land )
      return;

    if( !hasPermission( player, *land, 0 ) )
      return;

    removeInternalItem( player, *terri, containerId, slot, sendToStoreroom );
  }
  else if( auto terri = std::dynamic_pointer_cast< HousingZone >( player.getCurrentTerritory() ) )
  {
    auto land = terri->getLand( static_cast< uint8_t >( plot ) );
    if( !land )
      return;

    if( !hasPermission( player, *land, 0 ) )
      return;

    auto containerType = static_cast< Common::InventoryType >( containerId );

    removeExternalItem( player, *terri, *land, containerType, slot, sendToStoreroom );
  }
}

bool Sapphire::World::Manager::HousingMgr::removeInternalItem( Entity::Player& player,
                                                               Territory::Housing::HousingInteriorTerritory& terri,
                                                               uint16_t containerId, uint16_t slotId,
                                                               bool sendToStoreroom )
{
  auto& containers = getEstateInventory( terri.getLandIdent() );

  int8_t containerIdx = 0;

  if( isPlacedItemsInventory( static_cast< Common::InventoryType >( containerId ) ) )
  {
    for( auto cId : m_internalPlacedItemContainers )
    {
      if( containerId == cId )
        break;

      containerIdx++;
    }
  }
  else
    containerIdx = -1;

  // its possible to remove an item from any container in basically all these remove functions
  // eg, remove a permit and reuse it elsewhere
  // I'm not going to bother fixing it for now, but worth noting for future reference

  auto it = containers.find( containerId );
  if( it == containers.end() )
    return false;

  auto container = it->second;

  auto item = std::dynamic_pointer_cast< Inventory::HousingItem >( container->getItem( static_cast< uint8_t >( slotId ) ) );
  if( !item )
    return false;

  if( !sendToStoreroom )
  {
    // make sure the player has a free inv slot first
    Inventory::InventoryContainerPair containerPair;
    if( !player.getFreeInventoryContainerSlot( containerPair ) )
      return false;

    auto& invMgr = Service< InventoryMgr >::ref();

    // remove it from housing inventory
    container->removeItem( static_cast< uint8_t >( slotId ) );
    invMgr.sendInventoryContainer( player, container );
    invMgr.removeHousingItemPosition( *item );
    invMgr.removeItemFromHousingContainer( terri.getLandIdent(), containerId, slotId );

    // add to player inv
    player.insertInventoryItem( containerPair.first, containerPair.second, item );

    // todo: set item as bound/unsellable/untradable
  }
  else
  {
    ItemContainerPtr freeContainer;
    Inventory::InventoryContainerPair freeSlotPair;
    freeContainer = getFreeEstateInventorySlot( terri.getLandIdent(), freeSlotPair, m_internalStoreroomContainers );

    if( !freeContainer )
      return false;

    auto& invMgr = Service< InventoryMgr >::ref();

    container->removeItem( static_cast< uint8_t >( slotId ) );
    invMgr.sendInventoryContainer( player, container );
    invMgr.removeHousingItemPosition( *item );
    invMgr.removeItemFromHousingContainer( terri.getLandIdent(), containerId, slotId );

    freeContainer->setItem( static_cast< uint8_t >( slotId ), item );
    invMgr.sendInventoryContainer( player, freeContainer );
    invMgr.saveHousingContainer( terri.getLandIdent(), freeContainer );
  }

  // despawn
  if( containerIdx != -1 )
  {
    auto arraySlot = ( containerIdx * 50 ) + slotId;
    terri.removeHousingObject( static_cast< uint16_t >( arraySlot ) );
  }

  return true;
}

bool Sapphire::World::Manager::HousingMgr::removeExternalItem( Entity::Player& player, HousingZone& terri, Land& land,
                                                               Common::InventoryType containerType, uint8_t slotId,
                                                               bool sendToStoreroom )
{
  auto& containers = getEstateInventory( land.getLandIdent() );

  auto it = containers.find( containerType );
  if( it == containers.end() )
    return false;

  auto& sourceContainer = it->second;

  auto item = std::dynamic_pointer_cast< Inventory::HousingItem >( sourceContainer->getItem( slotId ) );
  if( !item )
    return false;

  bool shouldDespawnItem = containerType != InventoryType::HousingExteriorStoreroom;

  auto& invMgr = Service< InventoryMgr >::ref();

  if( sendToStoreroom )
  {
    auto& storeroomContainer = containers[ containerType ];
    auto freeSlot = storeroomContainer->getFreeSlot();

    if( freeSlot == -1 )
      return false;

    sourceContainer->removeItem( slotId );
    invMgr.sendInventoryContainer( player, sourceContainer );
    invMgr.removeItemFromHousingContainer( land.getLandIdent(), sourceContainer->getId(), slotId );
    invMgr.removeHousingItemPosition( *item );

    storeroomContainer->setItem( static_cast< uint8_t >( freeSlot ), item );
    invMgr.sendInventoryContainer( player, storeroomContainer );
    invMgr.saveHousingContainer( land.getLandIdent(), storeroomContainer );
  }
  else
  {
    Inventory::InventoryContainerPair containerPair;
    if( !player.getFreeInventoryContainerSlot( containerPair ) )
      return false;

    // remove from housing inv
    sourceContainer->removeItem( slotId );
    invMgr.sendInventoryContainer( player, sourceContainer );
    invMgr.removeHousingItemPosition( *item );
    invMgr.removeItemFromHousingContainer( land.getLandIdent(), sourceContainer->getId(), slotId );

    // add to player inv
    player.insertInventoryItem( containerPair.first, containerPair.second, item );
  }

  if( shouldDespawnItem )
    terri.despawnYardObject( static_cast< uint16_t >( land.getLandIdent().landId ), slotId );

  return true;
}

Sapphire::ItemContainerPtr Sapphire::World::Manager::HousingMgr::getFreeEstateInventorySlot( Common::LandIdent ident,
                                                                                             Inventory::InventoryContainerPair& pair,
                                                                                             Inventory::InventoryTypeList bagList )
{
  auto& estateContainers = getEstateInventory( ident );

  for( auto bag : bagList )
  {
    auto it = estateContainers.find( bag );
    if( it == estateContainers.end() )
      continue;

    auto container = it->second;

    auto freeSlot = container->getFreeSlot();

    if( freeSlot == -1 )
      continue;

    pair = std::make_pair( bag, freeSlot );
    return container;
  }

  return nullptr;
}

void Sapphire::World::Manager::HousingMgr::reqEstateExteriorRemodel( Sapphire::Entity::Player& player, uint16_t plot )
{
  auto terri = std::dynamic_pointer_cast< HousingZone >( player.getCurrentTerritory() );
  if( !terri )
    return;

  auto land = terri->getLand( static_cast< uint8_t >( plot ) );
  if( !land )
    return;

  if( !hasPermission( player, *land, 0 ) )
    return;

  auto& inv = getEstateInventory( land->getLandIdent() );
  auto it = inv.find( InventoryType::HousingExteriorAppearance );
  if( it == inv.end() )
    return;

  auto& invMgr = Service< InventoryMgr >::ref();

  invMgr.sendInventoryContainer( player, it->second );

  auto pkt = Server::makeActorControlSelf( player.getId(), Network::ActorControl::ShowEstateExternalAppearanceUI, plot );
  player.queuePacket( pkt );

}

void Sapphire::World::Manager::HousingMgr::reqEstateInteriorRemodel( Sapphire::Entity::Player& player )
{
  auto terri = std::dynamic_pointer_cast< Territory::Housing::HousingInteriorTerritory >( player.getCurrentTerritory() );
  if( !terri )
    return;

  auto ident = terri->getLandIdent();
  auto landSet = toLandSetId( static_cast< uint16_t >( ident.territoryTypeId ), static_cast< uint8_t >( ident.wardNum ) );
  auto land = getHousingZoneByLandSetId( landSet )->getLand( static_cast< uint8_t >( ident.landId ) );

  if( !land )
    return;

  if( !hasPermission( player, *land, 0 ) )
    return;

  auto& inv = getEstateInventory( land->getLandIdent() );
  auto it = inv.find( InventoryType::HousingInteriorAppearance );
  if( it == inv.end() )
    return;

  auto& invMgr = Service< InventoryMgr >::ref();

  invMgr.sendInventoryContainer( player, it->second );

  auto pkt = Server::makeActorControlSelf( player.getId(), Network::ActorControl::ShowEstateInternalAppearanceUI );
  player.queuePacket( pkt );
}

bool Sapphire::World::Manager::HousingMgr::hasPermission( Sapphire::Entity::Player& player, Sapphire::Land& land,
                                                          uint32_t permission )
{
  // todo: proper perms checks pls
  if( land.getOwnerId() == player.getId() )
    return true;

  // todo: check perms here

  return false;
}

Sapphire::Inventory::HousingItemPtr Sapphire::World::Manager::HousingMgr::getHousingItemFromPlayer(
  Entity::Player& player, Common::InventoryType type, uint8_t slot )
{
  auto tmpItem = player.dropInventoryItem( type, slot );
  if( !tmpItem )
    return nullptr;

  return Inventory::make_HousingItem( tmpItem->getUId(), tmpItem->getId() );
}

void Sapphire::World::Manager::HousingMgr::editAppearance( bool isInterior, Sapphire::Entity::Player& player, const Common::LandIdent landIdent, std::vector< uint16_t > containerList, std::vector< uint8_t> slotList, uint8_t removeFlag )
{
  auto landSetId = toLandSetId( static_cast< uint16_t >( landIdent.territoryTypeId ), static_cast< uint8_t >( landIdent.wardNum ) );
  auto terri = getHousingZoneByLandSetId( landSetId );

  auto land = terri->getLand( static_cast< uint8_t >( landIdent.landId ) );
  if( !land )
    return;

  if( !hasPermission( player, *land, 0 ) )
    return;

  auto& housingContainer = getEstateInventory( landIdent )[ isInterior ? InventoryType::HousingInteriorAppearance : InventoryType::HousingExteriorAppearance ];

  auto& invMgr = Service< InventoryMgr >::ref();

  for( int i = 0; i < ( isInterior ? 10 : 9 ); i++ )
  {
    auto container = containerList.at( i );
    auto slot = slotList.at( i );
    if( container == 0x270F || slot == 0xFF )
    {
      if( i >= 5 )
      {
        auto removed = ( ( removeFlag >> ( i - 5 ) ) & 1 ) > 0;
        if( removed )
        {
          auto oldItem = housingContainer->getItem( i );
          if( oldItem )
          {
            housingContainer->removeItem( i );
            invMgr.removeItemFromHousingContainer( landIdent, housingContainer->getId(), i );
            player.addItem( oldItem, false, false, false );
          }
        }
      }
      continue;
    }
    auto item = getHousingItemFromPlayer( player, static_cast< Sapphire::Common::InventoryType >( container ), slot );
    if( item )
    {
      auto oldItem = housingContainer->getItem( i );
      housingContainer->setItem( i, item );
      if( oldItem )
      {
        player.insertInventoryItem( static_cast< Sapphire::Common::InventoryType >( container ), slot, oldItem );
      }
    }
  }
  invMgr.sendInventoryContainer( player, housingContainer );
  invMgr.saveHousingContainer( landIdent, housingContainer );
  updateHouseModels( land->getHouse() );
  if( !isInterior )
  {
    terri->sendLandUpdate( landIdent.landId );
  }
}

void Sapphire::World::Manager::HousingMgr::removeHouse( Entity::Player& player, uint16_t plot )
{
  auto terri = std::dynamic_pointer_cast< HousingZone >( player.getCurrentTerritory() );
  if( !terri )
    return;

  auto land = terri->getLand( static_cast< uint8_t >( plot ) );
  if( !land || !land->getHouse() )
    return;

  if( !hasPermission( player, *land, 0 ) )
    return;

  auto& interiorContainer = getEstateInventory( land->getLandIdent() )[ InventoryType::HousingInteriorAppearance ];
  auto& invMgr = Service< InventoryMgr >::ref();

  std::unordered_map< InventoryType, ItemContainerPtr > changedContainerSet = {};

  for( int i = 0; i < interiorContainer->getMaxSize(); i++ )
  {
    auto item = interiorContainer->getItem( i );
    if( !item )
      continue;

    Inventory::InventoryContainerPair freeSlotPair;
    auto freeContainer = getFreeEstateInventorySlot( land->getLandIdent(), freeSlotPair, m_internalStoreroomContainers );
    if ( !freeContainer )
    {
      // not sure what to do
      interiorContainer->removeItem( i, true );
    }
    else
    {
      interiorContainer->removeItem( i, false );
      freeContainer->setItem( freeSlotPair.second , item );
      changedContainerSet[ freeSlotPair.first ] = freeContainer;
    }
  }

  invMgr.sendInventoryContainer( player, interiorContainer );
  invMgr.saveHousingContainer( land->getLandIdent(), interiorContainer );
  for( auto entry : changedContainerSet )
  {
    invMgr.sendInventoryContainer( player, entry.second );
    invMgr.saveHousingContainer( land->getLandIdent(), entry.second );
  }

  deleteHouse( land->getHouse() );
  land->setHouse( nullptr );

  land->setStatus( HouseStatus::Sold );
  land->updateLandDb();
  terri->sendLandUpdate( plot );

  player.setLandFlags( LandFlagsSlot::Private, 0, land->getLandIdent() );

  terri->removeEstateEntranceEObj( plot );

  // missing reply for ClientTrigger RequestEstateHallRemoval
}