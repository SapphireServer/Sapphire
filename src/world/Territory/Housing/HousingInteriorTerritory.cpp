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
#include "Manager/HousingMgr.h"
#include "Manager/TerritoryMgr.h"
#include "WorldServer.h"
#include "Territory/Land.h"
#include "Territory/House.h"
#include "Inventory/ItemContainer.h"
#include "Inventory/HousingItem.h"

#include "Forwards.h"
#include "HousingInteriorTerritory.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::World::Manager;

using namespace Sapphire;
using namespace Sapphire::World::Territory;

Sapphire::World::Territory::Housing::HousingInteriorTerritory::HousingInteriorTerritory( Common::LandIdent ident,
                                                                                         uint16_t territoryTypeId,
                                                                                         uint32_t guId,
                                                                                         const std::string& internalName,
                                                                                         const std::string& contentName ) :
  Territory( territoryTypeId, guId, internalName, contentName ),
  m_landIdent( ident )
{
}

Housing::HousingInteriorTerritory::~HousingInteriorTerritory() = default;

bool Sapphire::World::Territory::Housing::HousingInteriorTerritory::init()
{
  updateHousingObjects();

  return true;
}

void Sapphire::World::Territory::Housing::HousingInteriorTerritory::onPlayerZoneIn( Entity::Player& player )
{
  auto& housingMgr = Common::Service< HousingMgr >::ref();
  auto& server = Common::Service< World::WorldServer >::ref();

  Logger::debug( "HousingInteriorTerritory::onPlayerZoneIn: Territory#{0}|{1}, Entity#{2}",
                  getGuId(), getTerritoryTypeId(), player.getId() );

  auto indoorInitPacket = makeZonePacket< FFXIVIpcInterior >( player.getId() );

  auto landSetId = housingMgr.toLandSetId( m_landIdent.territoryTypeId, m_landIdent.wardNum  );

  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pTeri = teriMgr.getTerritoryByGuId( landSetId );
  auto hZone = std::dynamic_pointer_cast< HousingZone >( pTeri );
  auto pLand = hZone->getLand( static_cast< uint8_t >( m_landIdent.landId ) );

  auto pHouse = pLand->getHouse();

  for( auto i = 0; i < 10; i++ )
  {
    indoorInitPacket->data().Interior[ i ] = static_cast< uint16_t >( pHouse->getInteriorModel(
      static_cast< Common::HouseInteriorSlot >( i ) ) );
  }

  server.queueForPlayer( player.getCharacterId(), indoorInitPacket );

  bool isFcHouse = pLand->getStatus() == Common::HouseStatus::PrivateEstate;
  HouseSize size = pLand->getSize();

  switch( size )
  {
    case HouseSize::HOUSE_SIZE_S:
    {
      auto objectInitPacket = makeZonePacket< FFXIVIpcFurnitureListS >( player.getId() );
      memcpy( &objectInitPacket->data().LandId, &m_landIdent, sizeof( Common::LandIdent ) );
      memcpy( &objectInitPacket->data().Furnitures, m_housingObjects.data(), sizeof( Common::Furniture ) * 100 );
      server.queueForPlayer( player.getCharacterId(), objectInitPacket );
      break;
    }
    case HouseSize::HOUSE_SIZE_M:
    {
      auto objectInitPacket = makeZonePacket< FFXIVIpcFurnitureListM >( player.getId() );
      memcpy( &objectInitPacket->data().LandId, &m_landIdent, sizeof( Common::LandIdent ) );
      memcpy( &objectInitPacket->data().Furnitures, m_housingObjects.data(), sizeof( Common::Furniture ) * 150 );
      server.queueForPlayer( player.getCharacterId(), objectInitPacket );
      break;
    }
    case HouseSize::HOUSE_SIZE_L:
    {
            auto objectInitPacket = makeZonePacket< FFXIVIpcFurnitureListL >( player.getId() );
      memcpy( &objectInitPacket->data().LandId, &m_landIdent, sizeof( Common::LandIdent ) );
      memcpy( &objectInitPacket->data().Furnitures, m_housingObjects.data(), sizeof( Common::Furniture ) * 200 );
      break;
    }
  }

  if( isFcHouse )
    server.queueForPlayer( player.getCharacterId(),
      makeActorControlSelf( player.getId(), Network::ActorControl::HideAdditionalChambersDoor ) );
}

void Sapphire::World::Territory::Housing::HousingInteriorTerritory::onUpdate( uint64_t tickCount )
{

}

const Common::LandIdent Sapphire::World::Territory::Housing::HousingInteriorTerritory::getLandIdent() const
{
  return m_landIdent;
}

