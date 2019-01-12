#include <Common.h>
#include <Logging/Logger.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Database/DatabaseDef.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/GamePacketNew.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketWrappers/ActorControlPacket143.h>
#include <Network/CommonActorControl.h>

#include "Actor/Player.h"
#include "Actor/Actor.h"
#include "Actor/EventObject.h"
#include "Land.h"
#include "House.h"
#include "Inventory/HousingItem.h"
#include "Inventory/ItemContainer.h"

#include "Forwards.h"
#include "HousingZone.h"
#include "Manager/HousingMgr.h"
#include "Framework.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::World::Manager;

Sapphire::HousingZone::HousingZone( uint8_t wardNum,
                                    uint16_t territoryTypeId,
                                    uint32_t guId,
                                    const std::string& internalName,
                                    const std::string& contentName,
                                    FrameworkPtr pFw ) :
  Zone( territoryTypeId, guId, internalName, contentName, pFw ),
  m_wardNum( wardNum ),
  m_territoryTypeId( territoryTypeId ),
  m_landSetId( ( static_cast< uint32_t >( territoryTypeId ) << 16 ) | wardNum ),
  m_pFw( pFw )
{

}

bool Sapphire::HousingZone::init()
{

  auto pDb = m_pFw->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  {
    auto res = pDb->query( "SELECT * FROM landset WHERE landsetid = " + std::to_string( m_landSetId ) );
    if( !res->next() )
    {
      pDb->directExecute( "INSERT INTO landset ( landsetid ) VALUES ( " + std::to_string( m_landSetId ) + " );" );
    }
  }


  int housingIndex;
  if( m_territoryTypeId == 339 )
    housingIndex = 0;
  else if( m_territoryTypeId == 340 )
    housingIndex = 1;
  else if( m_territoryTypeId == 341 )
    housingIndex = 2;
  else if( m_territoryTypeId == 641 )
    housingIndex = 3;

  auto pExdData = m_pFw->get< Data::ExdDataGenerated >();
  auto info = pExdData->get< Sapphire::Data::HousingLandSet >( housingIndex );

  // build yard objects array indices
  int16_t cursor = -1;
  uint16_t index = 0;
  for( const auto size : info->plotSize )
  {
    uint16_t itemMax = 0;
    switch( size )
    {
      case 0:
        itemMax = 20;
        break;

      case 1:
        itemMax = 30;
        break;

      case 2:
        itemMax = 40;
        break;
    }

    int16_t start = cursor + 1;
    int16_t end = cursor + itemMax;

    m_yardObjectArrayBounds[ index++ ] = std::make_pair( start, end );

    // reset cursor for subdivision
    if( index == 30 )
    {
      cursor = -1;

      continue;
    }

    cursor += itemMax;
  }

  // zero out the yard obj arrays so we don't leak memory like SE does :^)
  Common::HousingObject obj {};
  memset( &obj, 0x0, sizeof( Common::HousingObject ) );

  for( auto& arr : m_yardObjects )
  {
    arr.fill( obj );
  }

  auto housingMgr = m_pFw->get< World::Manager::HousingMgr >();
  auto landCache = housingMgr->getLandCacheMap();

  // make sure the landset exists
  auto landSetCache = landCache.find( m_landSetId );
  if( landSetCache == landCache.end() )
  {
    Logger::fatal( "LandSet {0} is missing from the land cache.", m_landSetId );
    return false;
  }

  // init the lands
  for( HousingMgr::LandCacheEntry& entry : landSetCache->second )
  {
    auto land = make_Land( m_territoryTypeId, getWardNum(), entry.m_landId, m_landSetId, info, m_pFw );

    // setup house
    if( entry.m_houseId )
    {
      auto house = make_House( entry.m_houseId, m_landSetId, land->getLandIdent(), entry.m_estateName,
                               entry.m_estateComment, m_pFw );

      housingMgr->updateHouseModels( house );
      land->setHouse( house );
    }

    land->init( entry.m_type, entry.m_size, entry.m_status, entry.m_currentPrice, entry.m_ownerId, entry.m_houseId );

    m_landPtrMap[ entry.m_landId ] = land;

    if( entry.m_houseId > 0 )
      registerEstateEntranceEObj( entry.m_landId );

    updateYardObjects( land->getLandIdent() );
  }

  return true;
}

Sapphire::HousingZone::~HousingZone() = default;

