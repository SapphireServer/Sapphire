#include <Common.h>
#include <Logging/Logger.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Database/DatabaseDef.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/GamePacketNew.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

#include "Actor/Player.h"
#include "Actor/Actor.h"
#include "Land.h"

#include "Forwards.h"
#include "HousingZone.h"
#include "HousingMgr.h"
#include "Framework.h"

extern Core::Framework g_fw;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

Core::HousingZone::HousingZone( uint8_t wardNum,
                                uint16_t territoryTypeId,
                                uint32_t guId,
                                const std::string& internalName,
                                const std::string& contentName ) :
  Zone( territoryTypeId, guId, internalName, contentName ),
  m_wardNum( wardNum ),
  m_zoneId( territoryTypeId ),
  m_landSetId( ( static_cast< uint32_t >( territoryTypeId ) << 16 ) | wardNum )
{

}

bool Core::HousingZone::init()
{

  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto res = pDb->query( "SELECT * FROM landset WHERE landsetid = " + std::to_string( m_landSetId ) );
  if( !res->next() )
  {
    pDb->directExecute( "INSERT INTO landset ( landsetid ) VALUES ( " + std::to_string( m_landSetId ) + " );" );
  }

  int housingIndex;
  if( m_zoneId == 339 )
    housingIndex = 0;
  else if( m_zoneId == 340 )
    housingIndex = 1;
  else if( m_zoneId == 341 )
    housingIndex = 2;
  else if( m_zoneId == 641 )
    housingIndex = 3;

  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  auto info = pExdData->get< Core::Data::HousingLandSet >( housingIndex );

  uint32_t landId;
  for( landId = 0; landId < 60; landId++ )
  {
    auto pObject = make_Land( m_territoryTypeId, getWardNum(), landId, m_landSetId, info );
    m_landPtrMap[ landId ] = pObject;
  }

  auto pHousingMgr = g_fw.get< HousingMgr >();
  pHousingMgr->insertHousingZone( (HousingZonePtr)this );

  return true;
}

Core::HousingZone::~HousingZone()
{

}

void Core::HousingZone::onPlayerZoneIn( Entity::Player& player )
{
  auto pLog = g_fw.get< Logger >();
  pLog->debug(
    "HousingZone::onPlayerZoneIn: Zone#" + std::to_string( getGuId() ) + "|" + std::to_string( getTerritoryTypeId() ) +
    ", Entity#" + std::to_string( player.getId() ) );

  uint32_t yardPacketNum;
  uint32_t yardPacketTotal = 8;

  sendLandSet( player );

  for( yardPacketNum = 0; yardPacketNum < yardPacketTotal; yardPacketNum++ )
  {
    auto landsetYardInitializePacket = makeZonePacket< FFXIVIpcLandSetYardInitialize >( player.getId() );
    landsetYardInitializePacket->data().unknown1 = 0xFFFFFFFF;
    landsetYardInitializePacket->data().unknown2 = 0xFFFFFFFF;
    landsetYardInitializePacket->data().unknown3 = 0xFF;
    landsetYardInitializePacket->data().packetNum = yardPacketNum;
    landsetYardInitializePacket->data().packetTotal = yardPacketTotal;

    //TODO: Add Objects here

    player.queuePacket( landsetYardInitializePacket );
  }

  auto landSetMap = makeZonePacket< FFXIVIpcLandSetMap >( player.getId() );
  landSetMap->data().subdivision = isPlayerSubInstance( player ) == false ? 2 : 1;
  uint8_t startIndex = isPlayerSubInstance( player ) == false ? 0 : 30;
  for( uint8_t i = startIndex, count = 0; i < ( startIndex + 30 ); i++, count++ )
  {
    landSetMap->data().landInfo[ count ].status = 1;
    //memcpy( , &getLand( i )->getLand(), sizeof( Common::LandStruct ) );
  }

  player.queuePacket( landSetMap );

}

void Core::HousingZone::sendLandSet( Entity::Player& player )
{
  auto landsetInitializePacket = makeZonePacket< FFXIVIpcLandSetInitialize >( player.getId() );

  landsetInitializePacket->data().landSetId = m_landSetId;
  landsetInitializePacket->data().zoneId = m_territoryTypeId;
  //TODO: get current WorldId
  landsetInitializePacket->data().worldId = 67;
  landsetInitializePacket->data().subInstance = isPlayerSubInstance( player ) == false ? 1 : 2;

  uint8_t startIndex = isPlayerSubInstance( player ) == false ? 0 : 30;

  for( uint8_t i = startIndex, count = 0; i < ( startIndex + 30 ); i++ )
  {
    memcpy( &landsetInitializePacket->data().land[ count++ ], &getLand( i )->getLand(), sizeof( Common::LandStruct ) );
  }

  player.queuePacket( landsetInitializePacket );
}

void Core::HousingZone::sendLandUpdate( uint8_t landId )
{
  for( const auto& playerIt : m_playerMap )
  {
    auto pPlayer = playerIt.second;

    auto landUpdatePacket = makeZonePacket< FFXIVIpcLandUpdate >( pPlayer->getId() );
    landUpdatePacket->data().landId = landId;
    landUpdatePacket->data().land = getLand( landId )->getLand();

    pPlayer->queuePacket( landUpdatePacket );
  }
}

bool Core::HousingZone::isPlayerSubInstance( Entity::Player& player )
{
  return player.getPos().x < -15000.0f; //ToDo: get correct pos
}

void Core::HousingZone::playerPurchseLand( Entity::Player & player, uint8_t plot, uint8_t state )
{
  uint32_t plotPrice = getLand( plot )->getCurrentPrice();
  if( plotPrice <= player.getCurrency( CurrencyType::Gil ) )
  {
    auto pHousing = std::dynamic_pointer_cast< HousingZone >( player.getCurrentZone() );
    if( state == 1 ) //TODO: add Free company purchase
      player.sendDebug( "Free company house purchase aren't supported at this time." );
    if( state == 2 ) //Private Purchase
    {
      getLand( plot )->setPlayerOwner( player.getId() );
      getLand( plot )->setState( HouseState::sold );

      player.removeCurrency( CurrencyType::Gil, plotPrice );
      player.setLandPermissions( LandPermissionSlot::Private, 0x0B, plot, pHousing->getWardNum(), pHousing->getTerritoryTypeId() );
      player.sendLandPermissions();

      getLand( plot )->UpdateLandDb();
      sendLandUpdate( plot );
    }
  }
  //else
    //TOD: add error msg - insufficient gil
}

void Core::HousingZone::onUpdate( uint32_t currTime )
{
  for( uint8_t i = 0; i < 60; i++ )
  {
    getLand( i )->Update( currTime );
  }
}

uint8_t Core::HousingZone::getWardNum() const
{
  return m_wardNum;
}

uint32_t Core::HousingZone::getLandSetId() const
{
  return m_landSetId;
}

Core::LandPtr Core::HousingZone::getLand( uint8_t id )
{
  auto it = m_landPtrMap.find( id );
  if( it == m_landPtrMap.end() )
    return nullptr;

  return it->second;
}