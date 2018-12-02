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
    indoorInitPacket->data().indoorItems[ i ] = pHouse->getHouseInteriorPart( (Common::HousingInteriorSlot)i );
  }


  uint32_t yardPacketNum;
  uint32_t yardPacketTotal = 2 + pLand->getSize();

  player.queuePacket( indoorInitPacket );

  for( yardPacketNum = 0; yardPacketNum < yardPacketTotal; yardPacketNum++ )
  {
    auto housingObjectInitializPacket = makeZonePacket< FFXIVIpcHousingObjectInitialize >( player.getId() );
    memcpy( &housingObjectInitializPacket->data().landIdent, &m_landIdent, sizeof( Common::LandIdent ) );
    housingObjectInitializPacket->data().landIdent.worldId = 67;
    housingObjectInitializPacket->data().u1 = 0;
    housingObjectInitializPacket->data().u2 = 100;
    housingObjectInitializPacket->data().packetNum = yardPacketNum;
    housingObjectInitializPacket->data().packetTotal = yardPacketTotal;

    //TODO: Add Objects here

    player.queuePacket( housingObjectInitializPacket );
  }

}

void Housing::HousingInteriorTerritory::onUpdate( uint32_t currTime )
{

}