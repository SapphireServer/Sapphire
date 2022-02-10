#include "ScriptLoader.h"

#include <Logging/Logger.h>
#include <Config/ConfigMgr.h>
#include <Util/Util.h>
#include "WorldServer.h"

#ifdef _WIN32
#include <Service.h>
namespace Sapphire
{
  class InstanceObjectCache;
}
namespace Sapphire::Data
{
  class ExdData;
}
namespace Sapphire::World::Manager
{
  class TerritoryMgr;
}
#endif

#include <filesystem>
#include <Manager/TerritoryMgr.h>
#include <Manager/WarpMgr.h>

namespace fs = std::filesystem;

const std::string Sapphire::Scripting::ScriptLoader::getModuleExtension()
{
#ifdef _WIN32
  return ".dll";
#elif __APPLE__
  return ".dylib";
#else
  return ".so";
#endif
}

bool Sapphire::Scripting::ScriptLoader::unloadModule( ModuleHandle handle )
{
#ifdef _WIN32
  bool success = FreeLibrary( handle ) != 0;
#else
  bool success = dlclose( handle ) == 0;
#endif

  if( !success )
  {
    Logger::error( "Failed to unload module " );

    return false;
  }

  Logger::debug( "Unloaded module" );

  return true;
}

Sapphire::Scripting::ScriptInfo* Sapphire::Scripting::ScriptLoader::loadModule( const std::string& path )
{
  fs::path f( path );

  if( isModuleLoaded( f.stem().string() ) )
  {
    Logger::error( "Unable to load module '{0}' as it is already loaded", f.stem().string() );
    return nullptr;
  }

  // copy to temp dir
  fs::path cacheDir( f.parent_path() /= m_cachePath );
  fs::create_directories( cacheDir );
  fs::path dest( cacheDir /= f.filename().string() );

  try
  {
    fs::copy_file( f, dest, fs::copy_options::overwrite_existing );
  }
  catch( const fs::filesystem_error& err )
  {
    Logger::error( "Error copying file to cache: {0}", err.code().message() );

    return nullptr;
  }


#ifdef _WIN32
  ModuleHandle handle = LoadLibrary( dest.string().c_str() );
#else
  ModuleHandle handle = dlopen( dest.c_str(), RTLD_LAZY );
#endif

  if( !handle )
  {
    Logger::error( "Failed to load module from: {0}", path );

    return nullptr;
  }

  Logger::debug( "Loaded module: {0}",  f.filename().string() );

  auto info = new ScriptInfo;
  info->handle = handle;
  info->library_name = f.stem().string();
  info->cache_path = dest.string();
  info->library_path = f.string();

  m_scriptMap.insert( std::make_pair( f.stem().string(), info ) );

  return info;
}

