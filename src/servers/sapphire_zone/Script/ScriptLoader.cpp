#include "ScriptLoader.h"

#include <Logging/Logger.h>
#include <Config/XMLConfig.h>

#include "ServerZone.h"

#include <boost/format.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>

#include "Framework.h"
extern Core::Framework g_fw;

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
  
   auto pLog = g_fw.get< Logger >();

   if( !success )
   {
      pLog->error( "Failed to unload module @ 0x" + boost::str( boost::format( "%|08X|" ) % handle ) );

      return false;
   }

   pLog->debug( "Unloaded module @ 0x" + boost::str( boost::format( "%|08X|" ) % handle ) );

   return true;
}

Core::Scripting::ScriptInfo* Core::Scripting::ScriptLoader::loadModule( const std::string& path )
{
   auto pLog = g_fw.get< Logger >();
   auto pConfig = g_fw.get< XMLConfig >();
   fs::path f( path );

   if( isModuleLoaded( f.stem().string() ) )
   {
      pLog->error( "Unable to load module '" + f.stem().string() + "' as it is already loaded" );
      return nullptr;
   }

   // copy to temp dir
   fs::path cacheDir( f.parent_path() /= pConfig->getValue< std::string >( "Settings.General.Scripts.CachePath", "./cache/" ) );
   fs::create_directories( cacheDir );
   fs::path dest( cacheDir /= f.filename().string() );

   try
   {
      fs::copy_file( f, dest, fs::copy_option::overwrite_if_exists );
   }
   catch( const boost::filesystem::filesystem_error& err )
   {
      pLog->error( "Error copying file to cache: " + err.code().message() );

      return nullptr;
   }


#ifdef _WIN32
   ModuleHandle handle = LoadLibrary( dest.string().c_str() );
#else
   ModuleHandle handle = dlopen( dest.string().c_str(), RTLD_LAZY );
#endif

   if( !handle )
   {
      pLog->error( "Failed to load module from: " + path );

      return nullptr;
   }

   pLog->debug( "Loaded module '" + f.filename().string() + "' @ 0x" + boost::str( boost::format( "%|08X|" ) % handle ) );

   auto info = new ScriptInfo;
   info->handle = handle;
   info->library_name = f.stem().string();
   info->cache_path = dest.string();
   info->library_path = f.string();

   m_scriptMap.insert( std::make_pair( f.stem().string(), info ) );

   return info;
}

ScriptObject** Core::Scripting::ScriptLoader::getScripts( ModuleHandle handle )
{
   using getScripts = ScriptObject**( *)( );
   auto pLog = g_fw.get< Logger >();

#ifdef _WIN32
   getScripts func = reinterpret_cast< getScripts >( GetProcAddress( handle, "getScripts" ) );
#else
   getScripts func = reinterpret_cast< getScripts >( dlsym( handle, "getScripts" ) );
#endif

   if( func )
   {
      auto ptr = func();

      pLog->debug( "got ScriptObject array @ 0x" + boost::str( boost::format( "%|08X|" ) % ptr ) );

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
   auto pLog = g_fw.get< Logger >();
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

         pLog->error( "failed to unload module: " + info->library_name );

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
      if( it->second->library_name == name )
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
      if( it->second->library_name.find( search ) != std::string::npos )
      {
         scripts.insert( it->second );
      }
   }
}
