#include "NaviMgr.h"
#include "Navi/NaviProvider.h"
#include <Logging/Logger.h>

Sapphire::World::Manager::NaviMgr::NaviMgr( FrameworkPtr pFw ) :
  BaseManager( pFw ),
  m_pFw( pFw )
{
}

bool Sapphire::World::Manager::NaviMgr::setupTerritory( const std::string& internalName )
{
  std::string bg;
  auto findPos = internalName.find_last_of( "/" );
  if( findPos != std::string::npos )
    bg = internalName.substr( findPos + 1 );

  auto provider = Navi::make_NaviProvider( bg, m_pFw );

  if( provider->init() )
  {
    m_naviProviderTerritoryMap.insert( std::make_pair( bg, provider ) );
    return true;
  }

  return false;
}

Sapphire::World::Navi::NaviProviderPtr Sapphire::World::Manager::NaviMgr::getNaviProvider( const std::string& internalName )
{
  std::string bg;
  auto findPos = internalName.find_last_of( "/" );
  if( findPos != std::string::npos )
    bg = internalName.substr( findPos + 1 );

  if( m_naviProviderTerritoryMap.find( bg ) != m_naviProviderTerritoryMap.end() )
    return m_naviProviderTerritoryMap[ bg ];

  return nullptr;
}
