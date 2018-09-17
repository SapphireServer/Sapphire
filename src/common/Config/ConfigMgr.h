#ifndef SAPPHIRE_CONFIGMGR_H
#define SAPPHIRE_CONFIGMGR_H

#include <boost/property_tree/ptree.hpp>

namespace Core {
class ConfigMgr
{
public:
  ConfigMgr() = default;

  ~ConfigMgr() = default;

  bool loadConfig( const std::string& configName );

  template< class T >
  T getValue( const std::string& name, T defaultValue = T() )
  {
    try
    {
      return m_propTree.get< T >( name );
    }
    catch( ... )
    {
      return defaultValue;
    }
  }

  template< class T >
  void setValue( const std::string& name, T defaultValue = T() )
  {
    m_propTree.put( name, defaultValue );
  }

private:
  bool copyDefaultConfig( const std::string& configName );

  boost::property_tree::ptree m_propTree;
  const std::string m_globalConfigFile = "global.ini";
  const std::string m_configFolderRoot = "./config/";
  const std::string m_configDefaultSuffix = ".default";
};
}

#endif //SAPPHIRE_CONFIGMGR_H
