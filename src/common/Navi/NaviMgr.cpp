#include "NaviMgr.h"
#include <Navi/NaviProvider.h>
#include <Service.h>
#include <filesystem>

using namespace Sapphire;

bool Common::Navi::NaviMgr::setupTerritory( const std::string& naviPath, const std::string& bgPath, uint32_t guid )
{
  std::string bg = getBgName( bgPath );

  // check if a provider exists already
  if( m_naviProviderTerritoryMap.find( guid ) != m_naviProviderTerritoryMap.end() )
    return true;

  auto provider = std::make_shared< Common::Navi::NaviProvider >( bg );

  if( provider->init( naviPath ) )
  {
    m_naviProviderTerritoryMap[ guid ] = provider;
    return true;
  }

  return false;
}

Common::Navi::NaviProviderPtr Common::Navi::NaviMgr::getNaviProvider( const std::string& bgPath, uint32_t guid )
{
  std::string bg = getBgName( bgPath );

  if( m_naviProviderTerritoryMap.find( guid ) != m_naviProviderTerritoryMap.end() )
    return m_naviProviderTerritoryMap[ guid ];

  return nullptr;
}

std::string Common::Navi::NaviMgr::getBgName( const std::string& bgPath )
{
  auto findPos = bgPath.find_last_of( '/' );
  if( findPos != std::string::npos )
    return bgPath.substr( findPos + 1 );

  return "";
}