void Sapphire::World::Territory::Housing::HousingInteriorTerritory::updateHousingObjects()
{
  auto& housingMgr = Common::Service< Manager::HousingMgr >::ref();

  auto containerIds = {
    InventoryType::HousingInteriorPlacedItems1,
    InventoryType::HousingInteriorPlacedItems2,
    InventoryType::HousingInteriorPlacedItems3,
    InventoryType::HousingInteriorPlacedItems4,
    InventoryType::HousingInteriorPlacedItems5,
    InventoryType::HousingInteriorPlacedItems6,
    InventoryType::HousingInteriorPlacedItems7,
    InventoryType::HousingInteriorPlacedItems8,
  };

  // zero out the array
  // there's some really weird behaviour where *some* values will cause the linkshell invite notification to pop up
  // for some reason
  Common::Furniture obj {};
  memset( &obj, 0x0, sizeof( Common::Furniture ) );
  m_housingObjects.fill( obj );

  auto containers = housingMgr.getEstateInventory( getLandIdent() );

  uint8_t containerIdx = 0;
  for( auto containerId : containerIds )
  {
    auto container = containers.find( containerId );
    if( container == containers.end() )
      // no more containers left
      break;

    for( const auto& item : container->second->getItemMap() )
    {
      auto housingItem = std::dynamic_pointer_cast< Inventory::HousingItem >( item.second );
      assert( housingItem );

      auto offset = item.first + ( containerIdx * 50 );

      auto obj = housingMgr.getYardObjectForItem( housingItem );

      m_housingObjects[static_cast< size_t >( offset ) ] = obj;
    }

    containerIdx++;
  }
}

void Sapphire::World::Territory::Housing::HousingInteriorTerritory::spawnHousingObject( uint8_t containerIdx,
                                                                                        uint16_t slot,
                                                                                        uint16_t containerType,
                                                                                        Inventory::HousingItemPtr item )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto& housingMgr = Common::Service< Manager::HousingMgr >::ref();

  auto offset = ( containerIdx * 50 ) + slot;
  auto obj = housingMgr.getYardObjectForItem( item );

  m_housingObjects[ static_cast< size_t >( offset ) ] = obj;

  for( const auto& player : m_playerMap )
  {
    auto objectSpawnPkt = makeZonePacket< FFXIVIpcFurniture >( player.second->getId() );

    objectSpawnPkt->data().StorageId = containerType;
    objectSpawnPkt->data().ContainerIndex = static_cast< uint8_t >( slot );

    objectSpawnPkt->data().Furniture.patternId = item->getAdditionalData() & 0xFFFF;
    objectSpawnPkt->data().Furniture.dir = Util::floatToUInt16Rot( item->getRot() );
    objectSpawnPkt->data().Furniture.pos[ 0 ] = Util::floatToUInt16( item->getPos().x );
    objectSpawnPkt->data().Furniture.pos[ 1 ] = Util::floatToUInt16( item->getPos().y );
    objectSpawnPkt->data().Furniture.pos[ 2 ] = Util::floatToUInt16( item->getPos().z );

    server.queueForPlayer( player.second->getCharacterId(), objectSpawnPkt );
  }
}

void Sapphire::World::Territory::Housing::HousingInteriorTerritory::updateHousingObjectPosition( Entity::Player& sourcePlayer,
                                                                                                 uint16_t slot,
                                                                                                 Common::FFXIVARR_POSITION3 pos,
                                                                                                 uint16_t rot )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto& obj = m_housingObjects[ slot ];

  obj.pos[ 0 ] = Util::floatToUInt16( pos.x );
  obj.pos[ 1 ] = Util::floatToUInt16( pos.y );
  obj.pos[ 2 ] = Util::floatToUInt16( pos.z );
  obj.dir = Util::floatToUInt16Rot( rot );

  // todo: how does this update on other clients?

  for( const auto& player : m_playerMap )
  {
    if( player.second->getId() == sourcePlayer.getId() )
      continue;

    auto moveObjPkt = makeZonePacket< FFXIVIpcHousingObjectTransform >( player.second->getId() );

    moveObjPkt->data().Dir = static_cast< uint16_t >( obj.dir );
    moveObjPkt->data().Pos[ 0 ] = obj.pos[ 0 ];
    moveObjPkt->data().Pos[ 1 ] = obj.pos[ 1 ];
    moveObjPkt->data().Pos[ 2 ] = obj.pos[ 2 ];

    // todo: how does this work when an item is in a slot >50 or u8 max? my guess is landid is the container index, but not sure...
    moveObjPkt->data().ContainerIndex = static_cast< uint8_t >( slot % 50 );
    moveObjPkt->data().UserData2 = slot / 50;

    server.queueForPlayer( player.second->getCharacterId(), moveObjPkt );
  }
}

void Sapphire::World::Territory::Housing::HousingInteriorTerritory::removeHousingObject( uint16_t slot )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  memset( m_housingObjects.data() + slot, 0x0, sizeof( Common::Furniture ) );

  for( const auto& player : m_playerMap )
  {
    auto pkt = makeActorControlSelf( player.second->getId(), Network::ActorControl::RemoveInteriorHousingItem, slot );

    server.queueForPlayer( player.second->getCharacterId(), pkt );
  }
}
