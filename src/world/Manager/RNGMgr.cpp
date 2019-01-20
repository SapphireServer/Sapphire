#include "RNGMgr.h"
#include <Logging/Logger.h>

Sapphire::World::Manager::RNGMgr::RNGMgr( FrameworkPtr pFw ) :
  BaseManager( pFw ),
  m_engine( *engineSeed< std::mt19937::state_size >() )
{

}

