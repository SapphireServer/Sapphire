#include "ConfigMgr.h"
#include <iostream>
#include <fstream>
#include <experimental/filesystem>

/**
 * Loads an ini file and parses it
 * @param configName the name of ini file relative to m_configFolderRoot to load alongside global.ini
 * @return true if loading was successful
 */
bool Core::ConfigMgr::loadConfig( const std::string& configName )
{
  std::stringstream configStream;

  // get global config
  auto configDir = std::experimental::filesystem::path( m_configFolderRoot );

  if( !std::experimental::filesystem::exists( configDir ) )
  {
    return false;
  }

  auto globalConfig = std::experimental::filesystem::path( configDir / m_globalConfigFile );
  if( !std::experimental::filesystem::exists( globalConfig ) )
  {
    if( !copyDefaultConfig( globalConfig.filename().string() ) )
      return false;
  }

  std::ifstream globalConfigFile( globalConfig.c_str() );
  configStream << globalConfigFile.rdbuf();

  // add some newlines just in case there's no newline at the end of the global file
  configStream << "\n\n";

  // get local config
  auto localConfig = std::experimental::filesystem::path( configDir / configName );
  if( !std::experimental::filesystem::exists( localConfig ) )
  {
    if( !copyDefaultConfig( localConfig.filename().string() ) )
      return false;
  }
  std::ifstream configFile( localConfig.c_str() );
  configStream << configFile.rdbuf();

  // parse the trxee and we're fuckin done
  //boost::property_tree::read_ini( configStream, m_propTree );
  
  m_pInih = std::unique_ptr< INIReader >( new INIReader( localConfig ) );

  if( m_pInih->ParseError() < 0 )
    return false;

  return true;
}

bool Core::ConfigMgr::copyDefaultConfig( const std::string& configName )
{
  std::experimental::filesystem::path configPath( m_configFolderRoot );
  configPath /= configName;

  if( !std::experimental::filesystem::exists( configPath.string() + m_configDefaultSuffix ) )
  {
    // no default file :(
    return false;
  }

  std::experimental::filesystem::copy_file( configPath.string() + m_configDefaultSuffix, configPath );

  return true;
}
