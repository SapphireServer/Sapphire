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
#include "Manager/HousingMgr.h"
#include "Territory/Land.h"
#include "Territory/House.h"
#include "Inventory/ItemContainer.h"
#include "Inventory/HousingItem.h"

#include "Forwards.h"
#include "HousingInteriorTerritory.h"
#include "Framework.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::World::Manager;

using namespace Sapphire;
using namespace Sapphire::World::Territory;

Sapphire::World::Territory::Housing::HousingInteriorTerritory::HousingInteriorTerritory( Common::LandIdent ident,
                                                                                         uint16_t territoryTypeId,
                                                                                         uint32_t guId,
                                                                                         const std::string& internalName,
                                                                                         const std::string& contentName,
                                                                                         FrameworkPtr pFw ) :
  Zone( territoryTypeId, guId, internalName, contentName, pFw ),
  m_landIdent( ident )
{
  m_lastActivityTime = static_cast< uint32_t >( Util::getTimeSeconds() );
}

Housing::HousingInteriorTerritory::~HousingInteriorTerritory() = default;

bool Sapphire::World::Territory::Housing::HousingInteriorTerritory::init()
{
  updateHousingObjects();

  return true;
}

void Sapphire::World::Territory::Housing::HousingInteriorTerritory::onPlayerZoneIn( Entity::Player& player )
{
  auto pHousingMgr = m_pFw->get< HousingMgr >();

  Logger::debug( "HousingInteriorTerritory::onPlayerZoneIn: Zone#{0}|{1}, Entity#{2}",
                  getGuId(), getTerritoryTypeId(), player.getId() );

  auto indoorInitPacket = makeZonePacket< Server::FFXIVIpcHousingIndoorInitialize >( player.getId() );
  indoorInitPacket->data().u1 = 0;
  indoorInitPacket->data().u2 = 0;
  indoorInitPacket->data().u3 = 0;
  indoorInitPacket->data().u4 = 0;

  auto landSetId = pHousingMgr->toLandSetId( m_landIdent.territoryTypeId, m_landIdent.wardNum );
  auto pLand = pHousingMgr->getHousingZoneByLandSetId( landSetId )->getLand( m_landIdent.landId );
  auto pHouse = pLand->getHouse();

  for( auto i = 0; i < 10; i++ )
  {
    indoorInitPacket->data().indoorItems[ i ] = pHouse->getInteriorModel(
      static_cast< Common::HouseInteriorSlot >( i ) );
  }

  player.queuePacket( indoorInitPacket );

  bool isFcHouse = pLand->getStatus() == Common::HouseStatus::PrivateEstate;

  auto yardPacketTotal = static_cast< uint8_t >( 2 + pLand->getSize() );
  for( uint8_t yardPacketNum = 0; yardPacketNum < yardPacketTotal; yardPacketNum++ )
  {
    auto objectInitPacket = makeZonePacket< Server::FFXIVIpcHousingObjectInitialize >( player.getId() );
    memcpy( &objectInitPacket->data().landIdent, &m_landIdent, sizeof( Common::LandIdent ) );

    if( isFcHouse )
      objectInitPacket->data().u1 = 2; // 2 = actrl 0x400 will hide the fc door, otherwise it will stay there
    else
      objectInitPacket->data().u1 = 0;

    objectInitPacket->data().u2 = 100;
    objectInitPacket->data().packetNum = yardPacketNum;
    objectInitPacket->data().packetTotal = yardPacketTotal;

    auto yardObjectSize = sizeof( Common::HousingObject );
    memcpy( &objectInitPacket->data().object, m_housingObjects.data() + ( yardPacketNum * 100 ), yardObjectSize * 100 );

    player.queuePacket( objectInitPacket );
  }

  if( isFcHouse )
    player.queuePacket( Server::makeActorControl143( player.getId(), Network::ActorControl::HideAdditionalChambersDoor ) );
}

void Sapphire::World::Territory::Housing::HousingInteriorTerritory::onUpdate( uint32_t currTime )
{
  if( m_playerMap.size() > 0 )
    m_lastActivityTime = currTime;
}

uint32_t Sapphire::World::Territory::Housing::HousingInteriorTerritory::getLastActivityTime() const
{
  return m_lastActivityTime;
}

const Common::LandIdent Sapphire::World::Territory::Housing::HousingInteriorTerritory::getLandIdent() const
{
  return m_landIdent;
}

void Sapphire::World::Territory::Housing::HousingInteriorTerritory::updateHousingObjects()
{
  auto housingMgr = m_pFw->get< Manager::HousingMgr >();

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
  Common::HousingObject obj {};
  memset( &obj, 0x0, sizeof( Common::HousingObject ) );
  m_housingObjects.fill( obj );

  auto containers = housingMgr->getEstateInventory( getLandIdent() );

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

      auto obj = housingMgr->getYardObjectForItem( housingItem );

      m_housingObjects[ offset ] = obj;
    }

    containerIdx++;
  }
}

void Sapphire::World::Territory::Housing::HousingInteriorTerritory::spawnHousingObject( uint8_t containerIdx,
                                                                                        uint16_t slot,
                                                                                        uint16_t containerType,
                                                                                        Inventory::HousingItemPtr item )
{
  auto housingMgr = m_pFw->get< Manager::HousingMgr >();

  auto offset = ( containerIdx * 50 ) + slot;
  auto obj = housingMgr->getYardObjectForItem( item );

  m_housingObjects[ offset ] = obj;

  for( const auto& player : m_playerMap )
  {
    auto objectSpawnPkt = makeZonePacket< Server::FFXIVIpcHousingInternalObjectSpawn >( player.second->getId() );

    objectSpawnPkt->data().containerId = containerType;
    objectSpawnPkt->data().containerOffset = slot;

    objectSpawnPkt->data().itemId = item->getAdditionalData() & 0xFFFF;
    objectSpawnPkt->data().rotation = item->getRot();
    objectSpawnPkt->data().pos = item->getPos();

    player.second->queuePacket( objectSpawnPkt );
  }
}

void Sapphire::World::Territory::Housing::HousingInteriorTerritory::updateHousingObjectPosition( Entity::Player& sourcePlayer,
                                                                                                 uint16_t slot,
                                                                                                 Common::FFXIVARR_POSITION3_U16 pos,
                                                                                                 uint16_t rot )
{
  auto& obj = m_housingObjects[ slot ];

  obj.pos = pos;
  obj.itemRotation = rot;

  // todo: how does this update on other clients?

  for( const auto& player : m_playerMap )
  {
    if( player.second->getId() == sourcePlayer.getId() )
      continue;

    auto moveObjPkt = makeZonePacket< Server::FFXIVIpcHousingObjectMove >( player.second->getId() );

    moveObjPkt->data().itemRotation = obj.itemRotation;
    moveObjPkt->data().pos = obj.pos;

    // todo: how does this work when an item is in a slot >50 or u8 max? my guess is landid is the container index, but not sure...
    moveObjPkt->data().objectArray = static_cast< uint8_t >( slot % 50 );
    moveObjPkt->data().landId = static_cast< uint8_t >( slot / 50 );

    player.second->queuePacket( moveObjPkt );
  }
}

void Sapphire::World::Territory::Housing::HousingInteriorTerritory::removeHousingObject( uint16_t slot )
{
  memset( m_housingObjects.data() + slot, 0x0, sizeof( Common::HousingObject ) );

  for( const auto& player : m_playerMap )
  {
    auto pkt = Server::makeActorControl143( player.second->getId(), Network::ActorControl::RemoveInteriorHousingItem, slot );

    player.second->queuePacket( pkt );
  }
}