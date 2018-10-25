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
  // get global config
  auto configDir = std::experimental::filesystem::path( m_configFolderRoot );

  m_pInih = std::unique_ptr< INIReader >( new INIReader( 
    std::experimental::filesystem::path( configDir / configName ) ) );

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
