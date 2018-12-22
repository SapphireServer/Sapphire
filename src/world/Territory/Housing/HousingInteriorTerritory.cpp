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
#include "Actor/EventObject.h"
#include "Manager/HousingMgr.h"
#include "Territory/Land.h"
#include "Territory/House.h"

#include "Forwards.h"
#include "HousingInteriorTerritory.h"
#include "Framework.h"

extern Sapphire::Framework g_fw;

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::World::Manager;

using namespace Sapphire;
using namespace Sapphire::World::Territory;

Housing::HousingInteriorTerritory::HousingInteriorTerritory( Common::LandIdent ident, uint16_t territoryTypeId,
                                                             uint32_t guId,
                                                             const std::string& internalName,
                                                             const std::string& contentName ) :
  Zone( territoryTypeId, guId, internalName, contentName ),
  m_landIdent( ident )
{
  m_lastActivityTime = static_cast< uint32_t >( Util::getTimeSeconds() );
}

Housing::HousingInteriorTerritory::~HousingInteriorTerritory()
{

}

bool Housing::HousingInteriorTerritory::init()
{
  return false;
}

void Housing::HousingInteriorTerritory::onPlayerZoneIn( Entity::Player& player )
{
  auto pHousingMgr = g_fw.get< HousingMgr >();
  auto pLog = g_fw.get< Logger >();
  pLog->debug(
    "HousingInteriorTerritory::onPlayerZoneIn: Zone#" + std::to_string( getGuId() ) + "|" + std::to_string( getTerritoryTypeId() ) +
    ", Entity#" + std::to_string( player.getId() ) );

  auto indoorInitPacket = makeZonePacket< FFXIVIpcHousingIndoorInitialize >( player.getId() );
  indoorInitPacket->data().u1 = 0;
  indoorInitPacket->data().u2 = 0;
  indoorInitPacket->data().u3 = 0;
  indoorInitPacket->data().u4 = 0;

  auto landSetId = pHousingMgr->toLandSetId( m_landIdent.territoryTypeId, m_landIdent.wardNum );
  auto pLand = pHousingMgr->getHousingZoneByLandSetId( landSetId )->getLand( m_landIdent.landId );
  auto pHouse = pLand->getHouse();

  for( auto i = 0; i < 10; i++ )
  {
    indoorInitPacket->data().indoorItems[ i ] = pHouse->getHouseInteriorModel(
      static_cast< Common::HousingInteriorSlot >( i ) );
  }


  uint32_t yardPacketNum;
  uint32_t yardPacketTotal = 2 + pLand->getSize();

  player.queuePacket( indoorInitPacket );

  for( yardPacketNum = 0; yardPacketNum < yardPacketTotal; yardPacketNum++ )
  {
    auto objectInitPacket = makeZonePacket< FFXIVIpcHousingObjectInitialize >( player.getId() );
    memcpy( &objectInitPacket->data().landIdent, &m_landIdent, sizeof( Common::LandIdent ) );
    objectInitPacket->data().u1 = 0;
    objectInitPacket->data().u2 = 100;
    objectInitPacket->data().packetNum = yardPacketNum;
    objectInitPacket->data().packetTotal = yardPacketTotal;

    //TODO: Add Objects here

    player.queuePacket( objectInitPacket );
  }

}

void Housing::HousingInteriorTerritory::onUpdate( uint32_t currTime )
{
  if( m_playerMap.size() > 0 )
    m_lastActivityTime = currTime;
}

uint32_t Housing::HousingInteriorTerritory::getLastActivityTime() const
{
  return m_lastActivityTime;
}

const Common::LandIdent Housing::HousingInteriorTerritory::getIdent() const
{
  return m_landIdent;
}