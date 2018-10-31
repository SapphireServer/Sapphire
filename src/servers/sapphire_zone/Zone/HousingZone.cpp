#include <Common.h>
#include <Logging/Logger.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Database/DatabaseDef.h>

#include <Network/GamePacketNew.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

#include "Actor/Player.h"
#include "Actor/Actor.h"
#include "Landset.h"

#include "Forwards.h"
#include "HousingZone.h"
#include "Framework.h"

extern Core::Framework g_fw;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

Core::HousingZone::HousingZone( uint8_t wardNum,
                                uint16_t territoryId,
                                uint32_t guId,
                                const std::string& internalName,
                                const std::string& contentName ) :
  Zone( territoryId, guId, internalName, contentName ),
  m_wardNum( wardNum ),
  m_zoneId( territoryId )
{

}

bool Core::HousingZone::init()
{
  uint32_t landsetId;
  for( landsetId = 0; landsetId < 60; landsetId++ )
  {
    auto pObject = make_Landset( m_territoryId, getWardNum(), landsetId );
    pObject->setHouseSize( 1 );
    m_landsetPtrMap[ landsetId ] = pObject;
  }

  return true;
}

Core::HousingZone::~HousingZone()
{

}

void Core::HousingZone::onPlayerZoneIn(Entity::Player& player)
{
  auto pLog = g_fw.get< Logger >();
  pLog->debug( "HousingZone::onPlayerZoneIn: Zone#" + std::to_string(getGuId()) + "|"
               ", Entity#" + std::to_string( player.getId() ) );

  uint32_t yardPacketNum;
  uint32_t yardPacketTotal = 8;

  sendMap( player );

  for( yardPacketNum = 0; yardPacketNum < yardPacketTotal; yardPacketNum++ )
  {
    auto landsetYardInitializePacket = makeZonePacket< FFXIVIpcLandsetYardInitialize >(player.getId());
    landsetYardInitializePacket->data().unknown1 = 0xFFFFFFFF;
    landsetYardInitializePacket->data().unknown2 = 0xFFFFFFFF;
    landsetYardInitializePacket->data().unknown3 = 0xFF;
    landsetYardInitializePacket->data().packetNum = yardPacketNum;
    landsetYardInitializePacket->data().packetTotal = yardPacketTotal;

    //TODO: Add Objects here

    player.queuePacket(landsetYardInitializePacket);
  }

}

void Core::HousingZone::sendMap( Entity::Player& player )
{
  auto landsetInitializePacket = makeZonePacket< FFXIVIpcLandsetInitialize >( player.getId() );

  landsetInitializePacket->data().wardNum = m_wardNum;
  landsetInitializePacket->data().zoneId = m_territoryId;
  //TODO: get current WorldId
  landsetInitializePacket->data().worldId = 67;
  landsetInitializePacket->data().subInstance = isPlayerSubInstance( player ) == false ? 1 : 2;

  uint8_t startIndex = isPlayerSubInstance( player ) == false ? 0 : 30;
  uint8_t count = 0;
  for( uint8_t i = startIndex; i < ( startIndex + 30 ); i++ )
  {
    memcpy( &landsetInitializePacket->data().landset[ count ],
            &getLandset( i )->getLandset(), sizeof( Common::LandsetStruct ) );
    count++;
  }

  player.queuePacket( landsetInitializePacket );
}

bool Core::HousingZone::isPlayerSubInstance( Entity::Player& player )
{
  return player.getPos().x < -15000.0f; //ToDo: get correct pos
}

void Core::HousingZone::onUpdate( uint32_t currTime )
{
  for( uint8_t i = 0; i < 60; i++ )
  {
    getLandset( i )->Update( currTime );
  }
}

uint8_t Core::HousingZone::getWardNum() const
{
  return m_wardNum;
}

Core::LandsetPtr Core::HousingZone::getLandset( uint8_t id )
{
  auto it = m_landsetPtrMap.find( id );
  if( it == m_landsetPtrMap.end() )
    return nullptr;

  return it->second;
}