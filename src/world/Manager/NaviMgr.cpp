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
  auto provider = Navi::make_NaviProvider( internalName, m_pFw );

  if( provider->init() )
  {
    m_naviProviderTerritoryMap.insert( std::make_pair( internalName, provider ) );
    return true;
  }

  return false;
}

Sapphire::World::Navi::NaviProviderPtr Sapphire::World::Manager::NaviMgr::getNaviProvider( const std::string& internalName )
{
  if( m_naviProviderTerritoryMap.find( internalName ) != m_naviProviderTerritoryMap.end() )
    return m_naviProviderTerritoryMap[ internalName ];

  return nullptr;
}
