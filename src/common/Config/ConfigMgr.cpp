#include "ConfigMgr.h"
#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

/**
 * Loads an ini file and parses it
 * @param configName the name of ini file relative to m_configFolderRoot to load alongside global.ini
 * @return true if loading was successful
 */
bool Sapphire::ConfigMgr::loadConfig( const std::string& configName )
{
  // get global config
  auto configFile = fs::path( fs::path( m_configFolderRoot ) / configName );

  if( !fs::exists( configFile ) )
  {
    copyDefaultConfig( configName );
    return false;
  }

  m_pInih = std::unique_ptr< INIReader >( new INIReader( configFile.string() ) );

  if( m_pInih->ParseError() < 0 )
    return false;

  return true;
}

bool Sapphire::ConfigMgr::copyDefaultConfig( const std::string& configName )
{
  fs::path configPath( m_configFolderRoot );
  configPath /= configName;

  if( !fs::exists( configPath.string() + m_configDefaultSuffix ) )
  {
    // no default file :(
    return false;
  }

  fs::copy_file( configPath.string() + m_configDefaultSuffix, configPath );

  return true;
}
