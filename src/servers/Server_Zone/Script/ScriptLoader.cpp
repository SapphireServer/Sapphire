#include "ScriptLoader.h"

#include <Server_Common/Logging/Logger.h>
#include <Server_Common/Config/XMLConfig.h>
#include "ServerZone.h"

#include <boost/format.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>

extern Core::Logger g_log;
extern Core::ServerZone g_serverZone;

namespace fs = boost::filesystem;

Core::Scripting::ScriptLoader::ScriptLoader()
{}

const std::string Core::Scripting::ScriptLoader::getModuleExtension()
{
#ifdef _WIN32
   return ".dll";
#elif __APPLE__
   return ".dylib";
#else
   return ".so";
#endif
}

bool Core::Scripting::ScriptLoader::unloadModule( ModuleHandle handle )
{
#ifdef _WIN32
   bool success = FreeLibrary( handle ) != 0;
#else
   bool success = dlclose( handle ) == 0;
#endif

   if( !success )
   {
      g_log.error( "Failed to unload module @ 0x" + boost::str( boost::format( "%|08X|" ) % handle ) );

      return false;
   }

   g_log.debug( "Unloaded module @ 0x" + boost::str( boost::format( "%|08X|" ) % handle ) );

   return true;
}

Core::Scripting::ScriptInfo* Core::Scripting::ScriptLoader::loadModule( const std::string& path )
{
   fs::path f( path );

   if ( isModuleLoaded( f.stem().string() ) )
   {
      g_log.error( "Unable to load module '" + f.stem().string() + "' as it is already loaded" );
      return nullptr;
   }

   // copy to temp dir
   fs::path cacheDir( f.parent_path() /= g_serverZone.getConfig()->getValue< std::string >( "Settings.General.Scripts.CachePath", "./cache/" ) );
   fs::create_directories( cacheDir );
   fs::path dest( cacheDir /= f.filename().string() );

   try
   {
      fs::copy_file( f, dest, fs::copy_option::overwrite_if_exists );
   }
   catch( const boost::filesystem::filesystem_error& err )
   {
      g_log.error( "Error copying file to cache: " + err.code().message() );

      return nullptr;
   }


#ifdef _WIN32
   ModuleHandle handle = LoadLibrary( dest.string().c_str() );
#else
   ModuleHandle handle = dlopen( dest.string().c_str(), RTLD_LAZY );
#endif

   if( !handle )
   {
      g_log.error( "Failed to load module from: " + path );

      return nullptr;
   }

   g_log.debug( "Loaded module '" + f.filename().string() + "' @ 0x" + boost::str( boost::format( "%|08X|" ) % handle ) );

   auto info = new ScriptInfo;
   info->handle = handle;
   info->library_name = f.stem().string();
   info->cache_path = dest.string();
   info->library_path = f.string();

   m_scriptMap.insert( std::make_pair( f.stem().string(), info ) );

   return info;
}

ScriptObject* Core::Scripting::ScriptLoader::getScriptObject( ModuleHandle handle )
{
   using getScript = ScriptObject*(*)();

#ifdef _WIN32
   getScript func = reinterpret_cast< getScript >( GetProcAddress( handle, "getScript" ) );
#else
   getScript func = reinterpret_cast< getScript >( dlsym( handle, "getScript" ) );
#endif

   if( func )
   {
      auto ptr = func();

      g_log.debug( "got ScriptObject @ 0x" + boost::str( boost::format( "%|08X|" ) % ptr ) );
      g_log.debug( "script info -> name: " + std::string( ptr->getName() ) + ", id: " + std::to_string( ptr->getId() ) );

      return ptr;
   }
   else
      return nullptr;
}

bool Core::Scripting::ScriptLoader::unloadScript( Core::Scripting::ScriptInfo* info )
{
   return unloadScript( info->handle );
}

bool Core::Scripting::ScriptLoader::unloadScript( ModuleHandle handle )
{
   for( auto it = m_scriptMap.begin(); it != m_scriptMap.end(); ++it )
   {
      if( it->second->handle == handle )
      {
         auto info = it->second;
         m_scriptMap.erase( it );

         if( unloadModule( handle ) )
         {
            // remove cached file
            fs::remove( info->cache_path );

            delete info;

            return true;
         }

         g_log.error( "failed to unload module: " + info->library_name );

         return false;
      }
   }

   return false;
}

bool Core::Scripting::ScriptLoader::isModuleLoaded( std::string name )
{
   for( auto it = m_scriptMap.begin(); it != m_scriptMap.end(); ++it )
   {
      if( boost::iequals( it->second->library_name, name ) )
         return true;
   }

   return false;
}

Core::Scripting::ScriptInfo* Core::Scripting::ScriptLoader::getScriptInfo( std::string name )
{
   for( auto it = m_scriptMap.begin(); it != m_scriptMap.end(); ++it )
   {
      if( it->second->script_name == name )
      {
         return it->second;
      }
   }

   return nullptr;
}

void Core::Scripting::ScriptLoader::findScripts( std::set< Core::Scripting::ScriptInfo* >& scripts, const std::string& search )
{
   for( auto it = m_scriptMap.begin(); it != m_scriptMap.end(); ++it )
   {
      if( it->second->script_name.find( search ) != std::string::npos )
      {
         scripts.insert( it->second );
      }
   }
}