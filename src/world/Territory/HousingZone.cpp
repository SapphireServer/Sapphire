#include <Common.h>
#include <Logging/Logger.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Database/DatabaseDef.h>
#include <Exd/ExdData.h>
#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketWrappers/ActorControlSelfPacket.h>
#include <Network/CommonActorControl.h>
#include <Service.h>

#include "Actor/Player.h"
#include "Actor/GameObject.h"
#include "Actor/EventObject.h"
#include "Land.h"
#include "House.h"
#include "Inventory/HousingItem.h"
#include "Inventory/ItemContainer.h"
#include "WorldServer.h"

#include <datReader/DatCategories/bg/LgbTypes.h>
#include <datReader/DatCategories/bg/lgb.h>

#include "Forwards.h"
#include "HousingZone.h"
#include "Manager/HousingMgr.h"
#include "InstanceObjectCache.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::World::Manager;

Sapphire::HousingZone::HousingZone( uint8_t wardNum, uint16_t territoryTypeId,
                                    const std::string& internalName, const std::string& contentName ) :
  Territory( territoryTypeId, ( static_cast< uint32_t >( territoryTypeId ) << 16 ) | wardNum, internalName, contentName ),
  m_wardNum( wardNum ),
  m_landSetId( ( static_cast< uint32_t >( territoryTypeId ) << 16 ) | wardNum )
{
}

bool Sapphire::HousingZone::init()
{

  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  {
    auto res = db.query( "SELECT * FROM landset WHERE landsetid = " + std::to_string( m_landSetId ) );
    if( !res->next() )
    {
      db.directExecute( "INSERT INTO landset ( landsetid ) VALUES ( " + std::to_string( m_landSetId ) + " );" );
    }
  }


  int housingIndex;
  if( m_territoryTypeId == 339 )
    housingIndex = 0;
  else if( m_territoryTypeId == 340 )
    housingIndex = 1;
  else if( m_territoryTypeId == 341 )
    housingIndex = 2;

  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto info = exdData.getRow< Excel::HousingLandSet >( housingIndex );

  // build yard objects array indices
  int16_t cursor = -1;
  uint16_t index = 0;
  for( const auto entry : info->data().Lands )
  {
    uint16_t itemMax = 0;
    switch( entry.Size )
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
  Common::Furniture obj {};
  memset( &obj, 0x0, sizeof( Common::Furniture ) );

  for( auto& arr : m_yardObjects )
  {
    memcpy( &arr, &m_yardObjects, sizeof( Common::Furniture ) );
  }

  auto& housingMgr = Common::Service< World::Manager::HousingMgr >::ref();
  auto landCache = housingMgr.getLandCacheMap();

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
    auto land = make_Land( m_territoryTypeId, getWardNum(), entry.m_landId, m_landSetId, info );

    // setup house
    if( entry.m_houseId )
    {
      auto house = make_House( entry.m_houseId, m_landSetId, land->getLandIdent(), entry.m_estateName, entry.m_estateComment );
      housingMgr.updateHouseModels( house );
      land->setHouse( house );
    }

    land->init( entry.m_type, entry.m_size, entry.m_status, entry.m_currentPrice, entry.m_ownerId, entry.m_houseId );

    m_landPtrMap[ entry.m_landId ] = land;

    // TODO: Fixme
    if( entry.m_houseId > 0 )
      registerEstateEntranceEObj( entry.m_landId );

    updateYardObjects( land->getLandIdent() );
  }

  return true;
}

bool Sapphire::HousingZone::isPlayerSubInstance( Entity::Player& player )
{
  return player.getPos().x < -15000.0f; //ToDo: get correct pos
}

void Sapphire::HousingZone::onPlayerZoneIn( Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  Logger::debug( "HousingZone::onPlayerZoneIn: Territory#{0}|{1}, Entity#{2}",
                 getGuId(), getTerritoryTypeId(), player.getId() );

  auto isInSubdivision = isPlayerSubInstance( player );

  uint32_t yardPacketNum;
  uint32_t yardPacketTotal = 8;

  sendLandSet( player );

  for( yardPacketNum = 0; yardPacketNum < yardPacketTotal; yardPacketNum++ )
  {
    auto housingObjectInit = makeZonePacket< FFXIVIpcYardObjectList >( player.getId() );
    housingObjectInit->data().PacketIndex = yardPacketNum;
    auto yardObjectSize = sizeof( Common::Furniture );
    housingObjectInit->data().PacketIndex = yardPacketNum;
    housingObjectInit->data().PacketEnd = yardPacketTotal;

    auto& objects = m_yardObjects[ isInSubdivision ? 1 : 0 ];

    memcpy( &housingObjectInit->data().YardObjects, &objects + ( yardPacketNum * 100 ), yardObjectSize * 100 );

    server.queueForPlayer( player.getCharacterId(), housingObjectInit );
  }
}

