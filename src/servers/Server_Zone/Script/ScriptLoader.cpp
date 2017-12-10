#include "ScriptLoader.h"

#include <Server_Common/Logging/Logger.h>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>

extern Core::Logger g_log;

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
      g_log.fatal( "Failed to unload module @ 0x" + boost::str( boost::format( "%|08X|" ) % handle ) );

      return false;
   }

   g_log.debug( "Unloaded module @ 0x" + boost::str( boost::format( "%|08X|" ) % handle ) );

   return true;
}

ModuleHandle Core::Scripting::ScriptLoader::loadModule( std::string path )
{
#ifdef _WIN32
   ModuleHandle handle = LoadLibrary( path.c_str() );
#else
   ModuleHandle handle = dlopen( path.c_str(), RTLD_LAZY );
#endif

   if( !handle )
   {
      g_log.error( "Failed to load module from: " + path );

      return NULL;
   }

   g_log.info( "Loaded module from '" + path + "' @ 0x" + boost::str( boost::format( "%|08X|" ) % handle ) );

   boost::filesystem::path f( path );
   m_moduleMap.insert( std::make_pair( f.stem().string(), handle ) );

   return handle;
}

ScriptObject* Core::Scripting::ScriptLoader::getScriptObject( ModuleHandle handle, std::string name )
{
   typedef ScriptObject* (*getScriptObjectType)();
   auto fn = boost::str( boost::format( "get%1%" ) % name );

   g_log.info( "getting symbol: " + fn  );

#ifdef _WIN32
   getScriptObjectType func = reinterpret_cast< getScriptObjectType >( GetProcAddress( handle, fn.c_str() ) );
#else
   getScriptObjectType func = reinterpret_cast< getScriptObjectType >( dlsym( handle, fn.c_str() ) );
#endif

   if( func )
      return func();
   else
      return nullptr;
}

bool Core::Scripting::ScriptLoader::unloadScript( std::string name )
{
   auto moduleHandle = m_moduleMap.at( name );
   if( moduleHandle )
   {
      return unloadModule( moduleHandle );
   }

   g_log.info( "Module '" + name + "' is not loaded" );
   return false;
}

bool Core::Scripting::ScriptLoader::unloadScript( ModuleHandle handle )
{
   for( auto it = m_moduleMap.begin(); it != m_moduleMap.end(); ++it )
   {
      if( it->second == handle )
      {
         m_moduleMap.erase( it );
         return unloadModule( handle );
      }
   }

   return false;
}