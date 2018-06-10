#include "ConfigMgr.h"

#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>

/**
 * Loads an ini file and parses it
 * @param configName the name of ini file relative to m_configFolderRoot to load alongside global.ini
 * @return true if loading was successful
 */
bool Core::ConfigMgr::loadConfig( const std::string& configName )
{
   std::stringstream configStream;

   // get global config
   auto configDir = boost::filesystem::path( m_configFolderRoot );

   if( !boost::filesystem::exists( configDir ) )
   {
      return false;
   }

   auto globalConfig = boost::filesystem::path( configDir / m_globalConfigFile );
   if( !boost::filesystem::exists( globalConfig ) )
   {
      if( !copyDefaultConfig( globalConfig.filename().string() ) )
         return false;
   }

   std::ifstream globalConfigFile( globalConfig.c_str() );
   configStream << globalConfigFile.rdbuf();

   // add some newlines just in case there's no newline at the end of the global file
   configStream << "\n\n";

   // get local config
   auto localConfig = boost::filesystem::path( configDir / configName );
   if( !boost::filesystem::exists( localConfig ) )
   {
      if( !copyDefaultConfig( localConfig.filename().string() ) )
         return false;
   }
   std::ifstream configFile( localConfig.c_str() );
   configStream << configFile.rdbuf();

   // parse the tree and we're fuckin done
   boost::property_tree::read_ini( configStream, m_propTree );

   return true;
}

bool Core::ConfigMgr::copyDefaultConfig( const std::string& configName )
{
   boost::filesystem::path configPath( m_configFolderRoot );
   configPath /= configName;

   if( !boost::filesystem::exists( configPath.string() + m_configDefaultSuffix ) )
   {
      // no default file :(
      return false;
   }

   boost::filesystem::copy_file( configPath.string() + m_configDefaultSuffix, configPath );

   return true;
}