void Sapphire::HousingZone::sendLandSet( Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto landsetInitializePacket = makeZonePacket< FFXIVIpcHouseList >( player.getId() );

  landsetInitializePacket->data().LandSetId.wardNum = m_wardNum;
  landsetInitializePacket->data().LandSetId.landId = m_landSetId;
  landsetInitializePacket->data().LandSetId.territoryTypeId = m_territoryTypeId;
  landsetInitializePacket->data().LandSetId.worldId = server.getWorldId();

  auto isInSubdivision = isPlayerSubInstance( player );
  landsetInitializePacket->data().Subdivision = isInSubdivision ? 2 : 1;
  for( uint8_t i = 0, count = 0; i < 30; ++i, ++count )
  {
    auto pLand = getLand( i );

    // todo: move this and sendLandUpdate building logic to its own function
    auto& landData = landsetInitializePacket->data().Houses[ count ];

    landData.size = pLand->getSize();
    landData.status = pLand->getStatus();
    landData.flags = pLand->getSharing();
    landData.fcCrestId = 1;
    /* //disbaled until we managed fc's
    landData.fcCrestId = pLand->getFcId();
    landData.fcIcon = pLand->getFcIcon();
    landData.fcIconColor = pLand->getFcColor();
    */

    if( auto house = pLand->getHouse() )
    {
      landData.flags = 1;

      auto& parts = house->getHouseModels();

      for( auto ii = 0; ii != parts.size(); ++ii )
      {
        landData.patternIds[ ii ] = parts[ ii ].first;
        landData.colors[ ii ] = parts[ ii ].second;
      }
    }
  }

  server.queueForPlayer( player.getCharacterId(), landsetInitializePacket );
}

void Sapphire::HousingZone::sendLandUpdate( uint8_t landId )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto pLand = getLand( landId );
  for( const auto& playerIt : m_playerMap )
  {
    auto pPlayer = playerIt.second;

    auto landUpdatePacket = makeZonePacket< FFXIVIpcHouse >( pPlayer->getId() );
    landUpdatePacket->data().Block = landId;

    auto& landData = landUpdatePacket->data().House;

    landData.size = pLand->getSize();
    landData.status = pLand->getStatus();
    landData.flags = pLand->getSharing();
    /*
    landData.fcId = pLand->getFcId();
    landData.fcIcon = pLand->getFcIcon();
    landData.fcIconColor = pLand->getFcColor();
    */

    if( auto house = pLand->getHouse() )
    {
      landData.flags = 1;

      auto& parts = house->getHouseModels();

      for( auto i = 0; i != parts.size(); ++i )
      {
        landData.patternIds[ i ] = parts[ i ].first;
        landData.colors[ i ] = parts[ i ].second;
      }
    }

    server.queueForPlayer( pPlayer->getCharacterId(), landUpdatePacket );
  }
}