Sapphire::ScriptAPI::ScriptObject** Sapphire::Scripting::ScriptLoader::getScripts( ModuleHandle handle )
{
  using getScripts = Sapphire::ScriptAPI::ScriptObject** ( * )();

#ifdef _WIN32
  auto func = reinterpret_cast< getScripts >( GetProcAddress( handle, "getScripts" ) );

  using win32initFunc = void(*)( std::shared_ptr< Sapphire::Data::ExdData > );
  using win32initFuncTeri = void(*)( std::shared_ptr< Sapphire::World::Manager::TerritoryMgr > );
  using win32initFuncLinkshell = void(*)( std::shared_ptr< Sapphire::World::Manager::LinkshellMgr > );
  using win32initFuncWarpMgr = void(*)( std::shared_ptr< Sapphire::World::Manager::WarpMgr > );
  using win32initIObjectCache = void(*)( std::shared_ptr< Sapphire::InstanceObjectCache > );

  auto win32init = reinterpret_cast< win32initFunc >( GetProcAddress( handle, "win32initExd" ) );
  auto win32initTeri = reinterpret_cast< win32initFuncTeri >( GetProcAddress( handle, "win32initTeri" ) );
  auto win32initLinkshell = reinterpret_cast< win32initFuncLinkshell >( GetProcAddress( handle, "win32initLinkshell" ) );
  auto win32initWarp = reinterpret_cast< win32initFuncWarpMgr >( GetProcAddress( handle, "win32initWarpMgr" ) );
  auto win32initIObject = reinterpret_cast< win32initIObjectCache >( GetProcAddress( handle, "win32initIObjectCache" ) );

  if( win32initIObject )
  {
    auto ioCache = Common::Service< Sapphire::InstanceObjectCache >::get();
    auto ptr = ioCache.lock();
    win32initIObject( ptr );
  }
  else
  {
    Logger::warn( "did not find a win32initIObjectCache export on a windows script target - the server will likely crash!" );
  }

  if( win32init )
  {
    auto exdData = Common::Service< Sapphire::Data::ExdData >::get();
    auto ptr = exdData.lock();
    win32init( ptr );

  }
  else
  {
    Logger::warn( "did not find a win32init export on a windows script target - the server will likely crash!" );
  }

  if( win32initTeri )
  {
    auto teriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::get();
    auto tptr = teriMgr.lock();
    win32initTeri( tptr );
  }
  else
  {
    Logger::warn( "did not find a win32initTeri export on a windows script target - the server will likely crash!" );
  }

  if( win32initLinkshell )
  {
    auto linkshellMgr = Common::Service< Sapphire::World::Manager::LinkshellMgr >::get();
    auto tptr = linkshellMgr.lock();
    win32initLinkshell( tptr );
  }
  else
  {
    Logger::warn( "did not find a win32initLinkshell export on a windows script target - the server will likely crash!" );
  }

  if( win32initWarp )
  {
    auto warpMgr = Common::Service< Sapphire::World::Manager::WarpMgr >::get();
    auto wptr = warpMgr.lock();
    win32initWarp( wptr );
  }
  else
  {
    Logger::warn( "did not find a win32initLinkshell export on a windows script target - the server will likely crash!" );
  }
#else
  auto func = reinterpret_cast< getScripts >( dlsym( handle, "getScripts" ) );
#endif

  if( func )
  {
    auto ptr = func();

    return ptr;
  }
  else
    return nullptr;
}

bool Sapphire::Scripting::ScriptLoader::unloadScript( Sapphire::Scripting::ScriptInfo* info )
{
  return unloadScript( info->handle );
}

bool Sapphire::Scripting::ScriptLoader::unloadScript( ModuleHandle handle )
{
  for( auto it = m_scriptMap.begin(); it != m_scriptMap.end(); ++it )
  {
    if( it->second->handle == handle )
    {
      auto info = it->second;

      if( unloadModule( handle ) )
      {
        m_scriptMap.erase( it );

        // remove cached file
        fs::remove( info->cache_path );

        delete info;

        return true;
      }

      Logger::error( "failed to unload module: {0}", info->library_name );

      return false;
    }
  }

  return false;
}

bool Sapphire::Scripting::ScriptLoader::isModuleLoaded( std::string name )
{
  for( auto it = m_scriptMap.begin(); it != m_scriptMap.end(); ++it )
  {

    if( Common::Util::toLowerCopy( it->second->library_name ) == Common::Util::toLowerCopy( name ) )
      return true;
  }

  return false;
}

Sapphire::Scripting::ScriptInfo* Sapphire::Scripting::ScriptLoader::getScriptInfo( std::string name )
{
  for( auto it = m_scriptMap.begin(); it != m_scriptMap.end(); ++it )
  {
    if( it->second->library_name == name )
    {
      return it->second;
    }
  }

  return nullptr;
}

void Sapphire::Scripting::ScriptLoader::findScripts( std::set< Sapphire::Scripting::ScriptInfo* >& scripts,
                                                     const std::string& search )
{
  for( auto it = m_scriptMap.begin(); it != m_scriptMap.end(); ++it )
  {
    if( it->second->library_name.find( search ) != std::string::npos )
    {
      scripts.insert( it->second );
    }
  }
}

const std::string& Sapphire::Scripting::ScriptLoader::getCachePath() const
{
  return m_cachePath;
}

void Sapphire::Scripting::ScriptLoader::setCachePath( const string& m_cachePath )
{
  ScriptLoader::m_cachePath = m_cachePath;
}