void Sapphire::HousingZone::onPlayerZoneIn( Entity::Player& player )
{
  Logger::debug( "HousingZone::onPlayerZoneIn: Zone#{0}|{1}, Entity#{2}",
                 getGuId(), getTerritoryTypeId(), player.getId() );

  auto isInSubdivision = isPlayerSubInstance( player ) ? true : false;

  uint32_t yardPacketNum;
  uint32_t yardPacketTotal = 8;

  sendLandSet( player );

  for( yardPacketNum = 0; yardPacketNum < yardPacketTotal; yardPacketNum++ )
  {
    auto housingObjectInit = makeZonePacket< FFXIVIpcHousingObjectInitialize >( player.getId() );
    memset( &housingObjectInit->data().landIdent, 0xFF, sizeof( Common::LandIdent ) );
    housingObjectInit->data().u1 = 0xFF;
    housingObjectInit->data().packetNum = yardPacketNum;
    housingObjectInit->data().packetTotal = yardPacketTotal;

    auto yardObjectSize = sizeof( Common::HousingObject );

    auto& objects = m_yardObjects[ isInSubdivision ? 1 : 0 ];

    memcpy( &housingObjectInit->data().object, objects.data() + ( yardPacketNum * 100 ), yardObjectSize * 100 );

    player.queuePacket( housingObjectInit );
  }

  auto landSetMap = makeZonePacket< FFXIVIpcLandSetMap >( player.getId() );
  landSetMap->data().subdivision = isInSubdivision ? 1 : 2;

  uint8_t startIndex = isInSubdivision ? 30 : 0;

  for( uint8_t i = startIndex, count = 0; i < ( startIndex + 30 ); i++, count++ )
  {
    landSetMap->data().landInfo[ count ].status = 1;
  }

  player.queuePacket( landSetMap );

}

void Sapphire::HousingZone::sendLandSet( Entity::Player& player )
{
  auto landsetInitializePacket = makeZonePacket< FFXIVIpcLandSetInitialize >( player.getId() );

  landsetInitializePacket->data().landIdent.wardNum = m_wardNum;
  //landsetInitializePacket->data().landIdent.landSetId = m_landSetId;
  landsetInitializePacket->data().landIdent.territoryTypeId = m_territoryTypeId;
  //TODO: get current WorldId
  landsetInitializePacket->data().landIdent.worldId = 67;
  landsetInitializePacket->data().subInstance = !isPlayerSubInstance( player ) ? 1 : 2;

  uint8_t startIndex = !isPlayerSubInstance( player ) ? 0 : 30;

  for( uint8_t i = startIndex, count = 0; i < ( startIndex + 30 ); ++i, ++count )
  {
    auto pLand = getLand( i );

    // todo: move this and sendLandUpdate building logic to its own function
    auto& landData = landsetInitializePacket->data().land[ count ];

    landData.plotSize = pLand->getSize();
    landData.houseState = pLand->getStatus();
    landData.iconAddIcon = pLand->getSharing();
    landData.fcId = pLand->getFcId();
    landData.fcIcon = pLand->getFcIcon();
    landData.fcIconColor = pLand->getFcColor();

    if( auto house = pLand->getHouse() )
    {
      landData.flags = 1;

      auto& parts = house->getHouseModels();

      for( auto i = 0; i != parts.size(); i++ )
      {
        landData.housePart[ i ] = parts[ i ].first;
        landData.houseColour[ i ] = parts[ i ].second;
      }
    }
  }

  player.queuePacket( landsetInitializePacket );
}

void Sapphire::HousingZone::sendLandUpdate( uint8_t landId )
{
  auto pLand = getLand( landId );
  for( const auto& playerIt : m_playerMap )
  {
    auto pPlayer = playerIt.second;

    auto landUpdatePacket = makeZonePacket< FFXIVIpcLandUpdate >( pPlayer->getId() );
    landUpdatePacket->data().landIdent.landId = landId;

    auto& landData = landUpdatePacket->data().land;

    landData.plotSize = pLand->getSize();
    landData.houseState = pLand->getStatus();
    landData.iconAddIcon = pLand->getSharing();
    landData.fcId = pLand->getFcId();
    landData.fcIcon = pLand->getFcIcon();
    landData.fcIconColor = pLand->getFcColor();


    if( auto house = pLand->getHouse() )
    {
      landData.flags = 1;

      auto& parts = house->getHouseModels();

      for( auto i = 0; i != parts.size(); i++ )
      {
        landData.housePart[ i ] = parts[ i ].first;
        landData.houseColour[ i ] = parts[ i ].second;
      }
    }

    pPlayer->queuePacket( landUpdatePacket );
  }
}

bool Sapphire::HousingZone::isPlayerSubInstance( Entity::Player& player )
{
  return player.getPos().x < -15000.0f; //ToDo: get correct pos
}