void Sapphire::HousingZone::onUpdate( uint64_t tickCount )
{
  for( const auto& pLandItr : m_landPtrMap )
  {
    pLandItr.second->update( tickCount );
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

  int housingIndex;
  if( m_territoryTypeId == 339 )
    housingIndex = 0;
  else if( m_territoryTypeId == 340 )
    housingIndex = 1;
  else if( m_territoryTypeId == 341 )
    housingIndex = 2;

  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto info = exdData.getRow< Excel::HousingLandSet >( housingIndex );

  auto landInfo = info->_data.Lands[ landId ];
  auto& instanceObjectCache = Common::Service< InstanceObjectCache >::ref();

  FFXIVARR_POSITION3 pos{ 0, 10, 0 };
  auto eObjInfo = instanceObjectCache.getEObj( landInfo.SignboardEObj );
  if( eObjInfo )
  {
    pos.x = eObjInfo->data.transform.translation.x;
    pos.y = eObjInfo->data.transform.translation.y;
    pos.z = eObjInfo->data.transform.translation.z;
  }
  else
  {
    Logger::error( "No position could be determined for housing entrance!" );
  }

  auto eObj = Entity::make_EventObject( getNextEObjId(), 2002737, 0, 0, 0, pos, 0.f, "entrance", 0 );
  eObj->setHousingLink( static_cast< uint32_t >( landId ) );
  eObj->setScale( 1.f );

  addEObj( eObj );

  return eObj;
}

void Sapphire::HousingZone::removeEstateEntranceEObj( uint8_t landId )
{
  auto land = getLand( landId );
  assert( land );

  for( auto entry : m_eventObjects )
  {
    auto eObj = entry.second;
    if( eObj->getHousingLink() == static_cast< uint32_t >( landId ) << 8 )
    {
      removeActor( eObj );
      m_eventObjects.erase( entry.first );
      break;
    }
  }
}

void Sapphire::HousingZone::updateYardObjects( Sapphire::Common::LandIdent ident )
{
  auto& housingMgr = Common::Service< World::Manager::HousingMgr >::ref();
  auto& landStorage = housingMgr.getEstateInventory( ident );

  auto yardContainer = landStorage[ InventoryType::HousingExteriorPlacedItems ];

  auto arrayBounds = m_yardObjectArrayBounds[ ident.landId ];

  for( const auto& item : yardContainer->getItemMap() )
  {
    auto housingItem = std::dynamic_pointer_cast< Inventory::HousingItem >( item.second );
    assert( housingItem );

    auto idx = item.first + arrayBounds.first;
    m_yardObjects[ idx ] = housingMgr.getYardObjectForItem( housingItem );
  }
}

void Sapphire::HousingZone::spawnYardObject( uint8_t landId, uint16_t slotId, Inventory::HousingItem& item )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto bounds = m_yardObjectArrayBounds[ landId ];
  auto offset = bounds.first + slotId;

  Common::Furniture obj {};

  obj.patternId = item.getAdditionalData();
  obj.dir = Util::floatToUInt16Rot( item.getRot() );

  obj.pos[ 0 ] = Util::floatToUInt16( item.getPos().x );
  obj.pos[ 1 ] = Util::floatToUInt16( item.getPos().y );
  obj.pos[ 2 ] = Util::floatToUInt16( item.getPos().z );

  // link obj
  m_yardObjects[ offset ] = obj;

  // spawn obj in zone
  for( const auto& player : m_playerMap )
  {
    auto packet = makeZonePacket< FFXIVIpcYardObject >( player.second->getId() );

    packet->data().YardObject = obj;

    server.queueForPlayer( player.second->getCharacterId(), packet );
  }
}

void Sapphire::HousingZone::updateYardObjectPos( Entity::Player& sourcePlayer, uint16_t slot, uint16_t landId,
                                                 Inventory::HousingItem& item )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto bounds = m_yardObjectArrayBounds[ landId ];
  auto offset = bounds.first + slot;

  auto& obj = m_yardObjects[ offset ];

  obj.dir = Util::floatToUInt16( item.getRot() );
  obj.pos[ 0 ] = Util::floatToUInt16( item.getPos().x );
  obj.pos[ 1 ] = Util::floatToUInt16( item.getPos().y );
  obj.pos[ 2 ] = Util::floatToUInt16( item.getPos().z );

  for( const auto& player : m_playerMap )
  {
    // don't send it from the origin player, it already has the position from the move request
    if( player.second->getId() == sourcePlayer.getId() )
      continue;

    auto packet = makeZonePacket< FFXIVIpcHousingObjectTransform >( player.second->getId() );

    packet->data().Dir = Util::floatToUInt16( item.getRot() );
    packet->data().Pos[ 0 ] = Util::floatToUInt16( item.getPos().x );
    packet->data().Pos[ 1 ] = Util::floatToUInt16( item.getPos().y );
    packet->data().Pos[ 2 ] = Util::floatToUInt16( item.getPos().z );

    packet->data().UserData1 = static_cast< uint8_t >( landId );
    packet->data().UserData2 = static_cast< uint8_t >( slot );

    server.queueForPlayer( player.second->getCharacterId(), packet );
  }
}

void Sapphire::HousingZone::despawnYardObject( uint16_t landId, uint16_t slot )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto bounds = m_yardObjectArrayBounds[ landId ];
  auto offset = bounds.first + slot;

  memset( &m_yardObjects[ offset ], 0x00, sizeof( Common::Furniture ) );

  for( const auto& player : m_playerMap )
  {
    auto param = ( landId << 16 ) | slot;
    auto pkt = makeActorControlSelf( player.second->getId(), Network::ActorControl::RemoveExteriorHousingItem, param );

    server.queueForPlayer( player.second->getCharacterId(), pkt );
  }
}
