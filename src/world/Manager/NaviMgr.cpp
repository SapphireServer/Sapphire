#include "NaviMgr.h"
#include "Navi/NaviProvider.h"
#include <Logging/Logger.h>

bool Sapphire::World::Manager::NaviMgr::setupTerritory( const std::string& bgPath, uint32_t guid )
{
  std::string bg = getBgName( bgPath );

  // check if a provider exists already
  if( m_naviProviderTerritoryMap.find( guid ) != m_naviProviderTerritoryMap.end() )
    return true;

  auto provider = Navi::make_NaviProvider( bg );

  if( provider->init() )
  {
    m_naviProviderTerritoryMap[ guid ] = provider;
    return true;
  }

  return false;
}

Sapphire::World::Navi::NaviProviderPtr Sapphire::World::Manager::NaviMgr::getNaviProvider( const std::string& bgPath, uint32_t guid )
{
  std::string bg = getBgName( bgPath );

  if( m_naviProviderTerritoryMap.find( guid ) != m_naviProviderTerritoryMap.end() )
    return m_naviProviderTerritoryMap[ guid ];

  return nullptr;
}

std::string Sapphire::World::Manager::NaviMgr::getBgName( const std::string& bgPath )
{
  auto findPos = bgPath.find_last_of( '/' );
  if( findPos != std::string::npos )
    return bgPath.substr( findPos + 1 );

  return "";
}
