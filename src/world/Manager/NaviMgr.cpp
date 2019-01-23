#include "NaviMgr.h"
#include <Logging/Logger.h>

Sapphire::World::Manager::NaviMgr::NaviMgr( FrameworkPtr pFw ) :
  BaseManager( pFw ),
  m_pFw( pFw )
{
}

bool Sapphire::World::Manager::NaviMgr::setupTerritory( std::string internalName )
{
  auto provider = new NaviProvider( internalName );

  if( provider->init() )
  {
    m_naviProviderTerritoryMap.insert( std::make_pair( internalName, provider ) );
    return true;
  }

  return false;
}

Sapphire::NaviProvider* Sapphire::World::Manager::NaviMgr::getNaviProvider( std::string internalName )
{
  if( m_naviProviderTerritoryMap.find( internalName ) != m_naviProviderTerritoryMap.end() )
    return m_naviProviderTerritoryMap[ internalName ];

  return nullptr;
}
