#include "HousingMgr.h"
#include "HousingMgr.h"
#include <Logging/Logger.h>
#include <Database/DatabaseDef.h>
#include <Exd/ExdDataGenerated.h>

#include <unordered_map>

#include "Actor/Player.h"

#include "Zone.h"
#include "HousingZone.h"
#include "HousingMgr.h"
#include "Land.h"
#include "Framework.h"

extern Core::Framework g_fw;

Core::HousingMgr::HousingMgr() :
  m_lastLandId( 0 )
{

}

Core::HousingMgr::~HousingMgr()
{

}

bool Core::HousingMgr::init()
{

  return true;
}

uint16_t Core::HousingMgr::getNexLandId()
{
  return ++m_lastLandId;
}

void Core::HousingMgr::insertHousingZone( Core::Data::HousingZonePtr hZone )
{
  uint16_t id = getNexLandId();
  m_housingZonePtrMap[id] = hZone;
}

Core::Data::HousingZonePtr Core::HousingMgr::getHousingZone( uint16_t id )
{
  auto it = m_housingZonePtrMap.find( id );
  if( it == m_housingZonePtrMap.end() )
    return nullptr;

  return it->second;
}

Core::LandPtr Core::HousingMgr::getLandByOwnerId( uint32_t id )
{
  for( const auto& hZoneIt : m_housingZonePtrMap )
  {
    auto pHousingZone = hZoneIt.second;
    for( uint8_t landId = 0; landId < 60; landId++ )
    {
      if( pHousingZone->getLand( landId )->getPlayerOwner() == id )
      {
        return pHousingZone->getLand( landId );
      }
    }
  }
  return nullptr;
}