void Sapphire::HousingZone::onUpdate( uint32_t currTime )
{
  for( auto pLandItr : m_landPtrMap )
  {
    pLandItr.second->update( currTime );
  }
}

uint8_t Sapphire::HousingZone::getWardNum() const
{
  return m_wardNum;
}

uint32_t Sapphire::HousingZone::getLandSetId() const
{
  return m_landSetId;
}

Sapphire::LandPtr Sapphire::HousingZone::getLand( uint8_t id )
{
  auto it = m_landPtrMap.find( id );
  if( it == m_landPtrMap.end() )
    return nullptr;

  return it->second;
}

Sapphire::Entity::EventObjectPtr Sapphire::HousingZone::registerEstateEntranceEObj( uint8_t landId )
{
  auto land = getLand( landId );
  assert( land );

  auto eObj = Entity::make_EventObject( getNextEObjId(), 2002737, 0, 4, land->getMapMarkerPosition(), 0.f, "entrance" );
  eObj->setHousingLink( landId << 8 );
  eObj->setScale( 1.f );

  registerEObj( eObj );

  return eObj;
}

void Sapphire::HousingZone::updateYardObjects( Sapphire::Common::LandIdent ident )
{
  auto housingMgr = m_pFw->get< World::Manager::HousingMgr >();
  auto& landStorage = housingMgr->getEstateInventory( ident );

  auto yardContainer = landStorage[ InventoryType::HousingExteriorPlacedItems ];

  auto arrayBounds = m_yardObjectArrayBounds[ ident.landId ];
  auto yardMapIndex = ident.landId <= 29 ? 0 : 1;

  for( const auto& item : yardContainer->getItemMap() )
  {
    auto housingItem = std::dynamic_pointer_cast< Inventory::HousingItem >( item.second );
    assert( housingItem );

    auto idx = item.first + arrayBounds.first;
    m_yardObjects[ yardMapIndex ][ idx ] = housingMgr->getYardObjectForItem( housingItem );
  }
}

void Sapphire::HousingZone::spawnYardObject( uint8_t landId, uint16_t slotId, Inventory::HousingItem& item )
{
  auto bounds = m_yardObjectArrayBounds[ landId ];
  auto offset = bounds.first + slotId;

  Common::HousingObject obj {};

  obj.itemId = item.getAdditionalData();
  obj.rotation = item.getRot();

  obj.pos = item.getPos();

  // link obj
  auto yardMapIndex = landId <= 29 ? 0 : 1;
  m_yardObjects[ yardMapIndex ][ offset ] = obj;

  // spawn obj in zone
  for( const auto& player : m_playerMap )
  {
    auto packet = makeZonePacket< Server::FFXIVIpcYardObjectSpawn >( player.second->getId() );

    packet->data().landId = landId;
    packet->data().objectArray = static_cast< uint8_t >( slotId );
    packet->data().object = obj;

    player.second->queuePacket( packet );
  }
}

void Sapphire::HousingZone::updateYardObjectPos( Entity::Player& sourcePlayer, uint16_t slot, uint16_t landId,
                                                 Inventory::HousingItem& item )
{
  auto bounds = m_yardObjectArrayBounds[ landId ];
  auto offset = bounds.first + slot;
  auto yardMapIndex = landId <= 29 ? 0 : 1;

  auto& obj = m_yardObjects[ yardMapIndex ][ offset ];

  obj.rotation = item.getRot();
  obj.pos = item.getPos();

  for( const auto& player : m_playerMap )
  {
    // don't send it from the origin player, it already has the position from the move request
    if( player.second->getId() == sourcePlayer.getId() )
      continue;

    auto packet = makeZonePacket< Server::FFXIVIpcHousingObjectMove >( player.second->getId() );

    packet->data().itemRotation = item.getRot();
    packet->data().pos = item.getPos();

    packet->data().landId = landId;
    packet->data().objectArray = slot;

    player.second->queuePacket( packet );
  }
}

void Sapphire::HousingZone::despawnYardObject( uint16_t landId, uint16_t slot )
{
  auto bounds = m_yardObjectArrayBounds[ landId ];
  auto offset = bounds.first + slot;
  auto yardMapIndex = landId <= 29 ? 0 : 1;

  memset( &m_yardObjects[ yardMapIndex ][ offset ], 0x00, sizeof( Common::HousingObject ) );

  for( const auto& player : m_playerMap )
  {
    auto param = ( landId << 16 ) | slot;
    auto pkt = Server::makeActorControl143( player.second->getId(), Network::ActorControl::RemoveExteriorHousingItem, param );

    player.second->queuePacket( pkt );
  }
}