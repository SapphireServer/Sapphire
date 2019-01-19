#include "NativeScriptMgr.h"

#include <Crypt/md5.h>
#include "ServerMgr.h"

#include "Framework.h"

namespace Sapphire::Scripting
{

  bool NativeScriptMgr::loadScript( const std::string& path )
  {
    auto module = m_loader.loadModule( path );
    if( !module )
      return false;

    auto scripts = m_loader.getScripts( module->handle );
    if( !scripts )
    {
      m_loader.unloadScript( module );
      return false;
    }

    //
    bool success = false;

    for( int i = 0;; i++ )
    {
      if( scripts[ i ] == nullptr )
        break;

      auto script = scripts[ i ];
      module->scripts.push_back( script );

      script->setFramework( framework().get() );

      m_scripts[ script->getType() ][ script->getId() ] = script;

      success = true;
    }

    if( !success )
    {
      m_loader.unloadScript( module->handle );
      return false;
    }

    return true;
  }

  const std::string NativeScriptMgr::getModuleExtension()
  {
    return m_loader.getModuleExtension();
  }

  bool NativeScriptMgr::unloadScript( const std::string& name )
  {
    auto info = m_loader.getScriptInfo( name );
    if( !info )
      return false;

    return unloadScript( info );
  }

  bool NativeScriptMgr::unloadScript( ScriptInfo* info )
  {
    for( auto& script : info->scripts )
    {
      m_scripts[ script->getType() ].erase( script->getId() );

      delete script;
    }

    return m_loader.unloadScript( info );
  }

  void NativeScriptMgr::queueScriptReload( const std::string& name )
  {
    auto info = m_loader.getScriptInfo( name );
    if( !info )
      return;

    // backup actual lib path
    std::string libPath( info->library_path );

    if( !unloadScript( info ) )
      return;

    m_scriptLoadQueue.push( libPath );
  }

  void NativeScriptMgr::processLoadQueue()
  {
    std::vector< std::string > deferredLoads;

    while( !m_scriptLoadQueue.empty() )
    {
      auto item = m_scriptLoadQueue.front();

      // if it fails, we defer the loading to the next tick
      if( !loadScript( item ) )
        deferredLoads.push_back( item );

      m_scriptLoadQueue.pop();
    }

    if( !deferredLoads.empty() )
    {
      for( auto& item : deferredLoads )
        m_scriptLoadQueue.push( item );
    }
  }

  void NativeScriptMgr::findScripts( std::set< Sapphire::Scripting::ScriptInfo* >& scripts, const std::string& search )
  {
    return m_loader.findScripts( scripts, search );
  }

  bool NativeScriptMgr::isModuleLoaded( const std::string& name )
  {
    return m_loader.isModuleLoaded( name );
  }

  NativeScriptMgr::NativeScriptMgr( FrameworkPtr pFw  ) :
    World::Manager::BaseManager( pFw )
  {
    auto pServerMgr = framework()->get< Sapphire::World::ServerMgr >();
    m_loader.setCachePath( pServerMgr->getConfig().scripts.cachePath );
  }


  std::shared_ptr< NativeScriptMgr > createNativeScriptMgr( FrameworkPtr pFw )
  {
    return std::make_shared< NativeScriptMgr >( pFw );
  }
}

